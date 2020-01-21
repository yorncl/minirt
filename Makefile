CC = gcc
CFLAGS = -Wall -Werror -Wextra

#includes windows WSL
INCLUDES_WIN_WSL = -L/usr/local/lib -lmlx -lm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lbsd
INCLUDES_MAC = -lmlx -framework OpenGL -framework AppKit

#minirt sources
VEC3_SRCS = srcs/vec3/misc.c \
			srcs/vec3/addsub.c \
			srcs/vec3/multiply.c \
			srcs/vec3/rotate1.c \
			srcs/vec3/rotate2.c \
			srcs/vec3/vec3.c \

#libft srcs, need tp fix this oneday
LIBFT_SRCS = libft/ft_atof.c \
			libft/ft_atoi.c \
			libft/ft_bzero.c \
			libft/ft_calloc.c \
			libft/ft_intlen.c \
			libft/ft_isalnum.c \
			libft/ft_isalpha.c \
			libft/ft_isascii.c \
			libft/ft_isdigit.c \
			libft/ft_isprint.c \
			libft/ft_isspace.c \
			libft/ft_itoa.c \
			libft/ft_lstadd_back_bonus.c \
			libft/ft_lstadd_front_bonus.c \
			libft/ft_lstclear_bonus.c \
			libft/ft_lstdelone_bonus.c \
			libft/ft_lstiter_bonus.c \
			libft/ft_lstlast_bonus.c \
			libft/ft_lstmap_bonus.c \
			libft/ft_lstnew_bonus.c \
			libft/ft_lstsize_bonus.c \
			libft/ft_max.c \
			libft/ft_memccpy.c \
			libft/ft_memchr.c \
			libft/ft_memcmp.c \
			libft/ft_memcpy.c \
			libft/ft_memmove.c \
			libft/ft_memset.c \
			libft/ft_min.c \
			libft/ft_putchar_fd.c \
			libft/ft_putendl_fd.c \
			libft/ft_putnbr_fd.c \
			libft/ft_putstr_fd.c \
			libft/ft_split.c \
			libft/ft_strchr.c \
			libft/ft_strdup.c \
			libft/ft_strjoin.c \
			libft/ft_strlcat.c \
			libft/ft_strlcpy.c \
			libft/ft_strlen.c \
			libft/ft_strmapi.c \
			libft/ft_strncmp.c \
			libft/ft_strnstr.c \
			libft/ft_strrchr.c \
			libft/ft_strtrim.c \
			libft/ft_substr.c \
			libft/ft_tolower.c \
			libft/ft_toupper.c
			
GET_NEXT_LINE_SRCS = 	get_next_line/get_next_line.c \
						get_next_line/get_next_line_utils.c



SRCS = $(VEC3_SRCS) \
		srcs/keyevents.c \
		srcs/collision.c \
		srcs/material.c \
		srcs/color.c \
		srcs/normals.c \
		srcs/camera.c \
		srcs/main.c \
		srcs/ray.c \
		srcs/objtypes.c \
		srcs/obj3d.c \
		srcs/world.c \
		srcs/window.c \
		srcs/parsing/utilsparsers.c \
		srcs/parsing/objparsers1.c \
		srcs/parsing/objparsers2.c \
		srcs/parsing/parser.c \
		$(LIBFT_SRCS) \
		$(GET_NEXT_LINE_SRCS)

test_wsl:
	$(CC) $(CFLAGS) $(SRCS) -g -fsanitize=address -I./headers -I./libft -I./get_next_line -o ./test/run_tests $(INCLUDES_WIN_WSL)
test_mac:
	$(CC) $(CFLAGS) $(SRCS) -g -I./headers -I./libft -I./get_next_line -o ./test/run_tests $(INCLUDES_MAC)
test_vec3:
	$(CC) $(CFLAGS) -g3 test/vec3_test.c $(VEC3_SRCS) -I headers -o ./test/run_tests -lm
