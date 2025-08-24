# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 09:19:42 by yyudi             #+#    #+#              #
#    Updated: 2025/08/22 20:51:03 by yyudi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# ---- Directories ----
SRC_DIR		= src
INC_DIR		= include
LIBFT_DIR	= include/libft
MLX42_DIR	= mlx42
MLX42_REPO	= https://github.com/codam-coding-college/MLX42.git

# ---- Includes ----
INC			= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX42_DIR)/include

SRCS		= \
	$(SRC_DIR)/alloc_map.c \
	$(SRC_DIR)/anim_bonus.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/draw_line.c \
	$(SRC_DIR)/events_center.c \
	$(SRC_DIR)/events_controls.c \
	$(SRC_DIR)/events_dispatch.c \
	$(SRC_DIR)/events_height.c \
	$(SRC_DIR)/events_init.c \
	$(SRC_DIR)/events_mouse.c \
	$(SRC_DIR)/events_reset.c \
	$(SRC_DIR)/init_app.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/pass_fill.c \
	$(SRC_DIR)/project_iso.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/render_grid.c \
	$(SRC_DIR)/render_palette.c \
	$(SRC_DIR)/render_pivot.c \
	$(SRC_DIR)/shade_bonus.c \
	$(SRC_DIR)/strarr_utils.c\
	$(SRC_DIR)/map_base.c 

OBJS		= $(SRCS:.c=.o)

# ---- Libs ----
LIBFT_A		= $(LIBFT_DIR)/libft.a
MLX42_LIB	= $(MLX42_DIR)/build/libmlx42.a

UNAME_S		:= $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBS	= -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	RPATH	= -Wl,-rpath,$(MLX42_DIR)/build
else
	LIBS	= -lglfw -ldl -lm -lpthread
	RPATH	= -Wl,-rpath,$(MLX42_DIR)/build
endif

# =============================
# Rules
# =============================

all: clone_mlx42 $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX42_LIB) $(LIBS) $(RPATH) -o $(NAME)

# ---- Fetch & build MLX42 ----
clone_mlx42:
	@if [ ! -d "$(MLX42_DIR)/.git" ]; then \
		echo "Cloning MLX42 into $(MLX42_DIR) ..."; \
		git clone $(MLX42_REPO) $(MLX42_DIR); \
	else \
		echo "MLX42 already cloned."; \
	fi

$(MLX42_LIB): clone_mlx42
	@echo "Building MLX42 with CMake ..."
	@cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR)
	@cmake --build $(MLX42_DIR)/build

# ---- Build libft ----
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

# ---- Objects ----
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# ---- Cleaning ----
clean_mlx:
	@echo "Cleaning MLX42 artifacts..."
	@if [ -d "$(MLX42_DIR)/build" ]; then rm -rf "$(MLX42_DIR)/build"; fi
	@if [ -f "$(MLX42_LIB)" ]; then rm -f "$(MLX42_LIB)"; fi

fclean_mlx:
	@echo "Removing MLX42 repository..."
	@if [ -d "$(MLX42_DIR)" ]; then rm -rf "$(MLX42_DIR)"; fi

clean: clean_mlx
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean fclean_mlx
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re clone_mlx42 clean_mlx fclean_mlx
