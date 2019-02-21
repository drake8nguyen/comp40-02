/*
* urray2.c
* COMP 40 - Homework 2
* Nick Daigler & Minh Duc Nguyen
* September 17th, 2018
*/

#include <stdlib.h>
#include <stdio.h>
#include "uarray.h"
#include "uarray2.h"
#include <assert.h>
#define T UArray2_T

typedef struct {
        int WIDTH; /* Columns */
        int HEIGHT; /*  Rows */
        int ELEMENT_SIZE;
        UArray_T ray;
} T;

T* UArray2_new(int width, int height, int element_size)
{
        T *two_d = malloc(sizeof(T));
        two_d->ray = UArray_new(width * height, element_size);
        two_d->WIDTH = width;
        two_d->HEIGHT = height;
        two_d->ELEMENT_SIZE = element_size;
        return two_d;
}
                
void UArray2_free(T **array)
{
        UArray_free((UArray_T *) &(*array)->ray);
        free(*array);
}

void *UArray2_at(T *array, int col, int row)
{
        return UArray_at(array->ray, (col * array->HEIGHT + row));
}

void UArray2_map_col_major(T *array, void apply(int col, int row, T *array,
                           void *val, void *cl), void *cl)
{
        for (int col = 0; col < array->WIDTH; col++) {
                for (int row = 0; row < array->HEIGHT; row++) {
                        void *val = UArray2_at(array, col, row);
                        apply(col, row, array, val, cl);
                }
        }
}

void UArray2_map_row_major(T *array, void apply(int col, int row, T *array,
                           void *val, void *cl), void *cl)
{
        for (int row = 0; row < array->HEIGHT; row++) {
                for (int col = 0; col < array->WIDTH; col++) {
                        void *val = UArray2_at(array, col, row);
                        apply(col, row, array, val, cl);
                }
        }
}

int UArray2_width(T *array)
{
        return array->WIDTH;
}

int UArray2_height(T *array)
{
        return array->HEIGHT;
}

int UArray2_size(T *array)
{
        return array->ELEMENT_SIZE;
}
