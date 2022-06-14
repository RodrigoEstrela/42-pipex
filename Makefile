# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 10:31:48 by fde-albe          #+#    #+#              #
#    Updated: 2022/06/08 17:01:58 by fde-albe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=		pipex.c pipex_utils.c ft_memcmp.c ft_split.c ft_strlen.c \
					ft_substr.c ft_strdup.c ft_strjoin.c \

OBJS 		=		$(addprefix objs/,$(SRCS:.c=.o))

CFLAGS		=		-Wall -Wextra -Werror -g

RM			=		rm -f

NAME		= 		pipex

all:        	$(NAME)

objs/%.o: srcs/%.c
			@mkdir -p objs
			@cc $(CFLAGS) -c $< -o $@

$(NAME):    	$(OBJS)
			@cc $(OBJS) $(CFLAGS) -o $(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

chrome:
			@echo "Opening Google Chrome"
			@sleep 2
			@launchapp /Applications/Google\ Chrome.app

parrot:
			@echo "Parroting.."
			@sleep 2
			@launchapp /Applications/iTerm.app

re:         fclean all
