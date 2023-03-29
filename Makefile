# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 13:35:25 by gwolf             #+#    #+#              #
#    Updated: 2023/03/29 13:43:36 by gwolf            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
SRC_DIR_B := src/bonus
OBJ_DIR := obj
OBJ_DIR_B := obj/bonus
LIB_DIR := lib
LOG_DIR := logs/$(shell date +"%Y-%m-%d")
LIB_DIR_FT := $(LIB_DIR)/libft
LIB_DIR_MLX := $(LIB_DIR)/mlx_linux

# include
INC := -I include -I /usr/include/X11 -I lib/libft/include -I lib/mlx_linux/

# libraries
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
NAME_B := fdf_bonus
LIBFT := $(LIB_DIR_FT)/libft.a
MLX := $(LIB_DIR_MLX)/libmlx_Linux.a

# progress bar
HIT_TOTAL = $(words $(SRCS))
HIT_COUNT = $(eval HIT_N != expr ${HIT_N} + 1)${HIT_N}
ECHO = printf "\033[2K\r[`expr ${HIT_COUNT} '*' 100 / ${HIT_TOTAL}`%%] %s"
HIT_TOTAL_B = $(words $(SRCS_B))
HIT_NB := 0
HIT_COUNT_B = $(eval HIT_NB := $(shell expr ${HIT_NB} + 1))${HIT_NB}
ECHO_B = printf "\033[2K\r[`expr ${HIT_COUNT_B} '*' 100 / ${HIT_TOTAL_B}`%%] %s"

# profile map
PROFILE_MAP = maps/julia.fdf

# source files
SRC :=  box.c \
        bresenham.c \
        check.c \
        color.c \
        draw.c \
        key_hooks.c \
        main.c \
        matrix.c \
        parse.c \
        reshape.c \
        terminate.c \
        utils_calc.c \
        utils_limits.c \
        utils_prog.c \
        utils_set.c \
        utils_string.c \
        window.c \

SRC_B := 	box_bonus.c \
			bresenham_bonus.c \
			check_bonus.c \
			clipping_bonus.c \
			color_bonus.c \
			draw_bonus.c \
			easter_bonus.c \
			key_hooks_bonus.c \
			key_hooks1_bonus.c \
			key_hooks2_bonus.c \
			key_hooks3_bonus.c \
			main_bonus.c \
			matrix_bonus.c \
			menu_bonus.c \
			mouse_bonus.c \
			numconvert_bonus.c \
			parse_bonus.c \
			precalc_matrix1_bonus.c \
			precalc_matrix2_bonus.c \
			put_to_screen_bonus.c \
			reshape_bonus.c \
			rotation_bonus.c \
			sphere_bonus.c \
			terminate_bonus.c \
			time_bonus.c \
			utils_calc_bonus.c \
			utils_limits_bonus.c \
			utils_prog_bonus.c \
			utils_set_bonus.c \
			utils_string_bonus.c \
			utils_swap_bonus.c \
			window_bonus.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRC))
SRCS_B := $(addprefix $(SRC_DIR_B)/, $(SRC_B))

OBJ := $(SRC:.c=.o)
OBJ_B := $(SRC_B:.c=.o)

OBJS := $(addprefix $(OBJ_DIR)/, $(OBJ))
OBJS_B := $(addprefix $(OBJ_DIR_B)/, $(OBJ_B))

LOG_FILE = $(LOG_DIR)/$(shell date +"%H-%M-%S")

.PHONY: all, clean, fclean, re, obj, debug, debug_bonus, profile, bonus, re_bonus

.SILENT:

all: $(NAME)
	printf '$(GREEN)ALL DONE!$(RESET)\n'

$(NAME): CFLAGS += -o3 -Wall -Werror -Wextra 
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	printf "\033[2K\r$(GREEN)%-50s$(RESET)\n" "compilation done"
	$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)
	echo "$(GREEN)$(NAME) created!$(RESET)"

bonus: CFLAGS += -o3 -Wall -Werror -Wextra 
bonus: $(LIBFT) $(MLX) $(OBJS_B)
	printf "\033[2K\r$(GREEN)%-50s$(RESET)\n" "compilation done"
	$(COMPILE) $(OBJS_B) $(LIBS) -o $(NAME_B)
	echo "$(GREEN)$(NAME) created - BONUS!$(RESET)"

debug: CFLAGS += -g
debug: clean $(OBJS) $(LIBFT) $(MLX)
	$(COMPILE) $(OBJS) $(LIBS) -o $(NAME)
	echo "$(NAME) created - DEBUG MODE!"

debug_bonus: CFLAGS += -g
debug_bonus: clean $(OBJS_B) $(LIBFT) $(MLX)
	$(COMPILE) $(OBJS_B) $(LIBS) -o $(NAME)
	echo "$(NAME) created - DEBUG MODE!"

profile: CFLAGS += -pg
profile: clean $(OBJS_B) $(LIBFT) $(MLX) | $(LOG_DIR)
	$(COMPILE) $(OBJS_B) $(LIBS) -o $(NAME_B)
	./$(NAME_B) $(PROFILE_MAP)
	gprof $(NAME_B) > $(LOG_FILE)
	rm gmon.out
	ls -dt1 $(LOG_DIR)/* | head -n 1 | xargs less

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_B):
	mkdir -p $(OBJ_DIR_B)

$(LOG_DIR):
	mkdir -p $(LOG_DIR)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) message
	$(ECHO) "$(CC) $@"
	$(COMPILE) -c $< -o $@

$(OBJ_DIR_B)/%.o: $(SRC_DIR_B)/%.c | $(OBJ_DIR_B) message
	$(ECHO_B) "$(CC) $@"
	$(COMPILE) -c $< -o $@

$(LIBFT):
	printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) -C $(LIB_DIR_FT)

$(MLX):
	printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)mlx$(RESET)]\n"
	$(MAKE) -C $(LIB_DIR_MLX)

message:
	printf "$(YELLOW)$(BOLD)compilation$(RESET) [$(BLUE)fdf$(RESET)]\n"

clean: 
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)fdf$(RESET)]\n"
	rm -rf $(OBJ_DIR)
	printf "$(RED)subdir $(OBJ_DIR) cleaned$(RESET)\n"
	rm -rf gmon.out

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME_B)
	printf "$(RED)$(NAME) cleaned$(RESET)\n"
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)libft$(RESET)]\n"
	$(MAKE) -C $(LIB_DIR_FT) fclean
	printf "$(YELLOW)$(BOLD)clean$(RESET) [$(BLUE)mlx$(RESET)]\n"
	$(MAKE) -C $(LIB_DIR_MLX) clean

re: fclean all
	
re_bonus: fclean bonus
