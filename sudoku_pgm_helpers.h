#include <stdio.h>
#include <stdlib.h>
#include <uarray2.h>
#include <pnmrdr.h>

#define BOARD_WIDTH 9
#define SECTION_WIDTH 3

UArray2_T populate_array_from_pgm(Pnmrdr_T, Pnmrdr_mapdata);
void finish_reading_pgm(Pnmrdr_T, Pnmrdr_mapdata);

UArray2_T populate_array_from_pgm(Pnmrdr_T rdr, Pnmrdr_mapdata rdr_data)
{
	unsigned dim = rdr_data.width;

	unsigned pixel = 0;
	void *val = NULL;
	UArray2_T sudoku_board = UArray2_new(dim, dim, sizeof(unsigned));

	for (unsigned row = 0; row < dim; row++) {
		for (unsigned col = 0; col < dim; col++) {
			pixel = Pnmrdr_get(rdr);
			val = UArray2_at(sudoku_board, row, col);
			*(int *) val = pixel;
		}
	}
	finish_reading_pgm(rdr, rdr_data);
	return sudoku_board;
}


/* The purpose of this function is to avoid aborting when freeing the pnmrdr in
	the case that the width is 9 and the height is greater
	than 9.
*/
void finish_reading_pgm(Pnmrdr_T rdr, Pnmrdr_mapdata rdr_data)
{
	int num_pixels_in_board = BOARD_WIDTH * BOARD_WIDTH;
	int pixels_remaining = (rdr_data.height * rdr_data.width) - 
				num_pixels_in_board;

	while (pixels_remaining != 0) {
		int temp_val = Pnmrdr_get(rdr);
		pixels_remaining--;
		(void) temp_val;
	}
}
