CC = cc
CFLAGS = -Werror -Wextra -Wall -pthread
SRC = ${wildcard *.c}
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
