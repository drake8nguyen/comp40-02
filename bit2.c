/*
* bit2.c
* COMP 40 - Homework 2
* Nick Daigler & Minh Duc Nguyen
* September 17th, 2018
*/

#include <stdlib.h>
#include <stdio.h>
#include <bit.h>
#include "bit2.h"

#define T Bit2_T

typedef struct {
        int WIDTH;
        int HEIGHT;
        int ELEMENT_SIZE;
        Bit_T set;
} T;

T* Bit2_new(int width, int height)
{
        T *two_d = malloc(sizeof(T));

        /* Add one to width * height because it is a checked runtime error if
                you try to update the value of the bit in the nth place, where
                n is equal to the length of the set */
        two_d->set = Bit_new(width * height + 1);

        two_d->WIDTH = width;
        two_d->HEIGHT = height;
        return two_d;
}

void Bit2_free(T **two_d)
{
        Bit_free((Bit_T *) &(*two_d)->set);
        free(*two_d);
}

int Bit2_get(T *two_d, int col, int row)
{
        int pos = row * two_d->WIDTH + col;
        if (pos > (two_d->WIDTH * two_d->HEIGHT -1)) {
                return 0;
        }

        if (pos < 0) {
                return 0;
        }

        return Bit_get(two_d->set, pos);
}

int Bit2_put(T *two_d, int col, int row, int bit)
{
        int pos = row * two_d->WIDTH + col;
        if (pos > (two_d->WIDTH * two_d->HEIGHT -1)) {
                return 0;
        }

        if (pos < 0) {
                return 0;
        }
        return Bit_put(two_d->set, pos, bit);
}

void Bit2_map_col_major(T *two_d, void apply(int col, int row, T *two_d,
                        int val, void *cl), void *cl)
{
        for (int col = 0; col < two_d->WIDTH; col++) {
                for (int row = 0; row < two_d->HEIGHT; row++) {
                        int val = Bit2_get(two_d, col, row);
                        apply(col, row, two_d, val, cl);
                }
        }       
}

void Bit2_map_row_major(T *two_d, void apply(int col, int row, T *two_d,
                        int val, void *cl), void *cl)
{
        for (int row = 0; row < two_d->HEIGHT; row++) {
                for (int col = 0; col < two_d->WIDTH; col++) {
                        int val = Bit2_get(two_d, col, row);
                        apply(col, row, two_d, val, cl);
                }
        }
}

int Bit2_width(T *two_d)
{
        return two_d->WIDTH;
}

int Bit2_height(T *two_d)
{
        return two_d->HEIGHT;
}

int Bit2_count (T *two_d)
{
        return Bit_count(two_d->set);
}
