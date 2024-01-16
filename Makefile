NAME			=	fract-ol

BONUS			=	fract-ol_bonus

LIBFT			=	libft.a

LIBFT_PATH		=	libft/

HEADER			=	-Iinclude -Ilibft/include -I/usr/include/X11 -Iminilibx-linux

MLX_PATH		=	minilibx-linux/

MLX				=	libmlx_Linux.a

MLX_FLAG 		=	-Lmlx -Lminilibx-linux -L/usr/lib/X11 -lXext -lX11

MATH_FLAG		=	-lm -lz

SRC_PATH		=	src/

OBJ_PATH		=	obj/

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra

RM				=	rm -rf

AR				=	ar rcs

SRCS			=	main.c \
					free.c \
					colors.c \
					colors_rgb.c \
					julia.c \
					mandelbrot.c \
					tricorn.c \
					screen.c \
					init_fractal.c \
					check.c \
					parse.c \
					handle_input.c \
					handle_input2.c

OBJS			=	${SRCS:.c=.o}

SRCS_D			=	$(addprefix ${SRC_PATH}, ${SRCS})

OBJS_D			=	$(addprefix ${OBJ_PATH}, ${OBJS})

LIBFT_D			=	$(addprefix ${LIBFT_PATH}, ${LIBFT})

all:			${NAME}

bonus:			${BONUS}

${BONUS}:		${LIBFT} ${MLX} ${OBJS_D}
		${CC} ${CFLAGS} -o ${BONUS} ${OBJS_D} ${HEADER} ${MATH_FLAG} ${MLX_FLAG} ${LIBFT} ${MLX}

${NAME}:		${LIBFT} ${MLX} ${OBJS_D}
		${CC} ${CFLAGS} -o ${NAME} ${OBJS_D} ${HEADER} ${MATH_FLAG} ${MLX_FLAG} ${LIBFT} ${MLX}

${OBJ_PATH}%.o:	${SRC_PATH}%.c
		mkdir -p ${OBJ_PATH}
		${CC} -g ${CFLAGS} ${HEADER} -c $< -o $@

${LIBFT}:
		make -C ${LIBFT_PATH}
		cp ${LIBFT_PATH}${LIBFT} .

${MLX}:
		${RM} ${MLX_PATH}
		git clone https://github.com/42Paris/minilibx-linux
		make -C ${MLX_PATH}
		cp ${MLX_PATH}${MLX} .

clean:
		make -C ${LIBFT_PATH} clean
		make -C ${MLX_PATH} clean
		${RM}  ${OBJS_D}

fclean:		clean
		make -C ${LIBFT_PATH} fclean
		${RM} ${MLX_PATH}
		${RM} ${NAME} ${BONUS} ${LIBFT} ${MLX}

re:			fclean all

.PHONY:		all fclean clean re libft


