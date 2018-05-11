# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fxst1 <fxst1@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/12 10:57:23 by fxst1             #+#    #+#              #
#    Updated: 2018/05/11 14:55:16 by fxst1            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = cc
FLAGS = -Wall -Wextra -Werror -g $(shell pkg-config --cflags gtk+-3.0)
INC = -I inc/ -I libs/libft/
LIBFT = ./libs/libft/libft.a
GNL = ./libs/get_next_line/get_next_line.c
GNL_OBJ = ./obj/get_next_line.o

OBJDIR = ./obj/
LIBS := -L ./libs/libft/ -lft $(shell pkg-config --libs gtk+-3.0)

SERVER_SRC := $(filter %.c, $(shell find srcs/server -type f))
SERVER_OBJ = $(addprefix $(OBJDIR), $(SERVER_SRC:.c=.o))
SERVER = server

CLIENT_SRC := $(filter %.c, $(shell find srcs/client -type f))
CLIENT_OBJ = $(addprefix $(OBJDIR), $(CLIENT_SRC:.c=.o))  $(UI_OBJ)
CLIENT = client

all: $(SERVER) $(CLIENT)

$(CLIENT) : $(LIBFT) $(CLIENT_OBJ)  $(GNL_OBJ)
	$(CC) $(FLAGS) $(INC) -o $(CLIENT) $(GNL_OBJ) $(CLIENT_OBJ) $(LIBS)

$(SERVER) : $(LIBFT) $(SERVER_OBJ)  $(GNL_OBJ)
	$(CC)  $(FLAGS) $(INC) -o $(SERVER) $(GNL_OBJ) $(SERVER_OBJ) -L ./libft/ -lft $(LIBS)

$(GNL_OBJ):
	$(CC) $(FLAGS) -c $(GNL) -o $(GNL_OBJ)

$(OBJDIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

$(LIBFT):
	make -C libs/libft

clean:
	make -C libs/libft clean
	@rm -rf $(OBJDIR)

cleanlib:
	make -C libs/libft fclean

fclean:
	@rm -rf $(OBJDIR)
	@rm -rf $(SERVER)

re: fclean all
