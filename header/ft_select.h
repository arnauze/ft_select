#ifndef FT_SELECT_H
# define FT_SELECT_H

#include "../libft/libft.h"
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <signal.h>
#include <sys/ioctl.h>

typedef struct 			s_select
{
	struct s_select		*next;
	struct s_select		*prev;
	char				*output;
	int					selected;
	int					cursor;
}						t_select;

typedef	struct			s_term
{
	struct termios		old_term;
	struct termios		new_term;
	struct winsize		win_size;
	t_select			*list;
	int					max_col;
	int					max_row;
	int					argc;
	int					nb_chr;
}						t_term;

# define ENTER					10
# define ESC_KEY				27
# define SPACE_KEY				32
# define LEFT_KEY				4479771
# define UP_KEY					4283163
# define RIGHT_KEY				4414235
# define DOWN_KEY				4348699
# define DEL_KEY				2117294875
# define BACKSPACE				127
# define O_KEY					111

t_term			*g_terminal;

int				ft_putint(int c);

/*
**		error.c
*/

int				ft_error(char *str);

/*
**		move/ft_move.c
*/

void			ft_move(long buf, t_term **terminal);
int 			is_move(long buf);

/*
**		move/help_move.c
*/

void			help_move_down(int x, int i, int j, t_select *current);
void			help_move_up(int x, int i, int j, t_select *current);
t_select		*find_cursor(int *i);

/*
**		key.c
*/

void			receive_key(t_term **terminal);


/*
**		list_args.c
*/

void			get_list(char **argv);
int 			size_list(t_select *head);
int 			longest_word(t_select *head);
int 			get_col_size(void);

/*
**		output.c
*/

void			print_list(t_term *terminal);
void			output_and_quit(t_term **terminal);

/*
**		term.c
*/

void			terminal_on(t_term *terminal);
void			terminal_off(t_term *terminal);
void			get_terminal(void);
void			ft_quit(int signal);
void			ft_free_memory();

/*
**		elem.c
*/

void			select_elem(t_term **terminal);
void			erase_elem(t_term **terminal);
t_select		*new_elem(void);
void			add_new_elem(t_select **head, char *name);


#endif
