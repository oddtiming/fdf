NAME	=	fdf

# FOR TESTING PURPOSES
RUN_ARGS = test_maps/42.fdf

SHELL	=	bash

GREEN		=	\033[0;32m
CYAN		=	\033[0;36m
RED			=	\033[0;31m
ON_RED		=	\033[41m
RESET_COL	=	\033[0m

CFILES	=	assign.c \
			assign_colors.c \
			bresenham.c \
			coalitions.c \
			colors.c \
			cleanup.c \
			display.c \
			display_map.c \
			display_menu.c \
			fdf.c \
			hooks.c \
			init.c \
			key_hooks.c \
			line_clipping.c \
			matrix.c \
			mouse_hooks.c \
			parse.c \
			perspective.c \
			utils.c

SRC_DIR	= src
SRCS	= $(addprefix $(SRC_DIR)/, $(CFILES))

OBJ_DIR	= obj
OBJS	= $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

INCFILES	=	fdf_hooks.h \
				fdf.h \
				mlx.h

INC_DIR			= ./include
INCS			= $(addprefix $(INC_DIR)/, $(INCFILES))

INCLFLAGS			= -I$(INC_DIR)
MLX_FLAGS 			= -Lminilibx_macos -lmlx  -framework OpenGL -framework AppKit
LIBFT_FLAGS			= -lft -Llibft
LIBM_FLAG			= -lm

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -Ofast -g

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

RM_OBJS			=	rm -rf $(OBJ_DIR)
RM_OBJS_OUT		=	$$($(RM_OBJS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_EXE			=	rm -f $(NAME)
RM_EXE_OUT		=	$$($(RM_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_LIBFT		=	make clean -sC ./libft

COMPILE_EXE				=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(LIBM_FLAG) $(MLX_FLAGS) $(INCLFLAGS) $(OBJS) -o $(NAME)
COMPILE_EXE_OUT			=	$$($(COMPILE_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_C		=	$(CC) $(CFLAGS) $(INCLFLAGS) -o $@ -c $<
COMPILE_C_OUT	=	$$($(COMPILE_C) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_LIBFT		=	make -sC $(LIBFT_DIR)
COMPILE_LIBFT_OUT	=	$$($(COMPILE_LIBFT) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(@D)
	@printf "$(CYAN)%-25s-->%25s $(RESET_COL)$(COMPILE_C_OUT)\n" $< $@


all: $(NAME)
	@if [ -e $(NAME) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Compilation successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Compilation failed\n>>>>>>>>$(RESET_COL)"; \
	fi


$(NAME):	libft pretty_print $(OBJS)
	@echo -e "\n$(CYAN)>>>>>>>> Compiling into executable $(UYELLOW)./$(NAME)$(RESET_COL)$(COMPILE_EXE_OUT)"

silent_libft:
	@echo -e "---------------------- libft.a ----------------------\n"
	@echo -e "\n$(CYAN)>>>>>>>> Compiling libft$(RESET_COL)$(COMPILE_LIBFT_OUT)"

libft: silent_libft

pretty_print: 
	@echo -e "\n--------------------- $(NAME) ---------------------"										  

clean:
	@echo -e "$(RED)>>>>>>>> Deleting obj files$(RESET_COL)"
	@$(RM_OBJS)

clean_libft:
	@echo -e "$(RED)>>>>>>>> Cleaning libft $(RESET_COL)"
	@$(RM_LIBFT)

fclean:	clean clean_libft
	@echo -e "$(RED)>>>>>>>> Deleting $(NAME)$(RESET_COL)"
	@$(RM_EXE)

re:	fclean all

run: all
	./$(NAME) $(RUN_ARGS)

.PHONY: all clean clean_libft fclean re libft silent_libft pretty_print run
