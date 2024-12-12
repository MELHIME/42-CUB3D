SRC = main.c gnl/get_next_line.c gnl/get_next_line_utils.c

NAME = cub3D

OBJ = $(SRC:.c=.o)

CC = cc -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : gnl/get_next_line.h $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
clean :
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	@echo "\033[1;31mthe Mandatory part target has been deleted\033[0m"
	𝔚ℌ𝔘 𝔖𝔒  𝔖𝔈ℜℑ𝔒𝔘𝔖
	@echo "\033[1;31m𝔚ℌ𝔘 𝔖𝔒  𝔖𝔈ℜℑ𝔒𝔘𝔖\033[0m"

re: fclean all

#baa9i lik lblan dial lfree 9bel ay error call