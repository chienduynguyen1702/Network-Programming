main: ./UDP_Client/client ./UDP_Server/server

./UDP_Client/client: ./UDP_Client/udp_client.c
	gcc ./UDP_Client/udp_client.c -o ./UDP_Client/client

./UDP_Server/server: ./UDP_Server/udp_server.c ./UDP_Server/lib/*
	gcc ./UDP_Server/udp_server.c -o ./UDP_Server/server

clean:
	rm -f ./UDP_Client/client ./UDP_Server/server
