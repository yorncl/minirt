CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./libft.h

SRCS = ft_isspace.c ft_atof.c ft_min.c ft_max.c ft_intlen.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putnbr_fd.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c 
SRCS_B = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c
OBJS = ${SRCS:.c=.o}
OBJS_B = ${SRCS_B:.c=.o}

SRCS_TEST = tests/libft_test.c
BIN_TEST = tests/run_test

LIB = libft.a
LIB_B = libft_bonus.a


NAME = libft.a


all : ${NAME}

$(NAME) :  ${OBJS}
	ar rcs ${LIB} ${OBJS}

bonus : ${OBJS_B} ${OBJS}
	ar rcs ${LIB} ${OBJS} ${OBJS_B}

re : fclean all

clean :
	rm -f ${OBJS}
	rm -f ${OBJS_B}

fclean : clean
	rm -f ${LIB} ${BIN_TEST}

test : bonus
	${CC} ${CFLAGS} -fsanitize=address -g3 -I . ${SRCS_TEST} ${LIB} -o ${BIN_TEST}
	