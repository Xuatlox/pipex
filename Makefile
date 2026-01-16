SRC = pipex.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_strnstr.c \
		main.c
CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:.o=.c)
NAME = pipex
.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean :
	rm -rf $(NAME)

fclean : clean

re : fclean $(NAME)
