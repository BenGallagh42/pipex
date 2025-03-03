NAME        = pipex
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g -O0

# Directories
SRC_DIR     = src
UTILS_DIR   = src/utils
OBJ_DIR     = src/obj
INCLUDE_DIR = inc

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/child.c \
	   $(SRC_DIR)/path.c \
       $(SRC_DIR)/pipex_utils.c \
	   $(SRC_DIR)/exits.c \
       $(SRC_DIR)/here_doc.c \
	   $(SRC_DIR)/normal.c \
       $(SRC_DIR)/pipex.c \
	   $(UTILS_DIR)/ft_putstr_fd.c \
	   $(UTILS_DIR)/ft_putendl_fd.c \
       $(UTILS_DIR)/ft_split.c \
	   $(UTILS_DIR)/ft_strcat.c \
	   $(UTILS_DIR)/ft_strchr.c \
       $(UTILS_DIR)/ft_strcmp.c \
	   $(UTILS_DIR)/ft_strcpy.c \
	   $(UTILS_DIR)/ft_strdup.c \
       $(UTILS_DIR)/ft_strlen.c \
       $(UTILS_DIR)/ft_strncmp.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include flags
INC = -I $(INCLUDE_DIR) -I $(UTILS_DIR)

# Default rule
all: $(NAME)

# Create object directories (en créant la structure miroir)
$(OBJ_DIR):
	@echo "\033[1;33mCreating object directories...\033[0m"
	@mkdir -p $(OBJ_DIR)/$(SRC_DIR)
	@mkdir -p $(OBJ_DIR)/$(UTILS_DIR)

# Build executable
$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "\033[1;36mCompiling project...\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)

# Compile .c files into .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "\033[1;35mCompiling $<...\033[0m"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Clean: remove object files
clean:
	@echo "\033[1;33mCleaning object files...\033[0m"
	@rm -rf $(OBJ_DIR)

# Fclean: remove executable and object files
fclean: clean
	@echo "\033[1;31mCleaning executable...\033[0m"
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
