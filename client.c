#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

void error(const char *msg){
    perror(msg);
    exit(0);}


int main(){
char buffer[256];
int n;
int sockfd;
struct sockaddr_in server;
sockfd = socket(AF_INET , SOCK_STREAM , 0);
server.sin_family = AF_INET; 
server.sin_addr.s_addr = INADDR_ANY; 
server.sin_port = htons( 52698 );
connect(sockfd, (void *)(&server), sizeof(server));
char abc[100];
    int x=0;
    char a = 'a';
    double amount;
    while(1){
    bzero(buffer,256);						
    n = read(sockfd,buffer,255);				//Read Server String(server asking for user id)
    if (n < 0) 
         error("ERROR reading from socket");
    if(strncmp("msg" , buffer , 3)==0){
            printf("%s\n",buffer);
            write(sockfd, &a, sizeof(a));
            }
    else if(strncmp("select option" , buffer , 13)==0){
    printf("%s\n",buffer);
    scanf("%d",&x);
    write(sockfd, &x, sizeof(x));
    }
    else if(strncmp("Enter amount" , buffer , 12)==0){
    printf("%s\n",buffer);
    scanf("%lf",&amount);
    write(sockfd, &amount, sizeof(amount));
    }
    else if(strncmp("bye" , buffer , 3)==0) {
        printf("%s\n",buffer);
        write(sockfd, &a, sizeof(a));
        goto EXIT;
    }
    
    else{
    printf("%s\n",buffer);
    bzero(abc,100);
    scanf("%s",abc);
    write(sockfd, abc, sizeof(abc));
    }}
////////////////////////////////////////////////
    EXIT:



return 0;
}
