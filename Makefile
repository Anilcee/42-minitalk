NAME	= minitalk
SERVER	= server
CLIENT	= client
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all: $(SERVER) $(CLIENT)

$(SERVER): server.c minitalk.h
	$(CC) $(CFLAGS) server.c -o $(SERVER)

$(CLIENT): client.c minitalk.h
	$(CC) $(CFLAGS) client.c -o $(CLIENT)

clean:
	$(RM) $(SERVER) $(CLIENT)

fclean: clean

re: fclean all

.PHONY: all clean fclean re