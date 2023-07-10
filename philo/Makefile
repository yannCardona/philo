CC = cc
CFLAGS = -Werror -Wextra -Wall -pthread
SRC = ft_atoi.c helpers.c init.c routine.c main.c
OBJ = ${SRC:.c=.o}

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	@-rm -f $(OBJ)

fclean: clean
	@-rm -f $(NAME)

re: fclean all
