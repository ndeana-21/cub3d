# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/03 16:47:25 by ndeana            #+#    #+#              #
#    Updated: 2020/08/28 17:39:10 by ndeana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	=	main.c			color.c			utils.c			mlx_utils.c		\
				color_utils.c	make_frame.c	hooks.c			cub3d.c			\
				parser.c		error.c			\

HEADERS		=	srcs/cub3d.h

SRCS_DIR	=	srcs
SRCS		=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJ_DIR		=	objs
OBJS		=	$(SRCS:.c=.o)

LIBFT_LINK	=	-L$(LIBFT_PATH) -lft
LIBFT_PATH	=	./libft
LIBFT_MAKE	=	@$(MAKE) -C $(LIBFT_PATH)
LIBFT_INCL	=	-I$(LIBFT_PATH)

MLX_LINK	=	-L$(MLX_PATH) -lmlx -lXext -lX11
MLX_PATH	=	./minilibx-linux
MLX_MAKE	=	@$(MAKE) -C $(MLX_PATH)
MLX_INCL	=	-I$(MLX_PATH)

LIBS		=	-lm $(MLX_LINK) $(LIBFT_LINK)
INCLUDES	=	-I./srcs $(LIBFT_INCL) $(MLX_INCL)

CC			=	gcc
CFLAGS		=	-Wall -Wextra $(INCLUDES)
NAME		=	cub3D

ARGS		=	map.cub

all:		makelib
			@$(MAKE) $(NAME)

$(NAME):	$(OBJS) $(HEADERS)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus:		all

run:		all
			@./$(NAME) $(ARGS)

makelib:			
			@$(LIBFT_MAKE)
			@$(MLX_MAKE)
			@$(PRINT) "$(FGREEN)make MLX$(PNULL)"

norme:
			@$(LIBFT_MAKE) norme
			@norminette $(SRCS) srcs/cub3d.h

clean:
			@$(RM) $(OBJS)
			@$(PRINT) "$(FYELLOW)remove objs of cub3D$(PNULL)"

fclean:		clean
			@$(RM) $(NAME)
			@$(PRINT) "$(FYELLOW)remove cub3D$(PNULL)"
			@$(LIBFT_MAKE) fclean

re:			clean all

fre:		fclean all

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