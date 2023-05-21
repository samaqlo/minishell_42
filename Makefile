# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astalha <astalha@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 11:11:05 by astalha           #+#    #+#              #
#    Updated: 2023/05/22 00:07:35 by astalha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = libft/ft_isalnum.c libft/ft_isprint.c libft/ft_memcmp.c libft/ft_strlcat.c libft/ft_strncmp.c  libft/ft_isalpha.c libft/ft_strnstr.c libft/ft_calloc.c libft/ft_strtrim.c libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putendl_fd.c\
		libft/ft_strchr.c  libft/ft_strlcpy.c  libft/ft_tolower.c libft/ft_bzero.c   libft/ft_isascii.c libft/ft_atoi.c libft/ft_strjoin.c libft/ft_itoa.c libft/ft_putchar_fd.c libft/ft_memcpy.c\
		libft/ft_memmove.c   libft/ft_strlen.c  libft/ft_strrchr.c libft/ft_toupper.c  libft/ft_isdigit.c libft/ft_memchr.c  libft/ft_memset.c libft/ft_strdup.c libft/ft_substr.c libft/ft_split.c libft/ft_putstr_fd.c libft/ft_putnbr_fd.c\
		minishell.c lexer.c linkedlist.c ft_substr_parse.c cleaner.c syntaxe.c built.c ft_strcmp.c ft_strrchr_env.c 

OBJS	= $(SRCS:.c=.o)
CC 		= cc
RM		= rm -rf
AR		= ar rc
FLAGS	= -Wall -Werror -Wextra
NAME	= minishell

.PHONY: all clean fclean re 

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -lreadline $(OBJS) -o $(NAME)
	
all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
