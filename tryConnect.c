#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <string.h>


#define MAXLEN 255


int checkInput(int, char*, char*);
int isNum(char*);


int main(int argc, char** argv){

	int port = 0;
	char* address;
	int inputStatus = 0;
	int socketf;
	int checkConn = 0;
    struct sockaddr_in serv_addr;

	inputStatus = checkInput(argc, argv[1], argv[2]);

	if(!inputStatus){
		printf("Wrong arguments\nUsage: tryConnect ip address port\n");
		return 0;
	}

	port = atoi(argv[2]);
	address = argv[1];


	socketf = socket(PF_INET, SOCK_STREAM, 0);

	if(socketf < 0){
		printf("Error: socket creation failed\n");
		shutdown(socketf, 2);
		return -1;
	}


	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(address);
	serv_addr.sin_port = htons(port);

	printf("Trying to connect to %s:%d\n", address, port);

	checkConn = connect(socketf, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	if(checkConn < 0)
		printf("No response from %s on %d\n", address, port);
	else 
		printf("Port %d is open on %s\n", port, address);
	

	shutdown(socketf, 2);

	return 0;
}


//Check input, improvable
int checkInput(int argc, char* address, char* port){

	if(argc < 3 || !isNum(port))
		return 0;
	
}


int isNum(char* str){

	int len = strlen(str);

	for(int i = 0; i < len && i < MAXLEN; i++)
		if(str[i] < '0' || str[i] > '9')
			return 0;

	return 1;
}