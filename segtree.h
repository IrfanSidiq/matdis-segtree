/* File : segtree.h */
/* ADT Segment Tree dengan Representasi Array */

#ifndef SEGTREE_H
#define SEGTREE_H

#include "boolean.h"

/* Jumlah maksimum ukuran data, dapat diganti sesuai kondisi */
#define CAPACITY 100000

/* Definisi TYPE Segment Tree dengan representasi array */
typedef int ElType;
typedef int IdxType;
typedef struct {
    ElType arr[2 * (CAPACITY+1)];
    int nEff;  // Jumlah data input
} SegTree;

/* ********** AKSES (Selektor) ********** */
#define CONTENTS(t) (t).arr
#define ELMT(t, i) (CONTENTS(t))[i]
#define NEFF(t) (t).nEff

/* ********** Predikat ********** */
boolean isSegTreeEmpty(SegTree t);
/* I.S. t terdefinisi */
/* F.S. Mengembalikan true jika segment tree kosong, yaitu nEff = 0 */

boolean isSegTreeFull(SegTree t);
/* I.S. t terdefinisi */
/* F.S. Mengembalikan true jika segment tree penuh, yaitu nEff = CAPACITY */

/* ********** Konstruktor ********** */
void BuildSegTree(SegTree *t);
/* I.S. sembarang */
/* F.S. Segment tree yaitu t berhasil terbangun, dengan akar tree adalah ELMT(t, 1) */

/* ********** Primitif Lain  ********** */
void modify(SegTree *t, IdxType pos, ElType val);
/* I.S. t terdefinisi */
/* F.S. Mengubah nilai data pada posisi pos menjadi bernilai val */

ElType query(SegTree t, int l, int r);
/* I.S. t terdefinisi */
/* F.S. Mengembalikan jumlah nilai elemen-elemen dari posisi ke-l hingga posisi ke-r */

#endif