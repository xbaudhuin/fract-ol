NAME		=	libft.a

SRC_PATH	=	src/

OBJ_PATH	=	obj/

HEADER		=	-I ./include

SRCS		=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_printf.c \
				parse_flags.c \
				print_char.c \
				print_hexa.c \
				print_memory.c \
				print_signed.c \
				print_string.c \
				print_unsigned.c \
				printf_utils.c \
				get_next_line.c \
				get_next_line_utils.c \
				ft_join_split.c

RM			=	rm -f

CFLAGS		=	-Wall -Werror -Wextra

CC			=	cc

AR			=	ar rcs

OBJS		=	${SRCS:.c=.o}

SRCS_D		=	$(addprefix ${SRC_PATH}, ${SRCS})

OBJS_D		=	$(addprefix ${OBJ_PATH}, ${OBJS})

all:		${NAME}

${NAME}:	${OBJS_D}
				${AR} ${NAME} ${OBJS_D}

${OBJ_PATH}%.o:	${SRC_PATH}%.c
			mkdir -p ${OBJ_PATH}
			${CC} ${CFLAGS} ${HEADER} -c $< -o $@

clean:
			${RM} ${OBJS_D}

fclean:			clean
			${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
