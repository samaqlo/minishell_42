# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 11:11:05 by astalha           #+#    #+#              #
#    Updated: 2023/06/23 16:19:11 by ohaimad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	libft/ft_isalnum.c libft/ft_isprint.c libft/ft_memcmp.c libft/ft_strlcat.c libft/ft_strncmp.c  libft/ft_isalpha.c libft/ft_strnstr.c\
		libft/ft_calloc.c libft/ft_strtrim.c libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putendl_fd.c\
		libft/ft_strchr.c  libft/ft_strlcpy.c  libft/ft_tolower.c libft/ft_bzero.c   libft/ft_isascii.c\
		libft/ft_atoi.c libft/ft_strjoin.c libft/ft_itoa.c libft/ft_putchar_fd.c libft/ft_memcpy.c\
		libft/ft_memmove.c   libft/ft_strlen.c  libft/ft_strrchr.c libft/ft_toupper.c  libft/ft_isdigit.c\
		libft/ft_memchr.c  libft/ft_memset.c libft/ft_strdup.c libft/ft_substr.c libft/ft_split.c libft/ft_putstr_fd.c libft/ft_putnbr_fd.c\
		parsing/minishell.c parsing/lexer.c parsing/linkedlist.c parsing/ft_substr_parse.c parsing/cleaner.c\
		execution/execution.c parsing/error_centre.c parsing/linkedlist_p_to_e.c parsing/the_expander.c execution/utils.c\
		execution/builtin.c execution/builtin_rest.c execution/built_src.c execution/built_src1.c execution/built_src2.c parsing/ft_strcmp.c \
		parsing/ft_strrchr_env.c parsing/here_doc.c parsing/here_doc_expand.c parsing/parser.c parsing/red.c\
		parsing/checkers.c parsing/tby_shell.c parsing/the_expander_utils.c parsing/the_expander_utils_2.c\
		parsing/the_expander_utils_3.c parsing/lexer_utils_1.c parsing/lexer_utils.c parsing/here_doc_utils.c\
		parsing/parser_utils.c parsing/red_utils.c parsing/red_utils_1.c \
		parsing/red_utils_2.c parsing/syntaxe_checker.c execution/export_funcs.c execution/built_exit.c execution/built_echo.c execution/execution_utils2.c execution/execution_utils.c

OBJS	= $(SRCS:.c=.o)
CC 		= cc
RM		= rm -rf
AR		= ar rc
FLAGS	= -Wall -Wextra -Werror
NAME	= minishell

%.o: %.c minishell.h  
	$(CC) $(FLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -L $(shell brew --prefix readline)/lib -lreadline -o $(NAME)

.PHONY: all clean fclean re 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
