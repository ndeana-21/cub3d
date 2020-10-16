# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 16:47:25 by ndeana            #+#    #+#              #
#    Updated: 2020/10/14 23:16:29 by ndeana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	=	main.c			color.c			utils.c			mlx_utils.c		\
				color_utils.c	make_frame.c	hooks.c			cub3d.c			\
				parser.c		error.c			parser_utils.c	ray_cast.c		\
				player.c		painting.c		get_obj.c		save_bmp.c		\
				get_obj_utils.c	player_utils.c	parser_path.c	parser_color.c	\
				parser_map.c	render_scene.c	render_scene_utl.c
				

HEADER_FILES=	cub3d.h			parser.h		keys_linux.h	color.h			\
				struct.h

SRCS_DIR	=	srcs
SRCS		=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJ_DIR		=	objs
OBJS		=	$(SRCS:.c=.o)
HEADER_DIR	=	srcs/include
HEADERS		=	$(addprefix $(HEADER_DIR)/, $(HEADER_FILES))
HEADER_INCL	=	-I./$(HEADER_DIR)

LIBFT_PATH	=	./libft
LIBFT_LINK	=	-L$(LIBFT_PATH) -lft
LIBFT_INCL	=	-I$(LIBFT_PATH)

MLX_PATH	=	./minilibx-linux
MLX_LINK	=	-L$(MLX_PATH) -lmlx -lXext -lX11
MLX_INCL	=	-I$(MLX_PATH)

LBMF_PATH	=	./libbitmapfile
LBMF_LINK	=	-L$(LBMF_PATH) -lbitmapfile
LBMF_INCL	=	-I$(LBMF_PATH)

LIBS		=	-lm $(MLX_LINK) $(LIBFT_LINK) $(LBMF_LINK)
INCLUDES	=	$(HEADER_INCL) $(LIBFT_INCL) $(MLX_INCL) $(LBMF_INCL)

MAKE_FLAGS	=	--no-print-directory -si -C
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g -O0 $(INCLUDES)
NAME		=	cub3D

ARGS		=	map2.cub
SCREEN		=	screen.bmp

all:		$(NAME)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) lib 
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus:		all

run:		all
	@./$(NAME) $(ARGS)

lib:			
	@make $(MAKE_FLAGS) $(LIBFT_PATH)
	@$(PRINT) "$(FGREEN)made LFT$(PNULL)"
	@make $(MAKE_FLAGS) $(MLX_PATH)
	@$(PRINT) "$(FGREEN)made MLX$(PNULL)"
	@make $(MAKE_FLAGS) $(LBMF_PATH)
	@$(PRINT) "$(FGREEN)made LBMF$(PNULL)"

norme:
	@make --no-print-directory -C $(LIBFT_PATH) norme
	@make --no-print-directory -C $(LBMF_PATH) norme
	@norminette $(SRCS) $(HEADERS)

clean:
	@$(RM) $(OBJS) $(SCREEN)
	@$(PRINT) "$(FYELLOW)remove objs of cub3D$(PNULL)"

fclean:
	@make clean --no-print-directory
	@$(RM) $(NAME)
	@$(PRINT) "$(FYELLOW)remove CUB3D$(PNULL)"
	@make clean $(MAKE_FLAGS) $(MLX_PATH)
	@$(PRINT) "$(FYELLOW)clean MLX$(PNULL)"
	@make fclean $(MAKE_FLAGS) $(LIBFT_PATH)
	@$(PRINT) "$(FYELLOW)fclean LFT$(PNULL)"
	@make fclean $(MAKE_FLAGS) $(LBMF_PATH)
	@$(PRINT) "$(FYELLOW)fclean LBMF$(PNULL)"


re:			fclean lib
	@make --no-print-directory
	@$(PRINT) "$(FGREEN)made CUB3D$(PNULL)"

fre:		fclean lib
	@make re $(MAKE_FLAGS) $(MLX_PATH)
	@$(PRINT) "$(FGREEN)made MLX$(PNULL)"
	@make re $(MAKE_FLAGS) $(LIBFT_PATH)
	@$(PRINT) "$(FGREEN)made LFT$(PNULL)"
	@make
	@$(PRINT) "$(FGREEN)made CUB3D$(PNULL)"

.PHONY:		all clean fclean re fre norme bonus run makelib

# **************************************************************************** #
#								Utilits										   #
# **************************************************************************** #

# Цвета шрифта
FBLACK		= \033[30m
FRED		= \033[31m
FGREEN		= \033[32m
FYELLOW		= \033[33m
FBLUE		= \033[34m
FMAGENTA	= \033[35m
FCYAN		= \033[36m
FGREY		= \033[37m

# Цвета фона
BGBLACK		= \033[40m
BGRED		= \033[41m
BGGREEN		= \033[42m
BGYELLOW	= \033[43m
BGBLUE		= \033[44m
BGMAGENTA	= \033[45m
BGCYAN		= \033[46m
BGGREY		= \033[47m

# Свойства текста
PBOLD		= \033[1m#	жирный шрифт
PDBOLD		= \033[2m#	полу яркий цвет
PNBOLD		= \033[22m#	нормальная интенсивность
PUNDERLINE	= \033[4m#	подчеркивание
PBLINK		= \033[5m#	мигание
PINVERSE	= \033[7m#	инверсия
PNULL		= \033[0m#	отмена

PRINT		= echo 