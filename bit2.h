/*
* bit2.h
* COMP 40 - Homework 2
* Nick Daigler & Minh Duc Nguyen
* September 17th, 2018
*/

#ifndef BIT_INCLUDED
#define BIT_INCLUDED
#define T Bit2_T

typedef struct T* T;

T Bit2_new(int width, int height);
void Bit2_free(T *two_d);
int Bit2_get(T two_d, int row, int col);
int Bit2_put(T two_d, int row, int col, int bit);
void Bit2_map_row_major(T two_d, void(int row, int col, T two_d, int val,
                        void *cl), void *cl);
void Bit2_map_col_major(T two_d, void(int row, int col, T two_d, int val,
                        void *cl), void *cl);
int Bit2_width(T two_d);
int Bit2_height(T two_d);
int Bit2_count(T two_d);

#undef T
#endif
