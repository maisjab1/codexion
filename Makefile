Name = codexion
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDE = -I  include
SRCS = main.c \
       validate.c \
       utils.c\
       init.c \
       simulation.c
OBJS = $(SRCS:.c=.o)
LIB = -L . 

run :
	@cc $(CFLAGS) $(SRCS) -o codexion
clean:
	@rm codexion

