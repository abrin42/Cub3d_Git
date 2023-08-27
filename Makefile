SRC_C	=	cub3d.c									\
			init.c									\
			parsing/get_map.c						\
			parsing/check_border.c					\
			parsing/check_error.c					\
			parsing/flood_fill.c					\
			parsing/malloc_map.c					\
			parsing/copy_map.c						\
			parsing/set_texture.c					\
			utils/utils.c							\
			utils/utils2.c							\
			utils/get_next_line.c					\
			raycasting/display.c					\
			raycasting/setup.c						\
			raycasting/step.c						\
			mlx_key/mlx_key.c						\

LIBX = minilibx-linux/libmlx_Linux.a -lXext -lX11 -lm

OBJS	=	${SRC_C:.c=.o}

LIBGCDIR = gc
LIBGC = libgc.a
LIBGCFLAGS = -L $(LIBGCDIR) -l:$(LIBGC)

NAME	=	cub3d

CFLAGS	= -Wall -Wextra -Werror -g3

CC	=	gcc

all : ${NAME}

$(LIBGCDIR)/$(LIBGC):
	make -C $(LIBGCDIR)

$(NAME): $(OBJS) $(LIBGCDIR)/$(LIBGC)
	$(CC) $(CFLAGS) $(OBJS) $(LIBX) $(LIBGCFLAGS) -o $(NAME)

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}
	make -C ${LIBGCDIR} fclean

re : fclean all

.PHONY: all fclean clean re
