/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:53:23 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/26 22:53:24 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_select.h"

static void		output_current(t_select *current, t_term *terminal)
{
	int 		i;

	i = 0;
	while (current->output[i])
	{
		ft_putchar_fd(current->output[i], 2);
		i++;
	}
	if (current->selected)
		tputs(tgetstr("me", NULL), 0, ft_putint);
	if (current->cursor)
		tputs(tgetstr("ue", NULL), 0, ft_putint);
	while (i < longest_word(terminal->list))
	{
		ft_putchar_fd(' ', 2);
		i++;
	}
}

/*
**		Print the list or arguments
*/

void			print_list(t_term *terminal)
{
	t_select	*current;
	t_select	*first;
	int 		i;
	int	j = 1;
	t_select *bite;

	first = terminal->list;
	current = terminal->list;
	//
	bite = first;
	while (bite && bite->cursor != 1)
	{
		bite = bite->next;
		j++;
	}
	ft_putnbr(j % g_terminal->max_col); //pb when last col becquse return 0
	ft_putchar_fd('\n', 2);
	// 
	ft_putnbr(g_terminal->argc % g_terminal->max_col);
	ft_putchar_fd('\n', 2);
	while (current)
	{
		i = 0;
		while (current && i < g_terminal->max_col)
		{
			if (current->selected)
				tputs(tgetstr("mr", NULL), 0, ft_putint);
			if (current->cursor)
				tputs(tgetstr("us", NULL), 0, ft_putint);
			output_current(current, g_terminal);
			current = current->next;
			if (current == first)
				break ;
			ft_putchar_fd(' ', 2);
			i++;
		}
		ft_putchar_fd('\n', 2);
		if (current == first)
				break ;
	}
}

void			output_and_quit(t_term **terminal)
{
	t_select	*current;
	t_select	*first;

	current = (*terminal)->list;
	first = (*terminal)->list;
	terminal_off(*terminal);
	while (current)
	{
		if (current->selected)
			ft_putstr(current->output);
		if (current->next == first)
			break ;
		if (current->selected)
			ft_putchar(' ');
		current = current->next;
	}
	ft_putchar('\n');
	exit(0);
}
