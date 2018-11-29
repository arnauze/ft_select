/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arnaud <Arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:52:36 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/28 19:21:43 by Arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_select.h"

/*
**		Select an element in the list of arguments by changing its value from 0 to 1
**		or 1 to 0, then move the cursor to the next argument in the list.
*/

void		select_elem(t_term **terminal)
{
	t_select	*current;

	current = (*terminal)->list;
	while (current && current->cursor == 0)
		current = current->next;
	current->selected = (current->selected) ?  0 : 1;
	current->cursor = 0;
	current->next->cursor = 1;
}

/*
**		Erase the element from the list (Doesn't work)
*/

void		erase_elem(t_term **terminal)
{
	t_select	*current;

	if (!(current = (*terminal)->list))
		ft_quit(0);
	if (current->cursor)
	{
		if (current->next)
			(*terminal)->list = current->next;
		else
			ft_quit(0);
	}
	while (current && !current->cursor)
		current = current->next;
	current->prev->next = current->next;
	current->next->prev = current->prev;
	current->next->cursor = 1; // This segfaults when no next
	ft_strdel(&current->output);
	free(current);
	current = NULL;
}

/*
**		Creates a new element of the list and initialize its values at 0
*/

t_select		*new_elem(void)
{
	t_select	*new;

	new = (t_select *)malloc(sizeof(t_select));
	new->output = ft_strnew(0);
	new->selected = 0;
	new->cursor = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/*
**		Add a new element in the structure t_select
*/

void			add_new_elem(t_select **head, char *name)
{
	t_select	*first;
	t_select	*elem;
	t_select	*new;

	new = (t_select *)malloc(sizeof(t_select));
	first = *head;
	elem = *head;
	while (elem->next && elem->next != first)
		elem = elem->next;
	new->output = ft_strdup(name);
	new->selected = 0;
	new->cursor = 0;
	new->next = first;
	new->prev = elem;
	first->prev = new;
	elem->next = new;
}
