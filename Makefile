# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinto-r <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 01:47:02 by rpinto-r          #+#    #+#              #
#    Updated: 2022/02/10 03:03:20 by rpinto-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###
CC         = gcc
WARN_FLAG  = -Werror -Wextra -Wall
DEBUG_FLAG = -g3 -fsanitize=leak
RM         = rm -rf
NORM       = norminette

NAME       = minishell
INC        = ./incs
SRC_DIR    = ./srcs
SRC_NAME   = main.c builtin.c command.c error.c signal.c varenv.c
SRC_NAME  += utils/array_utils.c utils/env_utils.c utils/utils.c
SRC_NAME  += builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c
SRCS       = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
OBJS       = $(SRCS:.c=.o)

LIBRL_FLAG = -lreadline
ifeq ($(shell uname), Linux)
    LIBRL_DIR = /usr/lib
    LIBRL_INC = /usr/include
else
    LIBRL_DIR = $(HOME)/.brew/opt/readline/lib
    LIBRL_INC = $(HOME)/.brew/opt/readline/include
endif

LIBFT_FLAG = -lft
LIBFT_DIR  = ./libft
LIBFT_A    = ./libft/libft.a

### RULES ###
all: $(NAME)

.c.o:
	$(CC) $(WARN_FLAG) -I $(INC) -I $(LIBRL_INC) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(LIBRL_FLAG) $(LIBFT_FLAG) -L $(LIBFT_DIR) -L $(LIBRL_DIR) -o $(NAME) 

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

run:
	./$(NAME)

norm:
	$(NORM)

dev: re all

sandbox:
	$(CC) sandbox/pipe_infile.c $(DEBUG_FLAG) $(LIBRL_FLAG) -I $(INC) -I $(LIBRL_INC) $(LIBFT_A) -o $(NAME) && ./$(NAME) hello world
	
.PHONY: all clean fclean re sandbox