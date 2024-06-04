S = src/
O = obj/
I = ./

SRC = \
	$Sphilo.c \
	$Sdata_utils.c \
	$Sutils.c \
	$Sthreads_controller.c \
	$Sphilo_actions.c \
	$Sphilo_utils.c

OBJ = $(SRC:$S%.c=$O%.o)

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
RMDIR = rmdir

all: $(NAME)

$O:
	mkdir -p $@

$(OBJ): | $O

$O%.o: $S%.c
	$(CC) $(CFLAGS) -I$I -c $^ -o $@

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	$(RM) $(OBJ)
	$(RMDIR) $O

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re