# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gregoirebeaumann <gregoirebeaumann@stud    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 14:18:20 by jleroux           #+#    #+#              #
#    Updated: 2023/07/06 11:50:27 by gregoirebea      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ircserv

SRC_DIR		=	src
SRCS		=	$(SRC_DIR)/main.cpp \
				$(SRC_DIR)/Server.cpp \
				$(SRC_DIR)/Client.cpp \
				$(SRC_DIR)/Message.cpp \
				$(SRC_DIR)/Channel.cpp \
				$(SRC_DIR)/join.cpp \
				$(SRC_DIR)/nick.cpp \
				$(SRC_DIR)/user.cpp \
				$(SRC_DIR)/names.cpp \
				$(SRC_DIR)/topic.cpp \
				$(SRC_DIR)/kick.cpp \
				$(SRC_DIR)/mode.cpp \

INCS		=	inc

CXX			=	c++#g++-13
CXXFLAGS	=	-std=c++98 -O2
CPPFLAGS	=	-Wall -Wextra -Werror -pedantic \
				$(addprefix -I,$(INCS)) -MMD -MP \

RM			=	rm -rf

BUILD_DIR	=	bin
OBJS		=	$(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS        =	$(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

run: all
	clear
	./$(NAME) 6667 password

leaks: all
	clear
	-leaks -quiet -atExit -- ./$(NAME) 6667 password

.PHONY: all clean fclean re run leaks
