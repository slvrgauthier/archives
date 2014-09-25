CC=g++
SOCK=sock.cc sockdist.cc

all : 
	make serveur_Chat 
	make client_Chat

serveur_Chat : serveur_Chat.cc
	$(CC) -o $@ $+ $(SOCK)

client_Chat : client_Chat.cc
	$(CC) -o $@ $+ $(SOCK)
