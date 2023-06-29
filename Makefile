CC = cc
CFLAGS = -Werror -Wextra -Wall -pthread
SRC = ${wildcard *.c}
OBJ = ${SRC:.c=.o}

Name = philo

all: $(Name)

$(Name): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME)

clean:
	@-rm -f $(OBJ)

flcean: clean
	@-rm -f $(NAME)

re: fclean all
