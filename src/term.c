/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:53:30 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/26 22:53:30 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_select.h"

/*
**		Activates the terminal we'll use for the program 
*/

void		terminal_on(t_term *terminal)
{
	terminal->new_term.c_lflag &= ~(ICANON); // Disable canonical mode
	terminal->new_term.c_lflag &= ~(ECHO); // Disable echoing
	terminal->new_term.c_cc[VMIN] = 1; // read every 1 char ??
	terminal->new_term.c_cc[VTIME] = 100; // ouput read request every 100 tenth of seconds ??
	tcsetattr(0, TCSADRAIN, &terminal->new_term); // Validate the changes and updates the terminal
	tputs(tgetstr("vi", NULL), 0, ft_putint);
	tputs(tgetstr("ti", NULL), 0, ft_putint);
}

/*
**		Puts terminal back to normal
*/

void			terminal_off(t_term *terminal)
{
	tputs(tgetstr("cl", NULL), 1, ft_putint);
	tcsetattr(0, TCSADRAIN, &terminal->old_term);
	tputs(tgetstr("ve", NULL), 0, ft_putint);
	tputs(tgetstr("te", NULL), 0, ft_putint);
	// ft_free_memory();
}

/*
**		Gets the terminal informations
*/

void		get_terminal(void)
{
	struct termios  termios;
	struct termios  old_termios;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &old_termios);
	tcgetattr(0, &termios);
	g_terminal->old_term = old_termios;
	g_terminal->new_term = termios;
	g_terminal->nb_chr = longest_word(g_terminal->list);
	ioctl(STDERR_FILENO, TIOCGWINSZ, &g_terminal->win_size);
	terminal_on(g_terminal);
}

void		ft_free_memory()
{
	t_select	*tmp;

	if (g_terminal->list)
	{
		while (g_terminal->list)
		{
			tmp = g_terminal->list;
			g_terminal->list = g_terminal->list->next;
			if (tmp->output)
				ft_strdel(&tmp->output);
			free(tmp);
			tmp = NULL;
		}
	}
	if (g_terminal)
		free(g_terminal);
	g_terminal = NULL;
}

/*
**		Quits the terminal properly
*/

void		ft_quit(int signal)
{
	(void)signal;
	terminal_off(g_terminal);
	exit(0);
}
