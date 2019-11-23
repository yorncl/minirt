CC = gcc
CFLAGS = -Wall -Werror -Wextra

#includes windows WSL
INCLUDES_WIN_WSL = -L/usr/local/lib -lmlx -lm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lbsd

#minirt sources
VEC3_SRCS = srcs/vec3/addsub.c srcs/vec3/multiply.c srcs/vec3/rotate.c srcs/vec3/vec3.c

test_wsl:
	$(CC) $(CFLAGS) test/main.c $(SRCS)  -I./headers -o ./test/run_tests $(INCLUDES_WIN_WSL)
test_vec3:
	$(CC) $(CFLAGS) -g3 test/vec3_test.c $(VEC3_SRCS) -I headers -o ./test/run_tests
