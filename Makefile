#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/16 09:31:29 by lberezyn          #+#    #+#              #
#    Updated: 2018/05/16 09:31:30 by lberezyn         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME        = avm

CC          = clang++

CFLAGS      = -Wall -Wextra -Werror

SRCS        = main.cpp src/Factory.cpp src/avm.cpp

OBJS        = $(SRCS:.cpp=.o)

INCS        = include/MyStack.hpp include/avm.hpp include/Factory.hpp include/MyStack.hpp include/IOperand.hpp include/IOperand_template.hpp

all         : $(NAME)

$(NAME)     : $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\e[38;5;46m./$(NAME)    SUCCESSFULLY BUILD 🎉\e[0m\n"

$(OBJS)     : %.o : %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

clean       :
	@rm -f $(OBJS)
	@printf "🗑  \e[38;5;226mo. files DELETED\e[0m\n"

fclean      : clean
	@rm -f $(NAME)
	@printf "🗑  \e[38;5;226m./$(NAME)    DELETED\e[0m\n"

re          : fclean all

.PHONY: clean fclean re
