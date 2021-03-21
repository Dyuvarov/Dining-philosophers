NAME		= philo_three

HEADERS		= philo.h
SRCS		= actions.c error_handler.c init.c main.c sem_utils.c utils.c monitoring.c str_utils.c
OBJS		= $(SRCS:.c=.o)

CC			= gcc
FLAGS		= -pthread -Wall -Wextra -Werror -I.

%.o:		%.c $(HEADERS)
			$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

philo_three:	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:		
			rm -f $(OBJS)
			
fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
