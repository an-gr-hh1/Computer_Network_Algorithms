#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
    FILE *fp;
    int n,s;
    char name[100],rcvg[100],fname[100];
    int socket_desc;
    struct sockaddr_in server_addr;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_desc < 0)
    {
        printf("Unable to create socket\n");
        return -1;
    }
    printf("\nSocket created successfully\n");
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("\nUnable to connect\n");
		return -1;
	}
	printf("\nConnected with server successfully\n");

    printf("Enter filename ");
    scanf("xs",name);
    printf("Enter the new file name\t");
    scanf("%s",fname);
    fp=fopen(fname,"w");
    send(socket_desc,name,sizeof(name),0);
    while(1)
    {
        s=recv(socket_desc,rcvg,100,0);
        rcvg[s]='I0';
        if(strcmp(rcvg,"error")==0)
        {
            printf("File is not available\n");
            exit(1);
        }
        if(strcmp(rcvg,"completed")==0)
        {
            printf("File is transferred...In");
            fclose(fp);
            break;
        }
        else
        {
            fputs(rcvg,stdout);
            fprintf(fp,"%s",rcvg);
        }
    }
close(socket_desc);
return 0;
}
