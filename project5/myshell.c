#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

char * commandline;
char * command;
char ** arglist = NULL;
char * filename;
int numargs = 0;
int fileop=0;
int time_out = 0;
void split();
void execute();
void clearargs();

int main()
{
	char buffer[100];
	commandline = buffer;
	while(1)
	{
		if( fgets(commandline, 100, stdin) == NULL)
		{
			printf("Command can not be read");
			exit(0);
		}
		split();
		execute();
		clearargs();
	}
	
	return 0;

}


void execute()
{
	pid_t pid;
     	int status;

	if( arglist[0] == NULL) // no command was typed
	{
		printf("%s\n", "No command entered");
		return;
	}
	else if( strcmp(arglist[0], "exit") == 0) // EXIT 
	{
		free(arglist);
		exit(0);
	}
	else if( strcmp(arglist[0], "cd") == 0) // CHANGE DIRECTORY
	{
		if( chdir(arglist[1]) == -1) //execute call
		{
			printf("%s\n", strerror(errno)); // error return statement
		}

	}
	else // UNIX COMMANDS
	{	

		pid = fork();

		if( pid == -1) //fork error
		{	
			printf("FORK ERROR: %s\n", strerror(errno)); //error return statement
			exit(1); //exit with error
		}
		
		if( pid == 0) // child
		{
				
			
			int savedfd = 0;
			int tempfd = 0;

			if(fileop == 1)
			{
				fflush(stdout);
				savedfd = dup(1);
				tempfd = open(filename, O_WRONLY);
				dup2(tempfd, 1);
				close(tempfd);
			}
			if(fileop == 2)
                        {
				fflush(stdin);
				savedfd = dup(STDIN_FILENO);
                                tempfd = open(filename,	O_RDONLY);
                                dup2(tempfd, STDIN_FILENO);
                                close(tempfd);
                        }

			if( (execvp(command,arglist)) == -1 ) //call execvp( command, arglist )
			{
				 printf("EXECVP ERR: %s\n", strerror(errno)); //error return statement
				 exit(1);
			}	
			
			fflush(stdout);
			fflush(stdin);
			dup2(savedfd, 1);
			close(savedfd);
			exit(0);

				
		}
		
		//PARENT
		
		clock_t start, stop;
		time_t now;
		double t = 0.0;

                start = clock();
                       	 
		wait(&status);
			 
		stop = clock();
		
		t = ((double) (stop - start)) / CLOCKS_PER_SEC;
		
		if( time_out == 1)
		{
			
                	printf ( "Function time: %d\n", t );
			time_out = 0;
		}
 
               
	}

}


void split()
{	
	char delim[] = " \t \n ( ) | & ; "; //delimiter string
	char * token; //token pointer
	int index = 0; // index of arglist

	{
   		printf("token = %s\n", token);
		if(strcmp ( token, "time") == 0)
		{
			time_out == 1;
		}
		else if( strcmp(token,">")== 0 )
		{	
			fileop = 1;
		}
		else if( strcmp(token, "<") == 0)
		{
			fileop = 2;
		}	
		else if(fileop > 0)
		{
			filename = malloc(sizeof(token));
		}
		else	
		{
		arglist = realloc (arglist, sizeof(char*) * ++index);
		arglist[index-1] = token;
		}
	}
	
	numargs = index;
	command = arglist[0];
}

void clearargs()
{
	int i = 0;
	for(i = 0; i < numargs; i ++);
	{
		arglist[i] = NULL;
	}
}



