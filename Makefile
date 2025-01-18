NAME=cub3D
CC=gcc 
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
MLX = ~/MLX42
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
NC=\033[0m

HEADERS	= -I ./include -I $(MLX)/include
LIBS	= $(MLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
HEADER = cub3.h

SRC = cub3.c \
	./config/check_map.c \
	./config/check.c\
	./config/FC.c\
	./config/fill_map.c\
	./config/free.c\
	./config/init.c\
	./config/is_valid.c\
	./config/map_lines.c\
	./config/parse.c\
	./config/print.c\
	./config/read_map.c\
	./config/textures.c\
	./raycasting/raycast.c \
	./raycasting/cast_ray.c \
	./raycasting/renders.c \
	./raycasting/utils.c \
	./raycasting/drawing.c \
    ./getnextline/get_next_line.c \
    ./getnextline/get_next_line_utils.c \
    ./lib/ft_split.c \
    ./lib/ft_substr.c \
    ./lib/ft_atoi.c \
    ./lib/skip_space.c \
    ./lib/ft_putstr.c \
    ./lib/substring.c \
	./lib/subtring2.c\
	./lib/trime.c \

OBJ_DIR = objs/

OBJ=$(addprefix $(OBJ_DIR),  $(SRC:.c=.o))

all: libmlx $(NAME)

libmlx:
	@cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4

$(OBJ_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)


$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling C objects...$(NC)"
	@$(CC) $(CFLAGS) $(LIBS) $(OBJ) $(HEADERS) -o $(NAME)

clean: 
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	rm -rf $(MLX)/build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re