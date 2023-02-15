CC := clang
CFLAGS = -DBUFFER_SIZE=4096

SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib

INC := -I /usr/include -I include
LIB_MLX := -L $(LIB_DIR)/mlx_linux -l mlx_Linux 
LIB_FT := -L $(LIB_DIR)/libft -l ft 
LIB_X := -L /usr/lib -l Xext -l X11 -l m -l z
LIBS := $(LIB_MLX) $(LIB_FT) $(LIB_X)

COMPILE = $(CC) $(CFLAGS) $(INC)

NAME := fdf.out
LIBFT := $(LIB_DIR)/libft/libft.a
MLX := $(LIB_DIR)/mlx_linux/libmlx_Linux.a

SRC := 	main.c \
		draw.c \
		color.c \
		hooks.c \
		window.c \
		terminate.c \
		parse.c \
		matrix.c \
		reshape.c \
		map_utils.c \
		test.c \
		vector.c \
		validate.c \
		utils.c \
		menu.c \
		rotation.c \
		print_utils.c \
		box.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ))

.PHONY: all, clean, fclean, re, obj, debug, optimize
.SILENT:

all: $(NAME)
	echo "$(NAME) created!"

$(NAME): CFLAGS += -o3 -Wall -Werror -Wextra 
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)

debug: CFLAGS += -g
debug: fclean $(NAME)
	$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBS) -o $(NAME)
	echo "$(NAME) created - DEBUG MODE!"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(COMPILE) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)/libft

$(MLX):
	$(MAKE) -C $(LIB_DIR)/mlx_linux

clean: 
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
