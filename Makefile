
CC = gcc -Wall -Wextra -Werror -o philo

SRC =  ft_atoi.c ft_isdigit.c manage_threads.c philosophers.c routine.c time.c 

NAME = philo

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC)

clean:
	rm -f $(NAME) 

fclean: clean	
	rm -f $(NAME) 

re : fclean all
