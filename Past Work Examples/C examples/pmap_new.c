/**********************************************************

 Created: Mark Brown
 ID: mb899115
 Date: 13/2/2018
 Description:
	This file is designed to mimic the "pmap" tool that
   can map out all the processes running currently on the
   the system.

**********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <procfs.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	if(argc != 2)
		printf("Error 1: Incorrect amount of arguments supplied to program\n");

	else
	{
		char fileName[40];
		char path[50];
		char flags[2];

		// Adds the file location to 'fileName' variable
		strcpy(fileName, "/proc/");
		strcat(fileName, argv[1]);
		strcat(fileName, "/map");

		// Adds the path for the readlink function
		strcpy(path, "/proc/");
		strcat(path, argv[1]);
		strcat(path, "/path/");
			

		FILE *file;

		file = fopen(fileName, "rb");

		if(file == 0)
			printf("Error 2: No such process found. Please use a different PID\n");
		else
		{
			prmap_t myStruct[75];
			int counter = 0;
			
			// Reads all the data into my structure that holds all the important information
			int val = fread(&myStruct, sizeof (prmap_t),100, file);		
	
			printf("%8s   %8s   %8s   %8s    %8s\n", "Start", "End", "Size", "Perms", "Path");

			printf("-----------------------------------------------------\n");

			//const char *restrict temp = myStruct[0].pr_mapname;
				

			while (counter < val){

				// checks for read				
				if(myStruct[counter].pr_mflags & MA_READ)	
					flags[0] = 'r';
				else
					flags[0] = '-';

				// checks for write				
				if(myStruct[counter].pr_mflags & MA_WRITE)	
					flags[1] = 'w';
				else
					flags[1] = '-';

				// checks for executable				
				if(myStruct[counter].pr_mflags & MA_EXEC)	
					flags[2] = 'x';
				else
					flags[2] = '-';
				
printf("%8x   %8x   %8dk   %4c%c%c", myStruct[counter].pr_vaddr, (myStruct[counter].pr_vaddr + myStruct[counter].pr_size), (myStruct[counter].pr_size / 1000), flags[0], flags[1], flags[2]);				

				// checks for stack
				if(myStruct[counter].pr_mflags & MA_STACK){
					printf("         %s\n", "[stack]");
				}
				// checks for anon
				else if(myStruct[counter].pr_mflags & MA_ANON){
					printf("         %s\n", "[anon]");
				}
				else{
					char temp[256];
					
					strcat(path, myStruct[counter].pr_mapname);
					readlink(path, temp, 256);
					printf("         %s\n", temp);
				}

				counter++;
			}
		}
	}

	return (0);	
}
