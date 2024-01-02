NAME			=	fract-ol

LIBFT			=	libft.a

LIBFT_PATH		=	libft/

HEADER			=	-I./include -I./libft/include -I/usr/include/X11

MLX_PATH		=	minilib/minilibx-linux/

MLX				=	libmlx_Linux.a

MLX_FLAG		=	-Lminilibx-linux -lmlx_Linux -lX11 -lXext

MATH_FLAG		=	-lm
#MIMILIB_FLAG	=	-L/usr/X11/lib -lXext --lX11 -lm -lbsd -lmlx

SRC_PATH		=	src/

OBJ_PATH		=	obj/

CC				=	cc

CFLAGS			=

RM				=	rm -f

AR				=	ar rcs

SRCS			=	fractal.c

OBJS			=	${SRCS:.c=.o}

SRCS_D			=	$(addprefix ${SRC_PATH}, ${SRCS})

OBJS_D			=	$(addprefix ${OBJ_PATH}, ${OBJS})

LIBFT_D			=	$(addprefix ${LIBFT_PATH}, ${LIBFT})

all:			${NAME}

#bonus:

${NAME}:		${LIBFT} ${MLX} ${OBJS_D}
		${CC} ${CFLAGS} -g -o ${NAME} ${OBJS_D} ${HEADER} ${MATH_FLAG} ${MLX_FLAG} ${LIBFT}

${OBJ_PATH}%.o:	${SRC_PATH}%.c
		mkdir -p ${OBJ_PATH}
		${CC} -g ${CFLAGS} ${HEADER} -c $< -o $@

${LIBFT}:
		make -C ${LIBFT_PATH}
		cp ${LIBFT_PATH}${LIBFT} .

${MLX}:
		make -C ${MLX_PATH}
		cp ${MLX_PATH}${MLX} .

clean:
		make -C ${LIBFT_PATH} clean
		${RM}  ${OBJS_D}

fclean:		clean
		make -C ${LIBFT_PATH} fclean
		${RM} ${NAME} ${LIBFT}

re:			fclean all

.PHONY:		all fclean clean re libft


