NAME = cub3d_parser
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include -I get_next_line -fsanitize=address -g3
# CFLAGS = -Wall -Wextra -Werror -I include -I get_next_line -g3

SRC_DIR = src
GNL_DIR = getnextline
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a  # Correct libft path

SRCS = $(SRC_DIR)/main.c \
		$(SRC_DIR)/read_file.c \
		$(SRC_DIR)/readdata.c \
		$(GNL_DIR)/get_next_line.c \
    	$(GNL_DIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

# Define a loading animation
define LOADING
	@echo "Compiling $@ ...";
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Finished $@ ✓"
endef

# Silent rule for compiling all source files
all: $(LIBFT) $(NAME)

# Compile main program and link libft silently
$(NAME): $(OBJS)
	@echo "Linking $(NAME) ..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo "$(NAME) built successfully! 🎉"

# Rule to compile object files from sources
$(OBJS): %.o : %.c
	$(LOADING)

# Build libft before linking
$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR) --silent  # --silent to suppress libft's makefile output
	@echo "libft built successfully!"

# Clean up object files and libft
clean:
	@echo "Cleaning up..."
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean --silent
	@echo "Clean completed!"

# Full clean: remove executable and object files
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --silent
	@echo "Full clean completed!"

# Rebuild everything
re: fclean all
