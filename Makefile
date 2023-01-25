CC := clang
CFLAGS := -Wall -Werror -Wextra -g

INC := -I/usr/include -Imlx_linux
LIB := -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

COMPILE := $(CC) $(CFLAGS) $(INC)

NAME := fdf

SRC := main.c draw.c color.c hooks.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILE) $(OBJ) $(LIB) -o $(NAME)
	
%.o: %.c
	$(COMPILE) -c $< -o $@

clean: 
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
