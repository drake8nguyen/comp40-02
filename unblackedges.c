/*
* unblackedges.c
* COMP 40 - Homework 2
* Nick Daigler & Minh Duc Nguyen
* September 25th, 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pnmrdr.h>
#include <stdbool.h>
#include <errno.h>
#include <bit2.h>
#include <seq.h>
#include <uarray2.h>
#include <file_io.h>
#include <dfs.h>

Bit2_T populate_bitmap_with_rdr(Pnmrdr_T, Pnmrdr_mapdata);
void remove_black_edges(Bit2_T);
void pbmwrite(FILE *, Bit2_T);

int main(int argc, char **argv) 
{
        if (argc > 2) {
                fprintf(stderr, "Only one file may be inputted.\n");
                exit(1);
        }

        char *file_name = argv[1];
        FILE *fp = open_file(file_name);

        Pnmrdr_T rdr = Pnmrdr_new(fp);
        Pnmrdr_mapdata rdr_data = Pnmrdr_data(rdr);
        if (rdr_data.type != Pnmrdr_bit) {
                fprintf(stderr, "Input type is not a portable bitmap.\n");
                exit(1);
        }


        Bit2_T bitmap = populate_bitmap_with_rdr(rdr, rdr_data);
        remove_black_edges(bitmap);
        pbmwrite(stdout, bitmap);

        Bit2_free(&bitmap);
        Pnmrdr_free(&rdr);
        close_file(fp);
        exit(0);
}

void remove_black_edges(Bit2_T bitmap)
{
        Bit2_T *map_ptr = &bitmap;

        /* Calling dfs on black perimeter pixels */
        for (int row = 0; row < Bit2_height(bitmap); row++) {
                for (int col = 0; col < Bit2_width(bitmap); col++) {
                        if (verify_dfs_call(row, col, bitmap)) {
                                dfs(map_ptr, col, row);
                        }
                }
        }
}

void pbmwrite(FILE *outputfp, Bit2_T bitmap)
{
        bool long_line = false;
        int char_count = 0;
        if (Bit2_width(bitmap) > 70) {
                long_line = true;
        }
        fprintf(outputfp, "P1\n");
        fprintf(outputfp, "%d %d\n", Bit2_width(bitmap), Bit2_height(bitmap));
        for (int row = 0; row < Bit2_height(bitmap); row++) {
                for (int col = 0; col < Bit2_width(bitmap); col++) {
                        fprintf(outputfp, "%d", Bit2_get(bitmap, col, row));

                        if (long_line) {
                                char_count++;
                        }
                        if (char_count % 69 == 0 && col != 0 &&
                            long_line == true) {
                                fprintf(outputfp, "\n");
                        }
                }
                if (!long_line) {
                        fprintf(outputfp, "\n");
                }
        }
}

Bit2_T populate_bitmap_with_rdr(Pnmrdr_T rdr, Pnmrdr_mapdata rdr_data)
{
        unsigned cols = rdr_data.width;
        unsigned rows = rdr_data.height;
        assert(cols > 0 && rows > 0);

        unsigned pixel = 0;
        Bit2_T bitmap = Bit2_new(cols, rows);

        for (unsigned row = 0; row < rows; row++) {
                for (unsigned col = 0; col < cols; col++) {
                        pixel = Pnmrdr_get(rdr);
                        assert(pixel == 0 || pixel == 1);
                        Bit2_put(bitmap, col, row, pixel);
                }
        }
        return bitmap;
}
