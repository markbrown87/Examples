/*----------------------------------------------------------------------
* Name: Mark Brown (mb899115)
* Date: 15//2018
* Description: Server side that communicates with the clients via fork()
*	process. The server takes in the request, forks, and communicates with
*	the client via that forked process.
*
*----------------------------------------------------------------------*/


#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define MAX_BUF 1024
#define FALSE 0
#define TRUE 1

// supplied message standards
typedef enum {
	REGULAR,
	COMMAND
} msg_type_t;

// structure for messages
typedef struct msg_message {
	msg_type_t type;
	char message_text[MAX_BUF];
}msg_request_t;

//structure for initiating the request to server
typedef struct msg_init {
	msg_type_t type;
	char init[MAX_BUF];
}msg_initial_request_t;

//Global Variables
int _clients = 0;


//COMMENTS HERE!!!
void signalHandler(int signal);


int main()
{
	// Variables used within the server script
	time_t rawtime;
	struct tm * timeinfo;
	int fd_read, fd_write;
	struct msg_message message = { REGULAR, "" };
	struct msg_init request = { COMMAND, "" };
	int trigger = TRUE, holder = FALSE;
	char *server_request = "server_np";
	char *full_write;
	char *full_read;
	char _append[MAX_BUF] = "";
	char *tmp;
	pid_t childpid;
	char buf[MAX_BUF];
	char _pid[MAX_BUF];

	//handles what happens when a child exits the process
	signal(SIGCHLD, signalHandler);


	// Below is where I make read/write named pipes for the server with rw-r--r-- permissions
	mkfifo(server_request, 0666);

	// basically infinite loop waiting for clients to connect to the server
	while (trigger)
	{
		if ((fd_read = open(server_request, O_RDONLY)) < 0)
			perror("fd_read (server) -> server_request");

		while (read(fd_read, buf, MAX_BUF) > 0)
		{
			_clients++;

			// if fork() returns an error then it closes with an error
			if ((childpid = fork()) == -1) {
				perror("forking error");
				exit(1);
			}
			
			else if (childpid == 0) {
				printf("Client %d connected to server @ <PID>%s\n", _clients, buf);
				trigger = FALSE;
			}

		}

		close(fd_read);
	}

	strcpy(_pid, buf);

	// copys over the PID number to set up the communicate pipes on the server side
	strcat(_append, buf);
	strcat(_append, "_send");
	full_read = _append;

	strcpy(_append, "");

	strcat(_append, buf);
	strcat(_append, "_receive");
	full_write = _append;

	trigger = TRUE;


	// loop for communicating with the server
	while (trigger) {

		if ((fd_read = open(full_read, O_RDONLY)) < 0)
			perror("fd_read (server) -> full_read");

		while (read(fd_read, buf, MAX_BUF) > 0)
		{
			// handles when exit is called
			if (strcmp("exit", buf) == 0) {
				if ((fd_write = open(full_write, O_WRONLY)) < 0)
					perror("fd_write (server) -> full_write");

				if ((write(fd_write, "exit", (strlen("exit") + 1))) < 0)
					perror("write (server) -> fd_write return value");

				holder = FALSE;

				close(fd_write);

				// change to _exit(0); once fork works
				_exit(0);
			}
			// handles status call to the server
			else if (strcmp("status", buf) == 0) {

				printf("Status requested: Clients %d\n", _clients);
				holder = TRUE;

				//if ((fd_write = open(full_write, O_WRONLY)) < 0)
				//	perror("fd_write (server) -> full_write");

				//strcpy(buf, "");
				//sprintf(buf, "%d", _clients);

				//if ((write(fd_write, buf, (strlen(buf) + 1))) < 0)
				//	perror("write (server) -> fd_write return value");

				//holder = FALSE;

				//close(fd_write);
			}
			// handles server call for time
			else if (strcmp("time", buf) == 0) {
				time(&rawtime);
				timeinfo = localtime(&rawtime);
				printf("Time: %s", asctime(timeinfo));
				holder = TRUE;
			}
			// handles the send function to the server
			else {
				printf("Message <%s>: %s\n", _pid, buf);
				holder = TRUE;
			}

		}

		// checker function for the server to respond. If it reponds we get a success message
		if (holder) {
			// send back that message was received to client
			if ((fd_write = open(full_write, O_WRONLY)) < 0)
				perror("fd_write (server) -> full_write");

			if ((write(fd_write, "received", (strlen("received") + 1))) < 0)
				perror("write (server) -> fd_write return value");

			close(fd_write);

			holder = FALSE;
		}

		close(fd_read);
	}

	unlink(server_request);

	return 0;
}

// handles the signal and decreases the number of clients on the server
void signalHandler(int signal)
{
	if (signal == SIGCHLD) {
		_clients--;
		wait(NULL);
	}
}