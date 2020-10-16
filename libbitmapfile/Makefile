# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndeana <ndeana@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/05 18:21:38 by ndeana            #+#    #+#              #
#    Updated: 2020/10/08 00:34:00 by ndeana           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libbitmapfile.a

SRCS	=	dint4cpy.c			create_bmpfile.c		write_bmpinfoheader.c	\
			write_pixeldata.c	write_bmpfileheader.c

OBJS	=	$(SRCS:.c=.o)

HEADER	=	bitmapfile.h

CC		=	clang
FLAGS	=	-Wall -Wextra -Werror

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -c $(SRCS) -I./ $(HEADER)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

all: $(NAME)

clean:
	@rm -f $(OBJS)
fclean: clean
	@rm -f $(NAME)

re: fclean all

norme:
	@norminette $(HEADER) $(SRCS)