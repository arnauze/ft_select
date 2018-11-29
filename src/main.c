/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:53:09 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/26 22:53:10 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/ft_select.h"

t_term		*g_terminal;

/*
**		Acts like a ft_putchar but needed for the tputs function
*/

int			ft_putint(int c)
{
	ft_putchar((char)c);
	return (0);
}

static int		get_size(void)
{
	ioctl(STDERR_FILENO, TIOCGWINSZ, &g_terminal->win_size);
	g_terminal->max_col = get_col_size();
	g_terminal->max_row = g_terminal->win_size.ws_row;
	if ((g_terminal->argc / g_terminal->max_col) >= g_terminal->max_row)
		return (-1);
	g_terminal->max_row = (g_terminal->argc / g_terminal->max_col);
	return (0);
}

static void		signal_handler(int sig)
{
	if (sig == SIGTSTP)
		ft_quit(0);
	else if (sig == SIGINT || sig == SIGABRT || sig == SIGSTOP || sig == SIGKILL || sig == SIGQUIT)
		ft_quit(0);
	if (sig == SIGWINCH)
	{
		tputs(tgetstr("cl", NULL), 0, ft_putint);
		if (get_size() == -1)
			ft_error("SPACE");
		else
			print_list(g_terminal);
	}

}

static void		initialize_signals(void)
{
	signal(SIGTSTP, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGKILL, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGWINCH, signal_handler);
}

/*
**		Cursor movement is weird
*/

int			main(int argc, char **argv)
{
	if (argc == 1)
		return(ft_error("USAGE"));
	g_terminal = (t_term *)malloc(sizeof(t_term));
	get_terminal();
	get_list(argv);
	initialize_signals();
	while (1)
	{
		tputs(tgetstr("cl", NULL), 0, ft_putint);
		if (get_size() == 0)
		{
			print_list(g_terminal);
			receive_key(&g_terminal);
		}
	}
	terminal_off(g_terminal);
	return (0);
}
