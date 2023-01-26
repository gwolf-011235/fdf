CC := clang
CFLAGS := -Wall -Werror -Wextra -g

INC := -I/usr/include -Imlx_linux -Iinclude
LIB := -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

COMPILE := $(CC) $(CFLAGS) $(INC)

NAME := fdf.out

SRC_PATH := src
OBJ_PATH := obj

SRC := main.c draw.c color.c hooks.c

SRCS := $(addprefix $(SRC_PATH)/, $(SRC))

OBJ := $(SRC:.c=.o)
OBJS := $(addprefix $(OBJ_PATH)/, $(OBJ))

.PHONY: all, clean, fclean, re, obj
.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	$(COMPILE) $(OBJS) $(LIB) -o $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(COMPILE) -c $< -o $@

clean: 
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)
