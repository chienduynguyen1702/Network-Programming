# main: ./TCP_Client/client ./TCP_Server/server

# ./TCP_Client/client: ./TCP_Client/TCP_client.c
# 	gcc ./TCP_Client/TCP_client.c -o ./TCP_Client/client

# ./TCP_Server/server: ./TCP_Server/TCP_server.c ./TCP_Server/lib/*
# 	gcc ./TCP_Server/TCP_server.c -o ./TCP_Server/server

# clean:
# 	rm -f ./TCP_Client/client ./TCP_Server/server
CC = gcc
CFLAGS = -Wall

TCP_CLIENT_DIR = TCP_Client
TCP_SERVER_DIR = TCP_Server

TCP_CLIENT_SRC = $(wildcard $(TCP_CLIENT_DIR)/*.c)
TCP_SERVER_SRC = $(wildcard $(TCP_SERVER_DIR)/*.c) $(wildcard $(TCP_SERVER_DIR)/lib/*.h)

all: client server

client: $(TCP_CLIENT_DIR)/client

server: $(TCP_SERVER_DIR)/server

$(TCP_CLIENT_DIR)/client: $(TCP_CLIENT_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(TCP_SERVER_DIR)/server: $(TCP_SERVER_SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TCP_CLIENT_DIR)/client $(TCP_SERVER_DIR)/server
