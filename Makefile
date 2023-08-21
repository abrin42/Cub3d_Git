
SRCS	=	cub3d.c									\
			parsing/get_map.c						\
			utils/utils.c							\
			utils/get_next_line.c					\

SRC_H = cub3d.h

LIBGCDIR = gc
LIBGC = libgc.a
LIBGCFLAGS = -L $(LIBGCDIR) -l:$(LIBGC)

OBJS	=	${SRC:.c=.o}

NAME	=	cub3d

CFLAGS	=	-g3 #-fsanitize=adresse
# CFLAGS	=	-Wall -Wextra -Werror -g3 #-fsanitize=adresse

all : ${NAME}

$(LIBGCDIR)/$(LIBGC):
	make -C $(LIBGCDIR)

$(NAME): $(SRCS) $(LIBGCDIR)/$(LIBGC)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBGCFLAGS) -lreadline

clean :
	rm -f ${OBJS}

fclean : clean
	rm -f ${NAME}
	make -C ${LIBGCDIR} fclean

re : fclean all

.PHONY: all fclean clean re
