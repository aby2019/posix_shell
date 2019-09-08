#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "ioredirection.h"
#include "p.h"
#include "pipe.h"
#include "bash.h"
#include "process.h"
int count=1;	
void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";//
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}
void history(char * str)
{
	 FILE *fp ;
     
    char arr[5];
    sprintf(arr, "%d", count);
    strcat(arr," ");
     count++;
    fp = fopen("/home/abhinav/Desktop/os_assignment1/history.txt", "a") ;
    if ( fp == NULL )
    {
        perror( "Could not open file history.txt\n" ) ;
    
    }
    	fputs(arr, fp);
        fputs(str, fp) ;   
        fputs("\n", fp) ;
    	fclose(fp) ;
}

void command_exec(char **args) 
{ 
    pid_t pid = fork();  
  	
    if (pid == -1) 
	{ 
        	perror("\nerror\n"); 
        	return; 
	} 
	else if (pid == 0) 
	{ 
		if (execvp(args[0],args) < 0) 
		{ 
		    perror("\nerror\n"); 
        	 
    	} 	
    	_exit(0); 
    }
	else 
	{  
	        wait(NULL);  
	        return ;
	}
		
} 
void command_script(char **args)
{
	int pid =fork();
		if(pid==0)
		{
			int fd;
			char filename[1024] = "/home/abhinav/Desktop/script.txt";
		 	if((fd = open(filename, O_APPEND|O_CREAT | O_WRONLY, 0644)) < 0)
	  		{
	        	perror("open error");
	        	
	      	}

	      	dup2(fd, 1);
	      	close(fd);
	      	execvp(args[0],args);
	      	perror("execvp error");
	      	_exit(EXIT_FAILURE);    
     	 }
      	else 
      		{
      			wait(NULL);
      		return;
      		}
}
void show_history()
{

	 char *his[5]={"cat","/home/abhinav/Desktop/os_assignment1/history.txt"};
	 command_exec(his);
	
}
void print_pwd() 
{
    	char str[1024];
	getcwd(str,sizeof(str));
	printf("%s\n",str);
}
void change_dir(char **args)
{
	if(!chdir(args[1]));
	else
		perror("error:");
}

int main() 
{
	 int record=0;
	init();
	while(1)
	{

		printf("%s ",PS1);
		print_pwd();
		int operation;// mode of io operation
		int arg_count=0;//no of arguments in token
		 int pipe_count;//no. of pipes
	     int back_ground=0; 
	    
		char* args[1024];
		ssize_t bufsize=1024;
		char *inbuilt[1024]={"exit","cd","clear","history",NULL};
		char *ptr;
			
		char *str;
		getline(&str,&bufsize,stdin);
	

			//tokenizing starts
		int tokens=0;
		ptr= strtok(str, " \n");

		while(ptr != NULL)
		{
			if(!strcmp(ptr,"&"))
	        {
	          back_ground=1;
	          tokens++;
	          break;
	        }
			args[tokens]=ptr;	
			ptr = strtok(NULL, " \n");
			tokens++;
		}
		args[tokens]=NULL;


				

		//tokenized
		arg_count=tokens;
		//printf("%d\n",arg_count);
		if(!back_ground)
		{
		operation=check_redirection(args,arg_count);//check if io operator exists
		pipe_count=get_pipe_count(args,arg_count);//no. of pipes
		}
		char variable[1024];


		

		if(str[0]=='\n')//on enter
			continue;




		history(str);

		for(int i=0;args[i];i++)///association of ~ with home
		{
			if(!strcmp(args[i],"~"))
				args[i]=HOME;
		}
		if(!strcmp(args[0],"alias"))//alias handle using function
		{
			// char temp[1024];
			// int tempi=0;
			// int alindex=0;
			// //strcpy(temp,args[3]);
			// for(int j=0;args[3][j];j++)
			// {
			// 	if(args[3][j]!=34)
			// 		{
			// 			temp[tempi++]=args[3][j];
			// 		}

			// }
			// temp[tempi]='\0';
			// alias[alindex++]=args[1];
		}

		if(!strcmp(args[0],"open"))
		{
			if(args[1]==NULL)
				continue;
			char *searchstr=strstr(args[1],".mp4");
			//printf("%s\n",args[0] );
			if(searchstr)
			{

				args[0]=opens[0];
				
			}
			searchstr=strstr(args[1],".txt");
			if(searchstr)
			{
				args[0]=opens[1];
			}
			searchstr=strstr(args[1],".pdf");
			if(searchstr)
			{
				args[0]=opens[1];
			}


		}
		if(!strcmp(args[0],"start")&&(!strcmp(args[1],"record")))
		{
			record=1;
			continue;
		}
		if(!strcmp(args[0],"stop")&&(!strcmp(args[1],"record")))
			{
				record=0;
				continue;
			}

		if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$USER")))
		{
			args[1]=USER;
			command_exec(args);
		}
		else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$HOME")))
		{
			args[1]=HOME;
			command_exec(args);
		}
		else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$PATH")))
		{
			args[1]=PATH;
			command_exec(args);
		}
		else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$HOSTNAME")))
		{
			args[1]=HOSTNAME;
			command_exec(args);
		}
		else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$PS1")))
		{
			args[1]=PS1;
			command_exec(args);
		}
			else if((!strcmp(args[0],"USER"))&&(!strcmp(args[1],"="))&&(arg_count>=2)) //no. of argument
			{
				//change path in envirn
				strcpy(USER,args[2]);
				set_env("USER",args);

			}
			else if((!strcmp(args[0],"HOSTNAME"))&&(!strcmp(args[1],"="))&&(arg_count>=2))// no. of argument
			{
				//change path in envirn
				strcpy(HOSTNAME,args[2]);
				set_env("HOSTNAME",args);

			}
			else if((!strcmp(args[0],"PATH"))&&(!strcmp(args[1],"="))&&(arg_count>=2))//no. of argument
			{
				//change path in envirn
				strcpy(PATH,args[2]);
				set_env("PATH",args);

			}
			else if((!strcmp(args[0],"HOME"))&&(!strcmp(args[1],"="))&&(arg_count>=2))//no. of argument
			{
				//change path in envirn
				strcpy(HOME,args[2]);
				set_env("HOME",args);

			}
			else if((!strcmp(args[0],"PS1"))&&(!strcmp(args[1],"="))&&(arg_count>=2))//no. of argument
			{
				//change path in envirn	
				strcpy(PS1,args[2]);

			}
			else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$$")))
			{
				printf("%d\n",getpid() );
			}
			///~~variables end;
		else if(!strcmp(args[0],inbuilt[3]))//history 
			show_history();
		
		else if(!strcmp(args[0],inbuilt[1]))
		{
			change_dir(args);
		}
		else if(pipe_count>0&&operation!=0)
	    {    
	    	piping_io(args,arg_count);
	    }
		else if(operation!=0)
		{
			io_redirection(args,operation,arg_count);
		}
		else if(pipe_count>0)
		{
			 piping(args,arg_count);
		}
		else if(!strcmp(args[0],inbuilt[2]))
		{
			clearScreen();
		}
		else if(!strcmp(args[0],inbuilt[0]))
		{
			// char *ex[3]={"rm","history.txt",NULL};
			// command_exec(ex);
			// count=1;
			exit(0);
		}
		else if(back_ground)
     	command_exec_bg(args);
		else
		{
			command_exec(args);
			if(record==1)
			{
				command_script(args);
			}

		}
	}	
    return 0;
}


