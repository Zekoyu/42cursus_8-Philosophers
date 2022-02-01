SRCS = 	create_philos.c \
		philo_actions.c \
		philo_utils.c \
		philo.c \
		ft_utils.c

OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

CC = gcc

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[0;96mCompiling \033[1;96m$<"

$(NAME):	$(OBJS)
	@echo "\033[0;95mLinking \033[0;95m($(OBJS)) into \033[1;35m$(NAME) "
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[1;92mDONE"	

all:		$(NAME)

clean:
	@rm -f $(OBJS)
	@echo "\033[0;91mRemoving \033[0;31m$(OBJS)"

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re
