#include "iterators.h"

void	set_iterator(t_iterator *iterator, int head, int size, bool is_reverse)
{
	iterator->index = head;
	iterator->head = head;
	iterator->max_size = size;
	iterator->is_reverse = is_reverse;
	return ;
}

void	set_iter_head(t_iterator *iterator, int new_head)
{
	iterator->head = new_head;
	iterator->index = new_head;
	return ;
}

void	iterate(t_iterator *iterator)
{
	int	incrementer;

	iterator->prev_index = iterator->index;
	//-1 if direction == 1, +1 if direction == 0
	incrementer = iterator->is_reverse * -1 + !iterator->is_reverse * 1;
	iterator->index += incrementer;
	if (incrementer == 1 && iterator->index > iterator->max_size - 1)
		iterator->index = 0;
	else if (incrementer == -1 && iterator->index < 0)
		iterator->index = iterator->max_size - 1 * (iterator->max_size != 0);
	return ;
}

void	iterate_once(t_iterator *iterator, bool is_reverse)
{
	iterator->is_reverse = is_reverse;
	iterate(iterator);
	return ;
}

//Will return true as long as it hasn't finished a full loop
bool	iterate_one_loop(t_iterator *iterator)
{
	int			incrementer;
	static bool	passed_go;

	if (passed_go == false)
	{
		passed_go = true;
		iterator->index = iterator->head;
	}
	else if (iterator->index == iterator->head)
	{
		passed_go = false;
		return (false);
	}
	iterator->prev_index = iterator->index;
	//-1 if direction == 1, +1 if direction == 0
	incrementer = iterator->is_reverse * -1 + !iterator->is_reverse * 1;
	iterator->index += incrementer;
	if (iterator->index >= iterator->max_size)
		iterator->index = 0;
	else if (iterator->index < 0)
		iterator->index = iterator->max_size - 1 * (iterator->max_size != 0);
	return (true);
}
