#include "../header/ft_select.h"

/*
**		Check if the key pressed is one of the arrows
*/

int 		is_move(long buf)
{
	if (buf == RIGHT_KEY || buf == LEFT_KEY ||
		buf == DOWN_KEY || buf == UP_KEY)
		return (1);
	return (0);
}

static void		move_side(t_term **terminal, char *str)
{
	t_select	*current;

	current = (*terminal)->list;
	while (current && current->cursor == 0)
		current = current->next;
	current->cursor = 0;
	if (ft_strcmp(str, "right") == 0)
		current->next->cursor = 1;
	else
		current->prev->cursor = 1;
}

static void		move_up(t_term **terminal)
{
	t_select	*current;
	int 		i;
	int 		j;

	j = -1;
	i = 0;
	current = (*terminal)->list;
	while (current && current->cursor == 0)
	{
		i++;
		current = current->next;
	}
	if ((i / get_col_size(*terminal)) >= 1)
	{
		current->cursor = 0;
		while (current && ++j < get_col_size(*terminal))
			current = current->prev;
		current->cursor = 1;
	}
}

static void		move_down(t_term **terminal)
{
	t_select	*current;
	int 		i;
	int 		j;

	j = -1;
	i = 0;
	current = (*terminal)->list;
	while (current && current->cursor == 0)
	{
		i++;
		current = current->next;
	}
	if ((i / get_col_size(*terminal)) >= 1) // Need to change this condition to see if it's in the last row instead
	{
		current->cursor = 0;
		while (current && ++j < get_col_size(*terminal))
			current = current->next;
		current->cursor = 1;
	}
}

/*
**		Handle cursor movement
*/

void		ft_move(long buf, t_term **terminal)
{
	if (buf == RIGHT_KEY)
		move_side(terminal, "right");
	else if (buf == LEFT_KEY)
		move_side(terminal, "left");
	else if (buf == DOWN_KEY)
		move_down(terminal);
	else if (buf == UP_KEY)
		move_up(terminal);
}