NAME=cub3D
NAME_BNS = cub3D_bonus
CC=gcc 
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
MLX = ~/MLX42
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
NC=\033[0m

HEADERS	= -I ./include -I $(MLX)/include
LIBS	= $(MLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
HEADER = ./mandatory/cub3.h
HEADER_BNS = ./bonus/cub3_bonus.h

SRC = ./mandatory/cub3.c \
	./mandatory/config/utils.c \
	./mandatory/raycasting/tex_utils.c \
	./mandatory/raycasting/tex_util.c \
	./mandatory/raycasting/texture.c \
	./mandatory/config/check_map.c \
	./mandatory/config/check.c\
	./mandatory/config/FC.c\
	./mandatory/config/fill_map.c\
	./mandatory/config/free.c\
	./mandatory/config/init.c\
	./mandatory/config/is_valid.c\
	./mandatory/config/map_lines.c\
	./mandatory/config/parse.c\
	./mandatory/config/print.c\
	./mandatory/config/read_map.c\
	./mandatory/config/textures.c\
	./mandatory/raycasting/raycast.c \
	./mandatory/raycasting/cast_ray.c \
	./mandatory/raycasting/utils.c \
	./mandatory/raycasting/keys.c \
	./mandatory/raycasting/utils2.c \
	./mandatory/raycasting/init.c \
    ./mandatory/getnextline/get_next_line.c \
    ./mandatory/getnextline/get_next_line_utils.c \
    ./mandatory/lib/ft_split.c \
    ./mandatory/lib/ft_substr.c \
    ./mandatory/lib/ft_atoi.c \
    ./mandatory/lib/skip_space.c \
    ./mandatory/lib/ft_putstr.c \
    ./mandatory/lib/substring.c \
	./mandatory/lib/subtring2.c\
	./mandatory/lib/trime.c \
	./mandatory/lib/ft_isdigit.c \

SRC_BNS = ./bonus/cub3_bonus.c \
		./bonus/config_bonus/utils.c \
		./bonus/raycasting_bonus/tex_utils.c \
		./bonus/raycasting_bonus/tex_util.c \
		./bonus/raycasting_bonus/texture.c \
		./bonus/config_bonus/check_map.c \
		./bonus/config_bonus/check.c\
		./bonus/config_bonus/FC.c\
		./bonus/config_bonus/fill_map.c\
		./bonus/config_bonus/free.c\
		./bonus/config_bonus/init.c\
		./bonus/config_bonus/is_valid.c\
		./bonus/config_bonus/map_lines.c\
		./bonus/config_bonus/parse.c\
		./bonus/config_bonus/print.c\
		./bonus/config_bonus/read_map.c\
		./bonus/config_bonus/textures.c\
		./bonus/raycasting_bonus/raycast.c \
		./bonus/raycasting_bonus/cast_ray.c \
		./bonus/raycasting_bonus/utils.c \
		./bonus/raycasting_bonus/keys.c \
		./bonus/raycasting_bonus/utils2.c \
		./bonus/raycasting_bonus/init.c \
		./bonus/raycasting_bonus/renders.c \
		./bonus/raycasting_bonus/animation.c \
    	./bonus/getnextline_bonus/get_next_line.c \
    	./bonus/getnextline_bonus/get_next_line_utils.c \
    	./bonus/lib_bonus/ft_split.c \
    	./bonus/lib_bonus/ft_substr.c \
    	./bonus/lib_bonus/ft_atoi.c \
    	./bonus/lib_bonus/skip_space.c \
    	./bonus/lib_bonus/ft_putstr.c \
    	./bonus/lib_bonus/substring.c \
		./bonus/lib_bonus/subtring2.c\
		./bonus/lib_bonus/trime.c \
		./bonus/lib_bonus/ft_isdigit.c \

OBJ_DIR = objs/
OBJ_BNS_DIR = objs_bns/

OBJ=$(addprefix $(OBJ_DIR),  $(SRC:.c=.o))
OBJ_BNS=$(addprefix $(OBJ_BNS_DIR), $(SRC_BNS:.c=.o))

all: libmlx $(NAME)

libmlx:
	@cmake $(MLX) -B $(MLX)/build && make -C $(MLX)/build -j4

$(OBJ_DIR)%.o: %.c $(HEADER)
	@echo "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(OBJ_BNS_DIR)%.o: %.c $(HEADER_BNS)
	@echo "$(GREEN)Compiling $<...$(NC)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)


$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(LIBS) $(OBJ) $(HEADERS) -o $(NAME)

$(NAME_BNS): $(OBJ_BNS)
	@echo "$(YELLOW)Compiling $(NAME_BNS)...$(NC)"
	@$(CC) $(CFLAGS) $(LIBS) $(OBJ_BNS) $(HEADERS) -o $(NAME_BNS)

bonus: libmlx $(NAME_BNS)

clean: 
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BNS_DIR)
	rm -rf $(MLX)/build

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_BNS)

re: fclean all

.PHONY: all clean fclean re bonus