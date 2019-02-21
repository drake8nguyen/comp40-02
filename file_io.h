/*
* file_io.c
* COMP 40 - Homework 2
* Nick Daigler & Minh Duc Nguyen
* September 25th, 2018
*/

#include <stdio.h>
#include <stdlib.h>

FILE *open_file(const char *file_name)
{
        FILE *fp;
        if (file_name != NULL) {
                fp = fopen(file_name, "rb");
                if (fp == NULL) {
                        perror(file_name);
                        exit(EXIT_FAILURE);
                }
        } else {
                fp = stdin;
        }
        return fp;
}

void close_file(FILE *fp)
{
        if (fp != stdin) {
                if (fclose(fp) != 0) {
                        exit(1);
                }
        }
}
