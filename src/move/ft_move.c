/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arnaud <Arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:53:16 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/28 19:11:00 by Arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/ft_select.h"

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
	(void)terminal;
	t_select	*current;
	int 		i;

	i = 0;
	current = find_cursor(&i);
	if ((i / g_terminal->max_col) == 0 || i == g_terminal->max_col)
		help_move_up(0, i, 0, current);
	else
		help_move_up(1, i, 0, current);
}

static void		move_down(t_term **terminal)
{
	t_select	*current;
	int 		i;

	(void)terminal;
	i = 0;
	current = find_cursor(&i);
	if (((i / g_terminal->max_col) == g_terminal->max_row - 1)
		|| (((i / g_terminal->max_col) == g_terminal->max_row)
			&& i % g_terminal->max_col == 0))
		help_move_down(0, i, -1, current);
	else if ((i / g_terminal->max_col) == g_terminal->max_row)
		help_move_down(1, i, -1, current);
	else
		help_move_down(2, i, -1, current);
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
