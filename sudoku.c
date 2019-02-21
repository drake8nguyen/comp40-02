/*
* sudoku.c
* COMP 40 - Homework 2
* Nick Daigler & Minh Duc Nguyen
* September 17th, 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pnmrdr.h>
#include <stdbool.h>
#include <uarray2.h>
#include <file_io.h>
#include <set.h>
#include <sudoku_pgm_helpers.h>

#define BOARD_WIDTH 9
#define SECTION_WIDTH 3

struct Closure {
        bool valid;
        bool val_array[BOARD_WIDTH];
};

void falsify_val_array(bool *, int size);
bool verify_all_squares(UArray2_T, struct Closure *);
bool verify_section(UArray2_T, int, int, bool);
void verify_linear_path(int, int, UArray2_T, void *, void *);

int main(int argc, char **argv) 
{
        if (argc > 2) {
                exit(1);
        }

        char *file_name = argv[1];
        FILE *fp = open_file(file_name);

        Pnmrdr_T rdr = Pnmrdr_new(fp);
        Pnmrdr_mapdata rdr_data = Pnmrdr_data(rdr);
        assert(rdr_data.type == Pnmrdr_gray);
        assert(rdr_data.height != 0);
        assert(rdr_data.width == 9 && rdr_data.width != 0);

        UArray2_T sudoku_board = populate_array_from_pgm(rdr, rdr_data);

        struct Closure cl;
        cl.valid = true;
        bool *array_p = cl.val_array;
        falsify_val_array(array_p, 9);

        UArray2_map_col_major(sudoku_board, verify_linear_path, &cl);
        UArray2_map_row_major(sudoku_board, verify_linear_path, &cl);
        cl.valid = verify_all_squares(sudoku_board, &cl);

        close_file(fp);
        UArray2_free(&sudoku_board);
        Pnmrdr_free(&rdr);

        cl.valid == 1 ? exit(0) : exit(1);
}

void falsify_val_array(bool *val_array, int size)
{
        for (int i = 0; i < size; i++) {
                *(val_array + i) = false;
        }
}

bool verify_all_squares(UArray2_T array, struct Closure *cl)
{
        for (int row = 0; row < UArray2_width(array); row += SECTION_WIDTH) {
                for (int col = 0; col < UArray2_height(array); 
                     col += SECTION_WIDTH) {
                        cl->valid = verify_section(array, row, col, cl->valid);
                }
        }
        return cl->valid;
}

bool verify_section(UArray2_T array, int row, int col, bool is_board_valid) 
{
        unsigned square_dim = SECTION_WIDTH;

        bool valid[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (unsigned i = row; i < row + square_dim; i++) {
                for (unsigned j = col; j < col + square_dim; j++) {
                        void *temp_val = UArray2_at(array, i, j);
                        if (*(int *)temp_val <= 0 || 
                            *(int *)temp_val > BOARD_WIDTH) {
                                is_board_valid = false;
                                return is_board_valid;
                        }
                        if (valid[(*(int *) temp_val) - 1]) {
                                is_board_valid = false;
                        } else {
                                valid[*(int *) temp_val-1] = 1;
                        }
                }
        }
        return is_board_valid;
}

void verify_linear_path(int row, int col, UArray2_T array, void *val, void *cl)
{
        (void) row;
        (void) col;
        (void) array;

        struct Closure *cl_p = cl;
        unsigned *board_val = val;
        unsigned full_array_count = 0;

        if (*board_val < 1 || *board_val > 9) {
                cl_p->valid = false;
                return;
        }

        for (int i = 0; i < 9; i++) {
                if ((*cl_p).val_array[i] == true) {
                        full_array_count++;
                }
        }

        if (full_array_count == 9) {
                falsify_val_array(cl_p->val_array, 9);
        }

        if ((*cl_p).val_array[*board_val - 1] == true && 
            full_array_count < 9) {
                (*cl_p).valid = false;
        } else {
                (*cl_p).val_array[*board_val - 1] = true;
        }
}
