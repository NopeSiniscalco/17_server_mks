#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

char * capitalize(char * in_args){
	int i;
	for(i=0; i<strlen(in_args); i++) {
		if(in_args[i]=='\n')
			in_args[i]=0;
		else if(in_args[i]>=97 && in_args[i]<=122)
			in_args[i]=in_args[i]-32;
	}

	return in_args;
}

void processor_main(int in_fd, int out_fd){
	while(1) {//IF OTHER STILL ALIVE
		char line[100];
		read(in_fd,line,sizeof(line));
		printf("\nRecieved:%s ...\n", line);
		capitalize(line);
		write(out_fd,line,sizeof(line));
	}
}

int main(){
	while(1) {
		//Make Well Known Pipe
		mkfifo("server_main", 0644);
		int server_main;
		server_main=open("server_main", O_RDWR);

		//Read in PID Pipe
		char line[20];
		read(server_main,line,sizeof(line));
		remove("server_main");
		printf("FIFO PIPE: %s\n", line);

		int client_send;
		client_send=open(line, O_WRONLY);

		//Confirm connection so client can remove Pipe
		write(client_send,line,sizeof(line));
		printf("\n%s\n\n", "Connection Established");


		//Send Back and Forth
		processor_main(server_main, client_send);







		/*
		   mkfifo("to_processor",0644);
		   mkfifo("to_console",0644);

		   int out_fd,in_fd;
		   out_fd=open("to_console", O_WRONLY);
		   in_fd=open("to_processor", O_RDONLY);
		   printf("Pipe Opened:\n");
		   //write(out_fd,"BRUHH",6);
		 */





		//
		// CONSOLE-PROCESSSOR STUFF
		//
		/*
		   while(1) {
		        char line[100];
		        read(in_fd,line,sizeof(line));
		        printf("\nRecieved:%s ...\n", line);
		   capitalize(line);
		        write(out_fd,line,sizeof(line));
		   }
		 */
		//
		// CONSOLE-PROCESSSOR STUFF
		//



		//close(out_fd);
		//close(in_fd);
		//remove("to_console");
		//remove("to_processor");
	}
	return 0;

}
