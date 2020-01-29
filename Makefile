CC = gcc
CFLAGS = -Wall -Werror -Wextra

#includes windows WSL
INCLUDES_WIN_WSL = -L/usr/local/lib -lmlx -lm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lbsd
INCLUDES_MAC = -lmlx -framework OpenGL -framework AppKit

INCLUDES_COMMON = -I./headers/common -I./libft -I./get_next_line
INCLUDES_VANILLA = $(INCLUDES_COMMON) -I./headers/vanilla
INCLUDES_BONUS = $(INCLUDES_COMMON) -I./headers/bonus

#minirt headers
# HEADERS = headers/camera.h \
# 		headers/color.h \
# 		headers/bmpsave.h \
# 		headers/light.h \
# 		headers/macro.h \
# 		headers/material.h \
# 		headers/objs.h \
# 		headers/parser.h \
# 		headers/ray.h \
# 		headers/raytracer.h \
# 		headers/raytracerstruct.h \
# 		headers/render.h \
# 		headers/vec3.h \
# 		headers/world.h \

# HEADERS_BONUS = headers/threads.h \
# HEADERS_VANILLA = headers/threads.h \

#minirt sources
VEC3_SRCS = srcs/common/vec3/misc.c \
			srcs/common/vec3/addsub.c \
			srcs/common/vec3/multiply.c \
			srcs/common/vec3/rotate1.c \
			srcs/common/vec3/rotate2.c \
			srcs/common/vec3/vec3.c \

#libft srcs, need tp fix this oneday
LIBFT_SRCS = libft/ft_atoi.c \
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


SRCS_COMMON = 	$(VEC3_SRCS) \
				srcs/common/bmpsave.c \
				srcs/common/collision.c \
				srcs/common/material.c \
				srcs/common/color.c \
				srcs/common/normals.c \
				srcs/common/camera.c \
				srcs/common/cameramov.c \
				srcs/common/ray.c \
				srcs/common/ray2.c \
				srcs/common/objtypes.c \
				srcs/common/objtypes2.c \
				srcs/common/obj3d.c \
				srcs/common/world.c \
				srcs/common/parsing/utilsparsers.c \
				srcs/common/parsing/objparsers1.c \
				srcs/common/parsing/objparsers2.c \
				srcs/common/parsing/parser.c \
				$(LIBFT_SRCS) \
				$(GET_NEXT_LINE_SRCS)

SRCS_VANILLA =	srcs/vanilla/keyevents.c \
				srcs/vanilla/render.c \
				srcs/vanilla/main.c \
				srcs/vanilla/window.c \
				srcs/vanilla/mainutils.c \
		
SRCS_BONUS =	srcs/bonus/barrier_bonus.c \
				srcs/bonus/keyevents_bonus.c \
				srcs/bonus/main_bonus.c \
				srcs/bonus/render_bonus.c \
				srcs/bonus/threads_bonus.c \
				srcs/bonus/window_bonus.c \
				srcs/bonus/mainutils_bonus.c \

OBJS_COMMON = $(SRCS_COMMON:%.c=objs/%.o)
OBJS_VANILLA = $(OBJS_COMMON) $(SRCS_VANILLA:%.c=objs/%.o)
OBJS_BONUS = $(OBJS_COMMON) $(SRCS_BONUS:%.c=objs/%.o)

NAME = miniRT

$(OBJS_VANILLA) : INCLUDES_COMP=$(INCLUDES_VANILLA) 
$(OBJS_BONUS) : INCLUDES_COMP=$(INCLUDES_BONUS) 

all: $(NAME)  

$(NAME): $(OBJS_VANILLA) 
	$(CC) $(CFLAGS) -O3 $(OBJS_VANILLA) $(INCLUDES_VANILLA) $(INCLUDES_MAC) -o $(NAME)

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) -O3 $(OBJS_BONUS) $(INCLUDES_BONUS) $(INCLUDES_MAC) -o $(NAME)

clean:
	$(RM) -f $(OBJS_BONUS)
	$(RM) -f $(OBJS_VANILLA)

fclean: clean
	$(RM) $(NAME)
	$(RM) save.bmp

re: fclean all

objs/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES_COMP)

test: $(NAME)
	./minirt ./test/map.rt -save
test_wsl:
	$(CC) $(CFLAGS) $(SRCS) -g -fsanitize=address -I./headers -I./libft -I./get_next_line -o ./test/run_tests $(INCLUDES_WIN_WSL)
test_mac: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -g -I./headers -I./libft -I./get_next_line -o ./test/run_tests $(INCLUDES_MAC)
test_vec3:
	$(CC) $(CFLAGS) -g3 test/vec3_test.c $(VEC3_SRCS) -I headers -o ./test/run_tests -lm
