/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:53:16 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/26 22:53:16 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	j = 0;
	i = 1;
	current = (*terminal)->list;
	while (current && current->cursor == 0)
	{
		i++;
		current = current->next;
	}
	if ((i / g_terminal->max_col) == 0)
	{
		current->cursor = 0;
		if (i % g_terminal->max_col >= g_terminal->argc % g_terminal->max_col)
			while (current && ++j <= g_terminal->max_col + (g_terminal->argc % g_terminal->max_col))
				current = current->prev;
		else
			while (current && ++j <= g_terminal->max_col - (g_terminal->argc % g_terminal->max_col))
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

static void		move_down(t_term **terminal)
{
	t_select	*current;
	int 		i;
	int 		j;

	j = -1;
	i = 1;
	current = (*terminal)->list;
	while (current && current->cursor == 0)
	{
		i++;
		current = current->next;
	}
	if ((((i / g_terminal->max_col) != g_terminal->max_row)) && (((i / g_terminal->max_col) != g_terminal->max_row - 1)))
	{
		current->cursor = 0;
		while (current && ++j < g_terminal->max_col)
			current = current->next;
		current->cursor = 1;
	}
	else if (((i / g_terminal->max_col) == g_terminal->max_row - 1))
	{
		current->cursor = 0;
		if (i % g_terminal->max_col >= g_terminal->argc % g_terminal->max_col)
			while (current && ++j < g_terminal->max_col + (g_terminal->argc % g_terminal->max_col))
				current = current->next;
		else
			while (current && ++j < g_terminal->max_col)
			current = current->next;
		current->cursor = 1;
	}
	else
	{
		current->cursor = 0;
		while (current && ++j <= g_terminal->max_col - (g_terminal->argc % g_terminal->max_col))
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
