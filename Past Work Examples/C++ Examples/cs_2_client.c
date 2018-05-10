/*----------------------------------------------------------------------
* Name: Mark Brown (mb899115)
* Date: 15/4/2018
* Description: Client side of the server/client communications
*
*----------------------------------------------------------------------*/


#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUF 1024
#define FALSE 0
#define TRUE 1

// supplied message standards
typedef enum {
	REGULAR,
	COMMAND
} msg_type_t;

// structure for message communications
typedef struct msg_message {
	msg_type_t type;
	char message_text[MAX_BUF];
}msg_request_t;

// structure for initiating the server request
typedef struct msg_init {
	msg_type_t type;
	char init[MAX_BUF];
}msg_initial_request_t;


int main()
{
	// public variables used in the client script
	int fd_write, fd_read;
	int trigger = TRUE, holder = TRUE;
	struct msg_message message = { REGULAR, "" };
	struct msg_init request = { COMMAND, "" };
	char buf[MAX_BUF];
	char _file[MAX_BUF];
	char temp_holder[MAX_BUF];
	char *_write = "_send";
	char *_read = "_receive";
	char _append[MAX_BUF] = "";
	char *full_write;
	char *full_read;
	char *server_request = "server_np";
	char *tmp;

	// add pid to file
	sprintf(_file, "%d", getpid());
	// add pid to server request message
	sprintf(request.init, "%d", getpid());

	// add the full file location for named pipe to send location
	strcpy(temp_holder, _file);
	strcat(_file, _write);
	strcat(_append, _file);
	full_write = _append;

	// opens the pipe with r/w functionately only
	if ((mkfifo(full_write, 0666)) < 0)
		perror("mkfifo write");

	// add the full file location for the named pipe to the receive location
	strcpy(_file, "");
	strcpy(_append, "");
	sprintf(_file, "%d", getpid());
	strcat(_file, _read);
	strcat(_append, _file);
	full_read = _append;

	// opens the pipe with r/w functionately only
	if ((mkfifo(full_read, 0666)) < 0)
		perror("mkfifo read");

	// makes the server request
	if ((fd_write = open(server_request, O_WRONLY)) < 0)
		perror("fd-write -> server_request");
	if (write(fd_write, request.init, (strlen(request.init) + 1)) < 0)
		perror("fd_write -> message.message_text");
	close(fd_write);

	// while loop to handle communcation between server(child) and client. It reads bidirectionally through <PID>_send/_receive pipes
	while (trigger) {

		holder = TRUE;

		if ((fd_write = open(full_write, O_WRONLY)) < 0)
			perror("fd-write -> full_read");

		printf("What would you like to send to the server? ");

		// reads in the message
		if (fgets(message.message_text, MAX_BUF, stdin) != NULL) {

			//temp pointer points at the message
			tmp = message.message_text;
			strtok(tmp, "\n");

			// parse the message to remove the 'send:' portion of the message
			tmp = strtok(tmp, ":");

			// checks for exit variable being called
			if (strcmp("exit", tmp) == 0) {

				if ((write(fd_write, message.message_text, (strlen(message.message_text) + 1))) < 0)
					perror("write (client) -> fd_write: exit");
			}
			// handles send function
			else if (strcmp("send", tmp) == 0) {
				tmp = strtok(NULL, "");

				// copys what the pointer tmp is pointing at to the message_text to be sent
				strcpy(message.message_text, tmp);
				if ((write(fd_write, message.message_text, (strlen(message.message_text) + 1))) < 0)
					perror("write (client) -> fd_write: send:...");
			}
			// handles the status call to the server
			else if (strcmp("status", tmp) == 0) {

				if ((write(fd_write, message.message_text, (strlen(message.message_text) + 1))) < 0)
					perror("write (client) -> fd_write: send:...");
			}
			// handles the time call to the server
			else if (strcmp("time", tmp) == 0) {
				if ((write(fd_write, message.message_text, (strlen(message.message_text) + 1))) < 0)
					perror("write (client) -> fd_write: send:...");
			}
			// simple error check for proper input
			else {
				printf("Error at input! Try again.\n");
				holder = FALSE;
			}
		}
		else {
			perror("fgets (client)");
		}
		close(fd_write);

		// holder checker for the server to send back a success message
		if (holder) {
			if ((fd_read = open(full_read, O_RDONLY)) < 0)
				perror("fd-read -> full_read");

			while (read(fd_read, buf, MAX_BUF) > 0)
			{
				// handles exit call from the server
				if (strcmp("exit", buf) == 0) {
					unlink(full_read);
					trigger = FALSE;
				}


				//else if (strcmp("status", tmp) == 0) {
				//	printf("Clients: %s\n", buf);
				//}
				else
					printf("Message Successfully Sent!\n");
			}

			close(fd_read);
		}
	}

	unlink(full_write);

	return 0;
}