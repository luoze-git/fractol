NAME = fractol

SRC = ./
SRC_FILES = $(SRC)main.c \
			$(SRC)render.c \
			$(SRC)init.c \
			$(SRC)parse.c \
			$(SRC)mandelbrot.c \
			$(SRC)julia.c \
			$(SRC)callbacks.c \
			$(SRC)math_util.c

SRC_OBJS = $(SRC_FILES:.c=.o)

## Libraries

# Libft
DLIBFT = libft
LIBFT = $(DLIBFT)/libft.a
FT = ft

# MLX42
MLX42 = mlx42
BUILD_DIR = $(MLX42)/build
MLX42LIB = $(BUILD_DIR)/libmlx42.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I$(MLX42)/include -I$(MLX42)/include/MLX42

## Current OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	EXT_LIBS = -lglfw -ldl -pthread -lm -lX11 -lXext -lXrandr -lXinerama -lXcursor -lXi -lXxf86vm
else
	EXT_LIBS = -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif

all: $(NAME)

bonus: $(NAME)

$(NAME): $(MLX42LIB) $(SRC_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_OBJS) -o $@ -L$(DLIBFT) -l$(FT) -L$(BUILD_DIR) -lmlx42 $(EXT_LIBS)

$(LIBFT):
	$(MAKE) -C $(DLIBFT) all

$(MLX42LIB):
	if [ ! -d $(MLX42) ]; then \
		echo "Error: $(MLX42) directory not found. Provide MLX42 at $(MLX42) or update MLX42 path."; \
		exit 1; \
	fi
	if [ ! -f $(BUILD_DIR)/libmlx42.a ]; then \
		cmake -S $(MLX42) -B $(BUILD_DIR) && \
		cmake --build $(BUILD_DIR) -j4; \
	fi

re: fclean all

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(DLIBFT) fclean

clean:
	rm -f $(SRC_OBJS)
	$(MAKE) -C $(DLIBFT) clean

$(SRC_OBJS): fracto_header.h

.PHONY: all clean fclean re bonus
