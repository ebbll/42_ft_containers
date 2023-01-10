# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunlee <eunlee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 15:02:13 by eunlee            #+#    #+#              #
#    Updated: 2023/01/10 16:19:04 by eunlee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC							=		c++
CXXFLAG						=		-std=c++98 -Wall -Wextra -Werror
RM							=		rm

NAME						=		ft_containers
SRC_DIR						=		./srcs/
HEADER						=		./includes/
SRC_LIST					=		main.cpp

SRC							=		$(addprefix $(SRC_DIR), $(SRC_LIST))
OBJS						=		$(SRC:.cpp=.o)

%.o							:		%.cpp
		$(CC) $(CXXFLAG) -I $(HEADER) -c $< -o $@

$(NAME)						:		$(OBJS)
		$(CC) $(CXXFLAG) -I $(HEADER) $(OBJS)  -o $(NAME)

.PHONY						:		all
all							:		$(NAME)

.PHONY						:		clean
clean						:
		$(RM) $(OBJS)

.PHONY						:		fclean
fclean						:		clean
		$(RM) $(NAME)

.PHONY						:		re
re							:		fclean all

.PHONY						:		test
test						:
	@make -C ./tester/benchmark1
	@make -C ./tester/benchmark2 bench
	@make -C ./tester/tester1