#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[2000],client_message[2000],a[2000];
	
	//clean buffer
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	
	//create socket
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(socket_desc < 0)
	{
		printf("\nError while creating socket\n");
		return -1;
	}
	printf("\nSocket created successfully\n");
	
	//set port and ip
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	//bind to the set port and ip
	if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("\nUnable to connect\n");
		return -1;
	}
	printf("\nConnected with server\n");
	
	printf("Enter the message to server:\n");
	scanf("%s",a);
	//Message to server
	strcpy(client_message,a);
	
	if(send(socket_desc,client_message,strlen(client_message),0) < 0)
	{
		printf("\nCouldn't Send\n");
		return -1;
	}
	
	//Recieve client's message
	if(recv(socket_desc,server_message,sizeof(server_message),0) < 0)
	{
		printf("\nCouldn'd recieve\n");
		return -1;
	}
	printf("\nMsg from Server: %s",server_message);
	
	
	//Closing socket
	close(socket_desc);
	
	return 0;
}
