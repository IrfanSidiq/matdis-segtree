#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "segtree.h"
#include "boolean.h"

#define CAPACITY 100000

/* ----- Variabel Global ----- */
int n;
char* daftarBuku[CAPACITY];
int arr[CAPACITY];
SegTree t;

/* ----- Deklarasi Fungsi ----- */
void Muat();
void StartMenu();
void PinjamMenu();
void DataMenu();
int validasiInput(int l, int r);
int validasiBuku();
int validasiRange(int l, int r, boolean start);


/* ----- Program Utama ----- */
int main() {
    Muat();
    while(true) StartMenu();

    return 0;
}

void Muat() {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) printf("File data gagal dimuat.\n");
    else {
        int k, i = 0;
        char line[200];

        fscanf(f, "%d\n", &n);
        NEFF(t) = n;

        while(i < n) {
            fgets(line, 200, f);
            line[strlen(line) - 1] = '\0';

            daftarBuku[i] = (char*)malloc(strlen(line)+1);
            strcpy(daftarBuku[i], line);

            fscanf(f, "%d\n", &k);
            ELMT(t, n + i) = k;
            arr[i] = k;

            i++;
        }

        BuildSegTree(&t);
    }
}

void StartMenu() {
    printf("\nSelamat datang di program simulasi kecil Perpustakaan Matdis!\nPilih aksi yang diinginkan:\n");
    printf(" ____________________________________\n");
    printf("| 1. Pinjam Buku                     |\n"); 
    printf("| 2. Data Peminjaman Buku            |\n");
    printf(" ------------------------------------\n\n");
    
    int input = validasiInput(1, 2);

    printf("\nSilahkan pilih struktur data yang diinginkan:\n");
    printf(" ______________________________\n");
    printf("| 1. Segment Tree              |\n"); 
    printf("| 2. Array                     |\n");
    printf(" ----------------------- ------\n\n");

    int pilihanStrukturData = validasiInput(1, 2);
    switch(input) {
        case 1:
            PinjamMenu(pilihanStrukturData); break;
        default:
            DataMenu(pilihanStrukturData); break;
    }
}

int validasiInput(int l, int r) {
    int input;
    boolean inputValid = false;

    while(!inputValid) {
        printf("\nPilihan menu: ");
        scanf("%d", &input);

        if (input >= l && input <= r) inputValid = true;
        else printf("Input tidak valid! Masukkan angka %d-%d.\n", l, r);
    }

    return input;
}

void PinjamMenu(int input) {
    int idxBuku = validasiBuku();

    struct timeval startTime, endTime;
    mingw_gettimeofday(&startTime, NULL);

    if (input == 1) modify(&t, idxBuku, 1);
    else arr[idxBuku]++;

    mingw_gettimeofday(&endTime, NULL);
    int elapsed = (((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec));

    int jumlahPinjam = (input == 1)? ELMT(t, idxBuku + n) : arr[idxBuku];
    printf("Anda telah berhasil meminjam buku %s!\n", daftarBuku[idxBuku]);
    printf("Jumlah buku %s yang dipinjam: %d\n", daftarBuku[idxBuku], jumlahPinjam);
    printf("Waktu eksekusi: %d microseconds\n", elapsed);

    printf("\n----------------------------------------------------------------------------\n");
}

int validasiBuku() {
    int i;
    boolean isInputValid = false;

    while(!isInputValid) {
        printf("\nMasukkan nama buku yang ingin dipinjam: ");

        fflush(stdin);
        char line[200]; fgets(line, 199, stdin);
        line[strlen(line) - 1] = '\0';
        
        i = 0;
        boolean found = false;

        while(i < n && !found) {
            if (strcasecmp(line, daftarBuku[i]) == 0) found = true;
            else i++;
        }

        if (found) isInputValid = true;
        else printf("Tidak ditemukan buku dengan judul tersebut!\n");
    }
    
    return i;
}

void DataMenu(int input) {
    printf("\nMasukkan range entri buku yang ingin dilihat:\n");
    int l = validasiRange(1, CAPACITY, true);
    int r = validasiRange(l, CAPACITY, false);

    struct timeval startTime, endTime;
    mingw_gettimeofday(&startTime, NULL);

    int totalPinjam = 0;
    if (input == 1) totalPinjam = query(t, l, r);
    else for(int i = l; i < r; ++i) totalPinjam += arr[i];

    mingw_gettimeofday(&endTime, NULL);
    int elapsed = (((endTime.tv_sec - startTime.tv_sec) * 1000000) + (endTime.tv_usec - startTime.tv_usec));

    printf("Jumlah buku yang sedang dipinjam dari entri %d-%d: %d\n", l, r, totalPinjam);
    printf("Waktu eksekusi: %d microseconds\n", elapsed);
    printf("\n----------------------------------------------------------------------------\n");
}

int validasiRange(int l, int r, boolean start) {
    int input;
    boolean inputValid = false;

    while(!inputValid) {
        if (start) printf("Entri awal: "); else printf("Entri akhir: ");
        scanf("%d", &input);

        if (input >= l && input <= r) inputValid = true;
        else printf("Input tidak valid! Masukkan angka %d-%d.\n\n", l, r);
    }

    return input;
}