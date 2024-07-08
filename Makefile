all : server client
	cc -Wall -Wextra -Werror server.c -o server
	cc -Wall -Wextra -Werror client.c -o client

clean : 
	rm -f client server client_bonus server_bonus

re : clean all

bonus :
	rm -f client_bonus server_bonus
	cc -Wall -Wextra -Werror client_bonus.c -o client_bonus
	cc -Wall -Wextra -Werror server_bonus.c -o server_bonus