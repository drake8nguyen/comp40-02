/*
* dfs.c
* COMP 40 - Homework 2
* Nick Daigler & Minh Duc Nguyen
* September 25thth, 2018
*/

#include <bit2.h>
#include <seq.h>
#include <unblack_coords.h>

void dfs(Bit2_T *, int, int);
bool verify_dfs_call(int, int, Bit2_T);

void dfs(Bit2_T *bitmap, int col, int row)
{
	struct coordinates *coordinate = malloc(sizeof(struct coordinates));
	coordinate->row = row;
	coordinate->col = col;

	Seq_T stack = Seq_new(0);
	Seq_addlo(stack, coordinate);

	struct coordinates *top;
	
	while (Seq_length(stack) > 0) {
		top = (struct coordinates *) Seq_remlo(stack);

		int row = top->row;
		int col = top->col;

		if (Bit2_get(*bitmap, col, row) == 1) {
			Bit2_put(*bitmap, col, row, 0);
			free(top);
		} else  {
			free(top);
			continue;
		}

		if (row + 1 < Bit2_height(*bitmap) && 
		    Bit2_get(*bitmap, col, row + 1) == 1) {
			top = create_stack_element(row + 1, col);
			Seq_addlo(stack, top);
		}
		if (col - 1 >= 0 && Bit2_get(*bitmap, col - 1, row) == 1) {
			top = create_stack_element(row, col - 1);
			Seq_addlo(stack, top);
		}
		if (row - 1 >= 0 && Bit2_get(*bitmap, col, row - 1) == 1) {
			top = create_stack_element(row - 1, col);
			Seq_addlo(stack, top);
		}
		if (col + 1 < Bit2_width(*bitmap) && 
		    Bit2_get(*bitmap, col + 1, row) == 1) {
			top = create_stack_element(row, col + 1);
			Seq_addlo(stack, top);
		}

	}

	Seq_free(&stack);
}

bool verify_dfs_call(int row, int col, Bit2_T bitmap)
{
	return ((row == 0 || row == Bit2_height(bitmap) - 1 || 
		 	 col == 0 || col == Bit2_width(bitmap) - 1) &&
	         Bit2_get(bitmap, col, row) == 1);
}
