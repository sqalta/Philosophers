NAME = philo

SRC = main.c control_input.c init.c mutex.c routine.c time_print.c dead.c

CC = gcc

FLAGS = -Wall -Wextra -g 

FLAGS_DATARACE = -fsanitize=thread -g

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

data_race:
	$(CC) $(FLAGS_DATARACE) $(SRC) -o $(NAME)

fclean:
	rm -fr $(NAME)
	rm -fr *.dSYM

clean: fclean
	
re: fclean all

git:
	git add .
	git status
	git commit -m "First Try"
	git push

.PHONY: all clean re