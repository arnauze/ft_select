#include "../../header/ft_select.h"

void			help_move_down(int x, int i, int j, t_select *current)
{
	if (x == 0)
	{
		current->cursor = 0;
		if ((i % g_terminal->max_col > g_terminal->argc % g_terminal->max_col) || (i % g_terminal->max_col == 0))
			while (current && ++j < g_terminal->max_col + (g_terminal->argc % g_terminal->max_col))
				current = current->next;
		else
			while (current && ++j < g_terminal->max_col)
				current = current->next;
		current->cursor = 1;
	}
	else if (x == 1)
	{
		current->cursor = 0;
		while (current && ++j < g_terminal->argc % g_terminal->max_col)
			current = current->next;
		current->cursor = 1;
	}
	else
	{
		current->cursor = 0;
		while (current && ++j < g_terminal->max_col)
			current = current->next;
		current->cursor = 1;	
	}
}

void			help_move_up(int x, int i, int j, t_select *current)
{
	if (x == 0)
	{
		current->cursor = 0;
		if (i > (g_terminal->argc % g_terminal->max_col))
			while (current && ++j <= g_terminal->max_col + (g_terminal->argc % g_terminal->max_col))
				current = current->prev;
		else
			while (current && ++j <= g_terminal->argc % g_terminal->max_col)
				current = current->prev;
		current->cursor = 1;
	}
	else
	{
		current->cursor = 0;
		while (current && ++j <= g_terminal->max_col)
			current = current->prev;
		current->cursor = 1;
	}
}

t_select		*find_cursor(int *i)
{
	t_select	*current;

	if (!i)
	{
		i = (int*)malloc(sizeof(int));
		*i = 0;
	}
	current = g_terminal->list;
	while (current)
	{
		*i = *i + 1;
		if (current->cursor == 1)
			break ;
		current = current->next;
	}
	return (current);
}
