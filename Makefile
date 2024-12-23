NAME=cub3
CC=gcc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRC=$(wildcard *.c) \
    ./getnextline/get_next_line.c \
    ./getnextline/get_next_line_utils.c \
    ./lib/ft_split.c \
    ./lib/ft_substr.c \
    ./lib/ft_atoi.c
	
OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re