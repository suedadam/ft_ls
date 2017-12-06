# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asyed <asyed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 01:09:10 by asyed             #+#    #+#              #
#    Updated: 2017/12/05 15:55:57 by asyed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS += -Wall -Werror -Wextra

SRC = ft_ls.c \
		directory_handle.c \
		list.c \
		options.c \
		permissions.c \
		sort.c \
		utils.c \
		$(LIBFT)/libft.a \
		$(FTPRINTF)/libftprintf.a \

LIBFT = libft/
FTPRINTF = ft_printf/

all: $(NAME)

$(NAME):
	@make -C $(LIBFT)
	@make -C $(FTPRINTF)
	@gcc $(CFLAGS) $(SRC) -I $(LIBFT) -I $(FTPRINTF) -o $(NAME)
	@echo "\033[32mBuilt\033[0m"

clean:
	@/bin/rm -f $(NAME)
	@make clean -C $(LIBFT)
	@make clean -C $(FTPRINTF)
	@echo "\033[32mCleaned\033[0m"

fclean:
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@make fclean -C $(FTPRINTF)
	@echo "\033[32mRemoved Executable\033[0m"

re: clean all