#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>


int main(int argc, char **argv)
{
  int sockfd, portno, n;

  struct sockaddr_in serv_addr;
  struct hostent *server;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd == -1){
    perror("Error on creating socket");
    exit(1);
  }

  char buffer[256];

  portno = atoi(argv[2]);

  server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
        perror("ERROR connecting");
        exit(2);
      }
    //printf("Please enter the message: ");
    bzero(buffer,256);
    //fgets(buffer,255,stdin);
    strcpy(buffer, argv[3]);
    printf("%s\n", buffer);
    //char *c;

    int i;
    for(i=0;i<strlen(buffer);i++){
      if((buffer[i] == 'f')|| (buffer[i] == 'r')|| (buffer[i] == 'l')|| (buffer[i] == 'b') || (buffer[i] == 's'))
      {
        char c[2];
        //bzero(c,1);
        sprintf(c,"%c", buffer[i]);
         n = send (sockfd,c,strlen(c), 0);
         if (n < 0){
              perror("ERROR writing to socket");
              exit(3);
              sleep(2);
            }
      }else {
          printf("%c not a command\n", buffer[i]);
          continue;
        }

    }


  close(sockfd);
  return 0;
}