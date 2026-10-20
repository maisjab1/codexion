NAME = codexion

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c \
       validate.c \
       utils.c\
       init.c \
       simulation.c\
	   queue.c\
	   scheduler.c\
	   clean.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 

