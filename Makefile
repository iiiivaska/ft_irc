all:	server client

server:
		g++ main.cpp -o server -w

client:
		g++ client.cpp -o client -w