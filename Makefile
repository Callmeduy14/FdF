# =============================
# FdF — Build with MLX42 (GLFW)
# MLX42 di luar include/, libft di include/libft
# =============================

NAME        := fdf
CC          := cc
CFLAGS      := -Wall -Wextra -Werror

# ---- Directories ----
SRC_DIR     := src
INC_DIR     := include
LIBFT_DIR   := include/libft
MLX42_DIR   := mlx42
MLX42_REPO  := https://github.com/codam-coding-college/MLX42.git

# ---- Includes (PASTIKAN TIDAK ADA SPASI NYASAR) ----
INC         := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX42_DIR)/include

# ---- Sources ----
SRC := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parser.c \
	$(SRC_DIR)/project_iso.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/draw_line.c \
	$(SRC_DIR)/events.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/strarr_utils.c

BONUS := \
	$(SRC_DIR)/anim_bonus.c \
	$(SRC_DIR)/shade_bonus.c

OBJ  := $(SRC:.c=.o)
BOBJ := $(BONUS:.c=.o)

# ---- Libs ----
LIBFT_A     := $(LIBFT_DIR)/libft.a
MLX42_LIB   := $(MLX42_DIR)/build/libmlx42.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBS  := -lglfw -framework Cocoa -framework OpenGL -framework IOKit
	RPATH := -Wl,-rpath,$(MLX42_DIR)/build
endif
ifeq ($(UNAME_S),Linux)
	LIBS  := -lglfw -lGL -ldl -lm -lpthread
	RPATH := -Wl,-rpath,$(MLX42_DIR)/build
endif

# =============================
# Rules
# =============================

all: clone_mlx42 $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(MLX42_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(MLX42_LIB) $(LIBS) $(RPATH) -o $(NAME)

bonus: $(OBJ) $(BOBJ) $(LIBFT_A) $(MLX42_LIB)
	$(CC) $(CFLAGS) -DBONUS $(OBJ) $(BOBJ) $(LIBFT_A) $(MLX42_LIB) $(LIBS) $(RPATH) -o $(NAME)

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
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# ---- Cleaning ----
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re clone_mlx42
