CC := clang
CFLAGS = -DBUFFER_SIZE=4096

SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
LOG_DIR := logs/$(shell date +"%Y-%m-%d")
LIB_DIR_FT := $(LIB_DIR)/libft
LIB_DIR_MLX := $(LIB_DIR)/mlx_linux

INC := -I include
LIB_MLX := -L $(LIB_DIR_MLX) -l mlx_Linux 
LIB_FT := -L $(LIB_DIR_FT) -l ft 
LIB_X := -L /usr/lib -l Xext -l X11 -l m -l z
LIBS := $(LIB_MLX) $(LIB_FT) $(LIB_X)

COMPILE = $(CC) $(CFLAGS) $(INC)

NAME := fdf
LIBFT := $(LIB_DIR_FT)/libft.a
MLX := $(LIB_DIR_MLX)/libmlx_Linux.a

SRC := 	main.c \
		draw.c \
		color.c \
		key_hooks.c \
		key_hooks1.c \
		key_hooks2.c \
		key_hooks3.c \
		window.c \
		terminate.c \
		parse.c \
		matrix.c \
		reshape.c \
		map_utils.c \
		test.c \
		check.c \
		utils.c \
		menu.c \
		rotation.c \
		print_utils.c \
		box.c \
		precalc_matrix.c \
		precalc_matrix2.c \
		mouse.c \
		sphere.c \
		time.c \
		bresenham.c \
		clipping.c \
		wobble.c \
		swap.c \
		numconvert.c \
		put_to_screen.c \
		shapes.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRC))

OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ))

LOG_FILE = $(LOG_DIR)/$(shell date +"%H-%M-%S")

.PHONY: all, clean, fclean, re, obj, debug, optimize
.SILENT:

all: $(NAME)
	echo "$(NAME) created!"

$(NAME): CFLAGS += -o3 -Wall -Werror -Wextra 
$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)

debug: CFLAGS += -g
debug: clean $(OBJS) $(LIBFT) $(MLX)
	$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)
	echo "$(NAME) created - DEBUG MODE!"

profile: CFLAGS += -pg
profile: clean §(OBJS) $(LIBFT) $(MLX) | $(LOG_DIR)
	$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)
	./$(NAME) test_maps/julia.fdf
	gprof fdf > $(LOG_FILE)
	rm gmon.out
	ls -dt1 $(LOG_DIR)/* | head -n 1 | xargs less

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LOG_DIR):
	mkdir -p $(LOG_DIR)
	
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
	$(MAKE) -C $(LIB_DIR_FT) fclean
	$(MAKE) -C $(LIB_DIR_MLX) clean

re: fclean all
