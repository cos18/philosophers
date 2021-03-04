# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/28 17:12:56 by sunpark           #+#    #+#              #
#    Updated: 2021/03/03 18:12:44 by sunpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c \
		utils/number_utils.c

SRCDIR	= ./srcs/
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(SRCS:.c=.o)

INCDIR	= ./includes/

NAME	= philo_one

GCC		= gcc
GCCFLAG	= -Wall -Wextra -Werror -lpthread
RM		= rm -f

%.o:		%.c
			$(GCC) $(GCCFLAG) -I$(INCDIR) -c $< -o $@

$(NAME):	$(OBJS)
			$(GCC) $(GCCFLAG) -I$(INCDIR) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
