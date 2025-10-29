SRCS = main.c tools.c events.c player.c draw_the_map.c ray_casting.c ray_casting_tools.c \
	horizontal_part_tools.c vertical_part_tools.c parsing/wolfnstein/config_check.c parsing/wolfnstein/get_line.c \
	parsing/wolfnstein/libc_utils.c parsing/wolfnstein/parser.c parsing/wolfnstein/utils.c
MLX_DIR = ./minilibx-linux
OBJS = ${SRCS:.c=.o}
CC = gcc
# CFLAGS = -Wall -Wextra -Werror -I/usr/include -I$(MLX_DIR) -O3
CFLAGS = -I/usr/include -I$(MLX_DIR) -O3
LDFLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

NAME = cub3d

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	@echo "Building MinilibX..."
	@cd $(MLX_DIR) && make -f Makefile all 2>/dev/null || \
	(cp Makefile.mk Makefile.gen && \
	 sed -i 's/%%%%/./' Makefile.gen && \
	 make -f Makefile.gen all)

$(NAME): $(MLX_DIR)/libmlx.a $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	make -C ./parsing/wolfnstein all

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C ./parsing/wolfnstein clean
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	make -C ./parsing/wolfnstein fclean
	@if [ -f $(MLX_DIR)/Makefile ]; then make -C $(MLX_DIR) clean; fi

re: fclean all
	make -C ./parsing/wolfnstein re

