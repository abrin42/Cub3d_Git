SRC_C	=	cub3d.c									\
			parsing/get_map.c						\
			utils/utils.c							\
			utils/get_next_line.c					\
			raycasting/display.c

LIBX = minilibx-linux/libmlx_Linux.a -lXext -lX11

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
