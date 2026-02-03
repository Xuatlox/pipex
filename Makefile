SRC = pipex.c \
		ft_strjoin.c \
		ft_strlen.c \
		ft_split.c \
		main.c
BONUS_SRC = pipex_bonus.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_split.c \
			main_bonus.c \
			pipeline_utils_bonus.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_strcmp.c
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
OBJ_DIR = obj/
BONUS_OBJ_DIR = bonus_obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJ_BONUS = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_SRC:.c=.o))
NAME = pipex
.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ) : $(SRC)
	cd $(OBJ_DIR) && $(CC) $(CFLAGS) -c $(addprefix ../, $(SRC))

clean :
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

bonus : $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BONUS)

$(OBJ_BONUS) : $(BONUS_SRC)
	cd $(BONUS_OBJ_DIR) && $(CC) $(CFLAGS) -c $(addprefix ../, $(BONUS_SRC))
