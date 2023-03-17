NAME = philo

SRC = philo.c ft_atoi.c parse_args.c handle_mutexes_and_threads.c routine.c helper_functions.c

OSRC = $(SRC:%.c=%.o)

WWW = -Wall -Wextra -Werror -g

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OSRC)
	cc $(WWW) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC)

fclean: clean
	rm -f $(NAME)

%.o: %.c
	cc $(WWW) -c -o $@ $^

re: fclean all
