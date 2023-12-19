NAME = philo

SRCS = activities.c\
		check_input.c\
		initialize.c\
		main.c\
		monitor.c\
		utils_philo.c\
		threads.c\

OBJS	= ${SRCS:.c=.o}

HEADERS = -I ./includes

FLAGS	= -g -Wall -Wextra -Werror

RM		= rm -f

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS} ${HEADERS} -o ${NAME}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all, clean, fclean, re