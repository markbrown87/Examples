/*----------------------------------------------------------------------
 * Name: Mark Brown (mb899115)
 * Date: 26/3/2018
 * Description: Software that uses an unnamed pipe to communication between
 *	forked software.
 *
 *----------------------------------------------------------------------*/
 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define READ 0
#define WRITE 1
#define MSG_LENGTH 100

// supplied message standards
typedef enum{
	REGULAR,
	COMMAND
} msg_type_t;

typedef struct msg{
	msg_type_t type;
	char message_text[MSG_LENGTH];
}msg_t;

int main(void){
	// declarations of variables
	int fd[2], nbytes;
	pid_t childpid;
	
	// message variables
	struct msg message = {REGULAR, ""};
	char readbuffer[80];
	
	// creating the pipe
	pipe(fd);
	
	// if fork() returns an error then it closes with an error
	if((childpid = fork()) == -1){
		perror("fork");
		exit(1);
	}
	// client side (child)
	else if(childpid == 0){
		close(fd[READ]);
		char *tmp;
		while(1){
			// sleeps for a moment while server prints the message sent
			sleep(1);
			printf("What would you like to send to the server? ");
			
			// reads in the message
			fgets(message.message_text, MSG_LENGTH, stdin);
			//temp pointer points at the message
			tmp = message.message_text;
			strtok(tmp, "\n");
			
			// parse the message to remove the 'send:' portion of the message
			tmp = strtok(tmp, ":");
			
			// checks for exit variable being called
			if(strcmp("exit", tmp) == 0){
				write(fd[WRITE], message.message_text, (strlen(message.message_text)+1));
				// _exit closes the forked process (child)
				_exit(0);
			}
			else if(strcmp("send",tmp) == 0){
				tmp = strtok(NULL, "");
				
				// copys what the pointer tmp is pointing at to the message_text to be sent
				strcpy(message.message_text, tmp);
				write(fd[WRITE], message.message_text, (strlen(message.message_text)+1));
			}
			// simple error check for proper input
			else{
				printf("Error at input! Try again. \n");
			}
		}
	}
	// server side (parent)
	else{
		close(fd[WRITE]);
		while(1){
			// reads in only if there is something to be read at the end of the pipe
			if(read(fd[0], readbuffer, sizeof(readbuffer)) > 0){
				// if what is being read in is exit then exit() the parent process
				if(strcmp("exit", readbuffer) == 0){
					printf("server (PID:%d) exits.\n", getpid());
					exit(0);
				}
				else{
					// reads out what is in the pipe
					printf("server (PID:%d): received string %s from client (PID:%d)\n",getpid(), readbuffer, childpid);
				}
			}
			else{
				break;
			}
		}
	}
}