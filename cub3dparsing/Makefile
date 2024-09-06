NAME = cub3d_parser
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include -I  get_next_line -I libft -fsanitize=address -g3

SRC_DIR = src
GNL_DIR = getnextline
LIBFT_DIR = ./libft/libft.a
INCLUDE_DIR = include

SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/read_file.c \
		$(SRC_DIR)/readdata.c \
		$(GNL_DIR)/get_next_line.c \
    	$(GNL_DIR)/get_next_line_utils.c
		$(LIBFT_DIR)/ft_split.c \
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re: fclean all