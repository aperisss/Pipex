#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/22 19:12:16 by aperis            #+#    #+#              #
#    Updated: 2021/12/23 12:31:05 by aperis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC=    get_path.c	\
		ft_split.c       		\
		pipex.c      \
		pipex_utils.c      \
		syscalls.c		\

NAME= pipex

OBJETS= ${SRC:.c=.o}

gcc=gcc -Werror -Wall -Wextra

$(NAME):    ${OBJETS}	

%.o: %.c
	${gcc} -o $@ -c $<
	
all: ${NAME}

re: fclean all

clean:
		rm -f ${OBJETS} 

fclean: clean
		rm -f ${NAME}

.PHONY: all clean fclean re