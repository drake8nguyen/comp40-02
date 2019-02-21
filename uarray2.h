/*
* urray2.h
* COMP 40 - Homework 2
* Nick Daigler & Minh Duc Nguyen
* September 17th, 2018
*/

#ifndef UARRAY_INCLUDED
#define UARRAY_INCLUDED
#define T UArray2_T

typedef struct T* T;

T UArray2_new(int width, int height, int element_size);
void UArray2_free(T *array);
void *UArray2_at(T array, int row, int col);
void UArray2_map_row_major(T array, void(int row, int col, T array, void *val,
                           void *cl), void *cl);
void UArray2_map_col_major(T array, void(int row, int col, T array, void *val,
                           void *cl), void *cl);
int UArray2_width(T array);
int UArray2_height(T array);
int UArray2_size(T array);

#undef T
#endif
