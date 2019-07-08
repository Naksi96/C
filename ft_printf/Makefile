# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doyang <doyang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 18:56:55 by doyang            #+#    #+#              #
#    Updated: 2019/03/07 13:44:38 by doyang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			libftprintf.a
CC =			gcc
FLAGS =			-Werror -Wall -Wextra
SRCDIR =		src/
OBJDIR =		obj/
IDIR =			include/
SOURCE =		
OBJ =			$(SOURCE:.c=.o)
OBJCOMP =		$(addprefix $(OBJDIR), $(OBJ))
EXT =			$(IDIR)ft_printf.h

#main
SOURCE += ft_printf.c
#utility
SOURCE += ft_atoi.c
SOURCE += ft_itoa.c
SOURCE += ft_isdigit.c
SOURCE += ft_iswhitespace.c
SOURCE += ft_isalpha.c
SOURCE += ft_countdigit.c
SOURCE += ft_memdel.c
SOURCE += ft_tolower.c
SOURCE += ft_isupper.c
SOURCE += checker.c
SOURCE += handle_etc.c
SOURCE += handle_etc_ext.c
SOURCE += get_etc.c
#print
SOURCE += ft_putchar.c
SOURCE += ft_putstr.c
SOURCE += ft_putnbr.c
SOURCE += print_type.c
SOURCE += print_type_ext.c
#str
SOURCE += ft_strnew.c
SOURCE += ft_strlen.c
SOURCE += ft_memalloc.c
SOURCE += ft_memset.c
SOURCE += ft_bzero.c
SOURCE += function_call.c
SOURCE += ft_strcmp.c
SOURCE += ft_strncmp.c
SOURCE += ft_strjoin.c
SOURCE += ft_strcpy.c
SOURCE += ft_strcat.c
SOURCE += ft_strdup.c
SOURCE += ft_strncpy.c
SOURCE += ft_strchr.c

all: $(NAME)

##actual make
$(NAME): $(OBJCOMP)
	ar rc $(NAME) $(OBJCOMP)
	ranlib $(NAME)

$(OBJCOMP): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)	

$(OBJDIR)%.o: $(SRCDIR)%.c $(EXT)
	$(CC) $(FLAGS) -c $< -o $@ -I $(IDIR)

norm:
	@norminette $(SRCDIR) $(IDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

test:
	$(CC) main.c -o test -I $(IDIR) -L ./ -lftprintf

testclean:
	@rm test

testre: testclean re test
