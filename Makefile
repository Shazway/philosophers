# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/06 23:27:53 by tmoragli          #+#    #+#              #
#    Updated: 2022/02/17 17:09:24 by tmoragli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO	= 	philo

SRCS	=	srcs/philosophers.c			\
			srcs/utils.c				\
			srcs/parsing.c				\

INCLUDES	=	-Iincludes

OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
RM			=	@rm -f

LD_FLAGS	=	-fsanitize=address
FLAGS		=	-Wall -Werror -Wextra $(INCLUDES) -g

.c.o:
				$(CC) -c $< -o $(<:.c=.o) $(FLAGS)

all:			start_message $(PHILO)

$(PHILO):		$(OBJS) start_link
				$(CC) $(OBJS) $(FLAGS) -o $(PHILO) $(LD_FLAGS)
				@echo "\033[1;31mphilosophers\033[0m is ready to use!"

clean:
#					@clear
					@echo "\033[0;33mCleaning \033[1;31mphilosophers\033[0;33m's objects\033[0m"
					$(RM) $(OBJS)

fclean:
					@echo "\033[0;33mRemoving \033[1;31mphilosophers\033[0;33m.\033[0m"
					$(RM) $(PHILO) $(OBJS)
					$(RM) $(OBJS)
start_message:
#				@clear
				@echo "\033[0;31mMaking \033[1;31mphilosophers"
				@echo "\033[1;32mCompiling objects\033[0;32m"

start_link:
				@echo "\033[1;32mLinking all objects\033[0;32m"

re:				fclean all

.PHONY:			all clean fclean re