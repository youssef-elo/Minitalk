all : server client
	cc -Wall -Wextra -Werror server.c -o server
	cc -Wall -Wextra -Werror client.c -o client

clean : 
	rm client server

re : clean all