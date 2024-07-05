#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	int socket_desc,client_sock,client_size;
	struct sockaddr_in server_addr,client_addr;
	char server_message[2000],client_message[2000];
	int client_struct_length=sizeof(client_addr);
	
	//Clean buffer
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	
	//Create socket
	socket_desc=socket(AF_INET,SOCK_DGRAM,0);
	
	if(socket_desc < 0)
	{
		printf("\nError while creating socket\n");
		return -1;
	}
	printf("\nSocket created successfully\n");

	//Set port and ip
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	//Bind to the set port and ip
	if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("\nCouldn't bind to the port\n");
		return -1;
	}
	printf("\nDone with binding\n");
	
	
	
	//Recieve client's message
	if(recvfrom(socket_desc,client_message,sizeof(client_message),0,(struct sockaddr*)&client_addr, &client_struct_length) < 0)
	{
		printf("\nCouldn'd recieve\n");
		return -1;
	}
	
	printf("Received message from IP:%s and port=%i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	printf("\nMsg from client: %s",client_message);
	//Respond to client
	strcpy(server_message,"THIS MESSAGE FROM SEVER\n");
	
	if(sendto(socket_desc,server_message,strlen(server_message),0,(struct sockaddr*)&client_addr,client_struct_length) < 0)
	{
		printf("\nCouldn't Send\n");
		return -1;
	}
	
	//Closing socket
	close(socket_desc);
	
	return 0;
}
