NAME = fractol

SRC_FILES = callbacks.c \
			fractals.c \
			init.c \
			main.c \
			parse.c \
			render.c \
			util_shared.c

SRC_OBJS = $(SRC_FILES:.c=.o)

##Libriaries

#Libft
DLIBFT = libft
LIBFT = $(DLIBFT)/libft.a
FT = ft

#MLX42
MLX42 = mlx42
BUILD_DIR = $(MLX42)/build
MLX42LIB = $(BUILD_DIR)/libmlx42.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I$(MLX42)/include


# Current OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	EXT_LIBS = -ldl -lglfw -pthread -lm
else
	EXT_LIBS += -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif

all: $(NAME)

bonus: $(NAME)

$(NAME): $(MLX42LIB) $(SRC_OBJS) $(LIBFT)
	cc $(CFLAGS) $^ -o $@ -L$(DLIBFT) -l$(FT) -L$(BUILD_DIR) -lmlx42 $(EXT_LIBS)

$(LIBFT) :
	make -C $(DLIBFT) all

$(MLX42LIB):
	if [ ! -d $(MLX42) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42); \
	fi
	if [ ! -f $(BUILD_DIR)/libmlx42.a ]; then \
		cmake $(MLX42) -B $(BUILD_DIR) && \
		cmake --build $(BUILD_DIR) -j4; \
	fi

re : fclean all

fclean : clean
	rm -f $(NAME)
	make -C $(DLIBFT) fclean
	rm -rf $(MLX42)

clean : 
	rm -f $(SRC_OBJS)
	make -C $(DLIBFT) clean

.PHONY: all clean fclean re bonus #debug debug_bonus
