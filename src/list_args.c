/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:53:00 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/26 22:53:00 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_select.h"

/*
**		Get the list of arguments and store them in the structure t_select which is
**		stored in the structure t_term
*/

void			get_list(char **argv)
{
	int 		i;
	t_select	*elem;

	i = 1;
	elem = new_elem();
	while (argv[i])
	{
		if (ft_strlen(elem->output) == 0)
		{
			elem->output = ft_strdup(argv[i]);
			elem->next = NULL;
			elem->prev = NULL;
			elem->selected = 0;
			elem->cursor = 1;
		}
		else
			add_new_elem(&elem, argv[i]);
		i++;
	}
	g_terminal->list = elem;
}

int 		size_list(t_select *head)
{
	t_select	*current;
	int 		count;

	count = 0;
	current = head;
	while (current && current->next != head && count++)
		current = current->next;
	return (count);
}

int 		longest_word(t_select *head)
{
	t_select	*current;
	int 		max;

	max = 0;
	current = head;
	while (current)
	{
		if (max < (int)ft_strlen(current->output))
			max = ft_strlen(current->output);
		if (current->next == head)
			break ;
		current = current->next;
	}
	return (max);
}

int 		get_col_size(t_term *terminal)
{
	int 	col;

	if (!(terminal->list->output))
		ft_quit(0);
	ioctl(STDERR_FILENO, TIOCGWINSZ, &terminal->win_size);
	col = terminal->win_size.ws_col / (longest_word(terminal->list) + 1);
	if (!col)
		col = 1;
	if (col < size_list(terminal->list))
		col = size_list(terminal->list);
	return (col);
}
