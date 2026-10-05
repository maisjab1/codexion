Name = codexion
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDE = -I  include
SRCS = main.c \
       validate.c \
       init.c \
       simulation.c
OBJS = $(SRCS:.c=.o)
LIB = -L . 

run :
	@cc  $(SRCS) -o codexion
clean:
	@rm codexion

