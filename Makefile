OBJECTS = *.o
SRC = libft/*.c\
		src/elem.c\
		src/key.c\
		src/list_args.c\
		src/main.c\
		src/move/ft_move.c\
		src/move/help_move.c\
		src/output.c\
		src/term.c\
		src/error.c

FLAGS = -Wall -Wextra -Werror -lncurses
NAME = ft_select

all: $(NAME)

$(NAME):
	make -C libft/
	gcc $(FLAGS) $(SRC) -o $(NAME)

sanitize:
	gcc $(FLAGS) $(SRC) -o $(NAME)

lldb:
	gcc $(FLAGS) -g $(SRC)

cleanlldb:
	rm a.out
	rm -rf a.out.dSYM

runlldb:
	lldb ./a.out

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
 
