struct coordinates *create_stack_element(int, int);

struct coordinates {
	int row;
	int col;
};

struct coordinates* create_stack_element(int row, int col)
{
	struct coordinates *elem_p = malloc(sizeof(struct coordinates));
	elem_p->row = row;
	elem_p->col = col;
	return elem_p;
}