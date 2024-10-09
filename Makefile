# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivotints <ivotints@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/24 12:41:50 by ivotints          #+#    #+#              #
#    Updated: 2024/10/09 14:03:04 by ivotints         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= PmergeMe
NAME2	= checker
SRCS	= main.cpp PmergeMe.cpp
OBJ_DIR	= obj
OBJS	= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
CFLAGS	= -Wall -Wextra -Werror -std=c++98
CC		= c++
INCLUDE	= includes/
VPATH	= src/


all: $(NAME) $(NAME2)

$(OBJ_DIR)/%.o: %.cpp
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
#	@echo $(NAME) done

$(NAME2):
	@$(CC) $(CFLAGS) Checker.cpp -o $(NAME2)


$(OBJ_DIR):
	@mkdir -p $@

run: $(NAME)
	@./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "`

trun: $(NAME)
	@./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "` | ./$(NAME2)

vrun: $(NAME)
	@valgrind --leak-check=full --show-error-list=yes ./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "`

clean:
	@rm -rf $(OBJ_DIR)
#@echo removed $(OBJ_DIR) folder

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME2)
#@echo removed $(NAME)

re: fclean all

.PHONY: all run vrun trun erun clean fclean re

