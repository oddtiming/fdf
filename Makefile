NAME	=	fdf

# FOR TESTING PURPOSES
RUN_ARGS = test_maps/42.fdf

SHELL	=	bash

GREEN		=	\033[0;32m
BLUE		=	\033[0;34m
CYAN		=	\033[0;36m
RED			=	\033[0;31m
ON_RED		=	\033[41m
RESET_COL	=	\033[0m

CFILES	=	assign.c \
			assign_colors.c \
			bresenham.c \
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

INCL		= include
HEADERS		= $(addprefix $(INCL)/, $(HFILES))

INCLFLAGS	= -I$(INCL)
MLX_FLAGS 	= -Lminilibx_macos -lmlx  -framework OpenGL -framework AppKit
LIBFT_FLAGS	= -lft -Llibft
LIBM_FLAG	= -lm

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -O3

#
# DEBUG build settings
#
DBG_DIR = debug_objs
DBG_EXE = $(NAME)_debug
DBG_OBJS = $(addprefix $(DBG_DIR)/, $(CFILES:.c=.o))
DBG_CFLAGS = -D DEBUG=1 -g


LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

RM_OBJS			=	rm -rf $(OBJ_DIR)
RM_OBJS_OUT		=	$$($(RM_OBJS) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_EXE			=	rm -f $(NAME)
RM_EXE_OUT		=	$$($(RM_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_LIBFT		=	make clean -sC ./libft
RM_LIBFT_OUT	=	$$($(RM_LIBFT) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_EXE		=	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(LIBM_FLAG) $(MLX_FLAGS) $(INCLFLAGS) $(OBJS) -o $(NAME)
COMPILE_EXE_OUT	=	$$($(COMPILE_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

COMPILE_C		=	$(CC) $(CFLAGS) $(INCLFLAGS) -o $@ -c $<
COMPILE_C_OUT	=	$$($(COMPILE_C) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN)%-25s-->%25s $(RESET_COL)$(COMPILE_C_OUT)\n" $^ $@

#
# DEBUG MACROS
#
COMPILE_DBG_EXE		=	$(CC) $(DBG_CFLAGS) $(LIBFT_FLAGS) $(LIBM_FLAG) $(MLX_FLAGS) $(INCLFLAGS) $(DBG_OBJS) -o $(DBG_EXE)
COMPILE_DBG_EXE_OUT	=	$$($(COMPILE_DBG_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
COMPILE_DBGC		=	$(CC) $(DBG_CFLAGS) $(INCLFLAGS) -o $@ -c $<
COMPILE_DBGC_OUT	=	$$($(COMPILE_DBGC) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')
RM_DBG_EXE			=	rm -rf $(DBG_EXE) $(DBG_DIR)
RM_DBG_EXE_OUT		=	$$($(RM_DBG_EXE) 2>&1 | sed -e 's/error/\\\033[0;31merror\\\033[0m/g' -e 's/warning/\\\033[0;33mwarning\\\033[0m/g')

$(DBG_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(DBG_DIR)
	@echo -e "$(ON_RED)>\t$^\t--> $@ $(RESET_COL)$(COMPILE_DBGC_OUT)"

all: $(NAME)
	@if [ -e $(NAME) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Compilation successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Compilation failed\n>>>>>>>>$(RESET_COL)"; \
	fi


$(NAME):	libft pretty_print $(OBJS)
	@echo -e "\n$(CYAN)>>>>>>>> Compiling $(NAME) ...$(RESET_COL)$(COMPILE_EXE_OUT)"

silent_libft:
	@echo -e "---------------------- libft.a ----------------------\n"
	@echo -e "$(CYAN)>>>>>>>> Archiving libft.a ...$(RESET_COL)"
	@make -s bonus -C $(LIBFT_DIR)
	@if [ -e $(LIBFT) ]; \
		then \
		echo -e "$(GREEN)>>>>>>>> Archive successful\n>>>>>>>>$(RESET_COL)"; \
	else \
		echo -e "$(RED)>>>>>>>> Archive failed\n>>>>>>>>$(RESET_COL)"; \
	fi

libft: silent_libft

pretty_print: 
	@echo -e "\n--------------------- $(NAME) ---------------------"
											  

clean:
	@echo -e "$(RED)>>>>>>>> Deleting obj files$(RESET_COL)$(RM_OBJS_OUT)"
	@echo -e "$(GREEN)>>>>>>>> obj files deleted\n>>>>>>>>$(RESET_COL)"

clean_libft:
	@echo -e "$(RED)>>>>>>>> make fclean -sC libft $(RESET_COL)$(RM_LIBFT_OUT)"
	@echo -e "$(GREEN)>>>>>>>> libft cleaned\n>>>>>>>>$(RESET_COL)"

clean_debug: clean
	@echo -e "$(RED)>>>>>>>> Deleting debug obj files$(RESET_COL)$(RM_DBG_EXE_OUT)"
	@echo -e "$(GREEN)>>>>>>>> obj files deleted\n>>>>>>>>$(RESET_COL)"

fclean:	clean clean_libft clean_debug
	@echo -e "$(RED)>>>>>>>> Deleting $(NAME)$(RESET_COL)$(RM_EXE_OUT)"
	@echo -e "$(GREEN)>>>>>>>> ./$(NAME) deleted\n>>>>>>>>$(RESET_COL)"

re:	fclean all

bonus:	all

run: all
	./$(NAME) $(RUN_ARGS)
#
# Debug rules
#
pretty_print_debug:
	@echo -e "$(RED)\n------------------- $(DBG_EXE) -------------------$(RESET_COL)\n"

debug: all pretty_print_debug $(DBG_OBJS)
	@echo -e "\n$(ON_RED)>>>>>>>> Compiling $(DBG_EXE) ...$(RESET_COL)$(COMPILE_DBG_EXE_OUT)"
	./$(DBG_EXE) $(RUN_ARGS)

.PHONY: all clean clean_libft fclean re bonus libft silent_libft pretty_print pretty_print_debug run debug
