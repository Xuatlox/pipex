SRC = pipex.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_split.c \
		ft_calloc.c \
		main.c
CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
NAME = pipex
.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ)

$(OBJ) : $(SRC)
	cd $(OBJ_DIR) && $(CC) $(CFLAGS) -c $(addprefix ../, $(SRC))
clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)
