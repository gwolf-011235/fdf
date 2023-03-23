# text effects
RESET := \033[0m
BOLD := \033[1m
BLACK := \033[30m
GREEN := \033[32m
YELLOW := \033[33m
RED := \033[31m
BLUE := \033[34m
CYAN := \033[36m
CYAN_B := \033[46m

# directories
SRC_DIR := src
OBJ_DIR := obj
LIB_DIR := lib
LOG_DIR := logs/$(shell date +"%Y-%m-%d")
LIB_DIR_FT := $(LIB_DIR)/libft
LIB_DIR_MLX := $(LIB_DIR)/mlx_linux

# libraries
INC := -I include -I /usr/include/X11 -I lib/libft/include -I lib/mlx_linux/
LIB_MLX := -L $(LIB_DIR_MLX) -l mlx_Linux 
LIB_FT := -L $(LIB_DIR_FT) -l ft 
LIB_X := -L /usr/lib -l Xext -l X11 -l m -l z
LIBS := $(LIB_MLX) $(LIB_FT) $(LIB_X)

# compiling
CC := cc
CFLAGS = -DBUFFER_SIZE=4096
COMPILE = $(CC) $(CFLAGS) $(INC)

# targets
NAME := fdf
LIBFT := $(LIB_DIR_FT)/libft.a
MLX := $(LIB_DIR_MLX)/libmlx_Linux.a

# progress bar
HIT_TOTAL = $(words $(SRCS))
HIT_COUNT = $(eval HIT_N != expr ${HIT_N} + 1)${HIT_N}
ECHO = printf "\033[2K\r[`expr ${HIT_COUNT} '*' 100 / ${HIT_TOTAL}`%%] %s"

SRC := 	main.c \
		check.c \
		parse.c \
		window.c \
		reshape.c \
		draw.c \
		color.c \
		bresenham.c \
		matrix.c \
		terminate.c \
		utils_calc.c \
		utils_limits.c \
		utils_prog.c \
		utils_set.c \
		utils_string.c \
		utils_swap.c \
		menu.c \
		rotation.c \
		box.c \
		precalc_matrix1.c \
		precalc_matrix2.c \
		mouse.c \
		key_hooks.c \
		key_hooks1.c \
		key_hooks2.c \
		key_hooks3.c \
		sphere.c \
		time.c \
		clipping.c \
		easter.c \
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

$(NAME): CFLAGS += -o3 -Wall -Werror -Wextra 
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	printf "\033[2K\r$(GREEN)%-50s$(RESET)\n" "compilation done"
	$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)
	echo "\n$(GREEN)$(NAME) created!$(RESET)"

debug: CFLAGS += -g
debug: clean $(OBJS) $(LIBFT) $(MLX)
	$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)
	echo "$(NAME) created - DEBUG MODE!"

profile: CFLAGS += -pg
profile: clean $(OBJS) $(LIBFT) $(MLX) | $(LOG_DIR)
	$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)
	./$(NAME) test_maps/julia.fdf
	gprof fdf > $(LOG_FILE)
	rm gmon.out
	ls -dt1 $(LOG_DIR)/* | head -n 1 | xargs less

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LOG_DIR):
	mkdir -p $(LOG_DIR)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) message
	$(ECHO) "$(CC) $@"
	$(COMPILE) -c $< -o $@

$(LIBFT):
	printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) -C $(LIB_DIR)/libft

$(MLX):
	printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)mlx$(RESET)]\n"
	$(MAKE) -C $(LIB_DIR)/mlx_linux

message:
	printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)fdf$(RESET)]\n"

clean: 
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)fdf$(RESET)]\n"
	rm -rf $(OBJ_DIR)
	printf "$(RED)subdir $(OBJ_DIR) cleaned$(RESET)\n"
	rm -rf gmon.out

fclean: clean
	rm -rf $(NAME)
	printf "$(RED)$(NAME) cleaned$(RESET)\n"
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) -C $(LIB_DIR_FT) fclean
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)mlx$(RESET)]\n"
	$(MAKE) -C $(LIB_DIR_MLX) clean

re: fclean all
