# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 16:47:25 by ndeana            #+#    #+#              #
#    Updated: 2020/09/16 16:44:34 by ndeana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	=	main.c			color.c			utils.c			mlx_utils.c		\
				color_utils.c	make_frame.c	hooks.c			cub3d.c			\
				parser.c		error.c			parser_utils.c	ray_cast.c		\
				player.c		free_cub3d.c	painting.c

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
LIBFT_MAKE	=	@$(MAKE) -C $(LIBFT_PATH)
LIBFT_INCL	=	-I$(LIBFT_PATH)

MLX_PATH	=	./minilibx-linux
MLX_LINK	=	-L$(MLX_PATH) -lmlx -lXext -lX11
MLX_MAKE	=	@$(MAKE) -C $(MLX_PATH)
MLX_INCL	=	-I$(MLX_PATH)


LIBS		=	-lm $(MLX_LINK) $(LIBFT_LINK)
INCLUDES	=	$(HEADER_INCL) $(LIBFT_INCL) $(MLX_INCL)

CC			=	gcc
CFLAGS		=	-Wall -Wextra $(INCLUDES)
NAME		=	cub3D

ARGS		=	map.cub

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADERS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus:		all

run:		all
			@./$(NAME) $(ARGS)

lib:			
			@$(LIBFT_MAKE)
			@$(PRINT) "$(FGREEN)made LFT$(PNULL)"
			@$(MLX_MAKE)
			@$(PRINT) "$(FGREEN)made MLX$(PNULL)"

norme:
			@$(LIBFT_MAKE) norme
			@norminette $(SRCS) $(HEADERS)

clean:
			@$(RM) $(OBJS)
			@$(PRINT) "$(FYELLOW)remove objs of cub3D$(PNULL)"
			@$(MLX_MAKE) clean
			@$(PRINT) "$(FYELLOW)clean mlx$(PNULL)"
			@$(LIBFT_MAKE) clean
			@$(PRINT) "$(FYELLOW)clean libft$(PNULL)"


fclean:		clean
			@$(RM) $(NAME)
			@$(PRINT) "$(FYELLOW)remove cub3D$(PNULL)"
			@$(LIBFT_MAKE) fclean
			@$(PRINT) "$(FYELLOW)fclean libft$(PNULL)"


re:			clean
			@$(MLX_MAKE)
			@$(PRINT) "$(FGREEN)made MLX$(PNULL)"
			@$(LIBFT_MAKE)
			@$(PRINT) "$(FGREEN)made LFT$(PNULL)"
			@$(MAKE)
			@$(PRINT) "$(FGREEN)made CUB3D$(PNULL)"

fre:		fclean
			@$(MLX_MAKE)
			@$(PRINT) "$(FGREEN)made MLX$(PNULL)"
			@$(LIBFT_MAKE)
			@$(PRINT) "$(FGREEN)made LFT$(PNULL)"
			@$(MAKE)
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