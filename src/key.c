/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:52:50 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/26 22:52:51 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_select.h"

/*
**		Reads from STDIN to receive the informations about the key pressed
*/

void		receive_key(t_term **terminal)
{
	int		buf;

	buf = 0;
	read(0, &buf, 4);
	if (buf == ESC_KEY)
		ft_quit(0);
	else if (is_move(buf))
		ft_move(buf, terminal);
	else if (buf == SPACE_KEY)
		select_elem(terminal);
	else if (buf == ENTER)
		output_and_quit(terminal);
	else if (buf == DEL_KEY || buf == BACKSPACE)
		erase_elem(&g_terminal);
}
