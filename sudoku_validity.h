#include <stdlib.h>
#include <uarray2.h>

#define BOARD_WIDTH 9
#define SECTION_WIDTH 3

bool verify_all_squares(UArray2_T, struct Closure *);
bool verify_section(UArray2_T, int, int, bool);
void verify_linear_path(int, int, UArray2_T, void *, void *);
void falsify_val_array(bool *, int size);

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
