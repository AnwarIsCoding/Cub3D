SRCS = rendering/main.c rendering/tools.c rendering/events.c rendering/player.c rendering/draw_the_map.c rendering/ray_casting.c rendering/ray_casting_tools.c rendering/tools2.c \
	rendering/horizontal_part_tools.c rendering/vertical_part_tools.c parsing/config_check.c parsing/get_line.c \
	parsing/parser.c parsing/utils.c parsing/utils2.c parsing/utils3.c parsing/utils4.c parsing/utils5.c rendering/textures.c parsing/libft_garb_collect/ft_atoi.c \
       parsing/libft_garb_collect/ft_strdup_g.c \
       parsing/libft_garb_collect/ft_strjoin_g.c \
       parsing/libft_garb_collect/ft_substr_g.c \
       parsing/libft_garb_collect/garb_coll_init.c \
       parsing/libft_garb_collect/garb_coll_clear.c \
       parsing/libft_garb_collect/ft_strlen.c \
       parsing/libft_garb_collect/ft_strcmp.c \
       parsing/libft_garb_collect/ft_strncmp.c \
       parsing/libft_garb_collect/ft_strchr.c \
       parsing/libft_garb_collect/ft_memcpy.c \
       parsing/libft_garb_collect/ft_bzero.c
MLX_DIR = ./minilibx-linux
OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -Wall -Wextra -Werror -I/usr/include -I$(MLX_DIR) -O3
LDFLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

NAME = cub3D

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	@$(MAKE) -C $(MLX_DIR) --no-print-directory > /dev/null

$(NAME): $(MLX_DIR)/libmlx.a $(OBJS)
	$(CC) -fsanitize=address $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c cub3d.h parsing/cube.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean; fi

re: fclean all

