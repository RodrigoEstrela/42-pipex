# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 10:31:48 by fde-albe          #+#    #+#              #
#    Updated: 2022/06/20 16:15:33 by rdas-nev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=		pipex.c pipex_utils.c ft_memcmp.c ft_split.c ft_strlen.c \
					ft_substr.c ft_strdup.c ft_strjoin.c ft_strchr.c children.c \
					arranjar_cmd.c ficheirodasbarraspontoc.c \

OBJS 		=		$(addprefix objs/,$(SRCS:.c=.o))

BONUS_SRCS	=		pipex.c pipex_utils.c ft_memcmp.c ft_split.c \
					ft_substr.c ft_strdup.c children.c \
					arranjar_cmd.c ficheirodasbarraspontoc.c  heredoc.c \
				get_next_line.c get_next_line_utils.c \

OBJS_BONUS	=		$(addprefix objs_bonus/,$(BONUS_SRCS:.c=.o))

CFLAGS		=		#-Wall -Wextra -Werror -g

RM			=		rm -f

NAME		= 		pipex

BONUS		=		pipex_bonus

objs/%.o: srcs/%.c
			@mkdir -p objs
			@cc $(CFLAGS) -c $< -o $@

objs_bonus/%.o: bonus/%.c
			@mkdir -p objs_bonus
			@cc $(CFLAGS) -c $< -o $@

$(NAME):    	$(OBJS)
			@cc $(OBJS) $(CFLAGS) -o $(NAME)

all:      	$(NAME)

bonus:		$(OBJS_BONUS)
			@cc $(OBJS_BONUS) $(CFLAGS) -o $(BONUS)
clean:
			@$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			@$(RM) $(NAME) $(BONUS)

chrome:
			@echo "Opening Google Chrome..."
			@sleep 2
			@launchapp /Applications/Google\ Chrome.app

parrot:
			@echo "Parroting..."
			@sleep 2
			@launchapp /Applications/iTerm.app

re:         fclean all
