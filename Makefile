NAME	:= Game
CFLAGS	:= -Wextra -Wall -Werror -g -Wunreachable-code -Ofast
LIBMLX	:= MLX42
LIBFT_DIR := new_libft
LIBFT := $(LIBFT_DIR)/libft.a
HEADERS	:= -I $(LIBFT_DIR)/include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT) -ldl -lglfw -pthread -lm
SRCS	:= get_coordinates.c main.c error.c connect_coordinates.c fdf_utils.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME) $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all, clean, fclean, re, libmlx
