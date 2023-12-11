#include <stdio.h>
#include "segtree.h"

/* ********** Predikat ********** */
boolean isSegTreeEmpty(SegTree t) {
/* I.S. t terdefinisi */
/* F.S. Mengembalikan true jika segment tree kosong, yaitu nEff = 0 */
    return NEFF(t) == 0;
}

boolean isSegTreeFull(SegTree t) {
/* I.S. t terdefinisi */
/* F.S. Mengembalikan true jika segment tree penuh, yaitu nEff = CAPACITY */
    return NEFF(t) == CAPACITY;
}

/* ********** Konstruktor ********** */
void BuildSegTree(SegTree *t) {
/* I.S. sembarang */
/* F.S. Segment tree yaitu t berhasil terbangun, dengan akar tree adalah ELMT(t, 1) */
    IdxType i;
    for(i = NEFF(*t) - 1; i > 0; --i) {
        ELMT(*t, i) = ELMT(*t, i*2) + ELMT(*t, i*2 + 1);
    }
}

/* ********** Primitif Lain  ********** */
void modify(SegTree *t, IdxType pos, ElType val) {
/* I.S. t terdefinisi */
/* F.S. Melakukan increment atau decrement pada nilai data pada posisi pos sesuai nilai val */
    ELMT(*t, pos + NEFF(*t)) += val;
    
    IdxType i;
    for(i = pos/2; i > 0; i /= 2) {
        ELMT(*t, i) = ELMT(*t, i*2) + ELMT(*t, i*2 + 1);
    }
}

ElType query(SegTree t, IdxType l, IdxType r) {
/* I.S. t terdefinisi */
/* F.S. Mengembalikan jumlah nilai elemen-elemen dari posisi ke-l hingga posisi ke-r */
    l += NEFF(t); r += NEFF(t) + 1;

    ElType result = 0;
    for(; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            result += ELMT(t, l);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            result += ELMT(t, r);
        }
    }

    return result;
}
