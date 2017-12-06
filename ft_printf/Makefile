# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asyed <asyed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 01:09:10 by asyed             #+#    #+#              #
#    Updated: 2017/11/27 15:56:25 by asyed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CFLAGS += -Wall -Werror -Wextra

SRC = ft_printf.c \
		integer.c \
		length.c \
		num_fetch.c \
		parse.c \
		special.c \
		strings.c \
		tools.c \
		utils.c \
		buffer.c \
		flags.c \
		special.c \
		wide.c \
		format.c \
		libft/ft_tolower.c \
		libft/ft_strcmp.c \
		libft/ft_putstr.c \
		libft/ft_putnbr.c \
		libft/ft_putchar.c \
		libft/ft_bzero.c \
		libft/ft_atoi.c \
		libft/ft_isdigit.c \
		libft/ft_isspace.c \
		libft/ft_isupper.c \
		libft/ft_memset.c \
		libft/ft_putnbr_fd.c \
		libft/ft_putstr_fd.c \
		libft/ft_putchar_fd.c \
		libft/ft_strlen.c \
		libft/ft_uputnbr_fd.c \
		libft/ft_uputnbr.c \
		libft/ft_wcslen.c \


SRC_OBJ = $(subst .c,.o, $(SRC))		

LIBFT = libft/libft.a

all: $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $^ -o $@

$(NAME): $(SRC_OBJ)
	@/bin/rm -f $(NAME)
	@ar rcs $(NAME) $(SRC_OBJ)
	@echo "\033[32mBuilt\033[0m"

clean:
	@/bin/rm -f $(SRC_OBJ)
	@echo "\033[32mCleaned\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo "\033[32mRemoved Executable\033[0m"

re: clean all