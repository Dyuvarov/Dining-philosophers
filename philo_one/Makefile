NAME		= philo_one

HEADERS		= philo.h
SRCS		= main.c utils.c error_handler.c init.c actions.c
OBJS		= $(SRCS:.c=.o)

CC			= gcc
FLAGS		= -pthread -Wall -Wextra -Werror -I.

%.o:		%.c $(HEADERS)
			$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

philo_one:	$(OBJS)
			$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:		
			rm -f $(OBJS)
			
fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
