#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>


void console_main(int in_fd, int out_fd){
	while(1) {
		char line[100];
		//read(STDIN_FILENO,line,sizeof(line));
		fgets(line,sizeof(line),stdin);
		write(out_fd,line,sizeof(line));
		char line2[100];
		read(in_fd,line2,sizeof(line2));
		printf("\nRecieved:[%s]\n", line2);
	}
}


int main(){
	//Connect to Well Known Pipe
	int server_main;
	server_main=open("server_main",O_WRONLY);

	//Send PID Pipe to Server
	char buffer[20];
	sprintf(buffer, "%d", getpid());
	printf("Buffer: %s\n",buffer);
	mkfifo(buffer, 0644);
	int client_receive;
	client_receive=open(buffer, O_RDWR);
	write(server_main,buffer,sizeof(buffer));

	//Confirm connection then remove pipe
	char confirm[20];
	read(client_receive,confirm,sizeof(confirm));
	if(!strcmp(confirm,buffer)){
		remove(buffer);
        printf("\n%s\n\n", "Connection Established");
    }

	//Send Back and Forth
	console_main(client_receive, server_main);





	/*
	   mkfifo("to_processor",0644);
	    mkfifo("to_console",0644);

	    int out_fd,in_fd;
	    in_fd=open("to_console", O_RDONLY);
	    out_fd=open("to_processor", O_WRONLY);
	   printf("Pipe Opened:\n");
	   //char testtest[6];
	   //read(in_fd,testtest,6);
	   //printf("%s\n",testtest);
	 */

	//
	// CONSOLE-PROCESSSOR STUFF
	//
	/*
	    while(1) {
	    char line[100];
	            //read(STDIN_FILENO,line,sizeof(line));
	    fgets(line,sizeof(line),stdin);
	            write(out_fd,line,sizeof(line));
	    char line2[100];
	            read(in_fd,line2,sizeof(line2));
	    printf("\nRecieved:[%s]\n", line2);
	    }
	 */
	//
	// CONSOLE-PROCESSSOR STUFF
	//

	//close(out_fd);
	//close(in_fd);
	//remove("to_console");
	//remove("to_processor");

	return 0;
}
