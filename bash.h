#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include<fcntl.h>

extern char **environ;

char HOME[1024]="/home/abhinav";
char PATH[1024]="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
char USER[1024]="abhinav";
char HOSTNAME[1024]="abhinav-HP-Laptop-15q-ds0xxx";
char PS1[1024]="abhinav@abhinav-HP-Laptop-15q-ds0xxx:~$";
char *opens[1024]={"vlc","libreoffice",NULL};
int cap;//history size

void init()
{

setenv("USER",USER,1);
setenv("HOSTNAME",HOSTNAME,1);
setenv("PATH",PATH,1);
setenv("HOME",HOME,1);
}
void set_env(char *str,char ** args)
{
	char temp[1024];
	strcpy(temp,args[2]);
	setenv(str,temp,1);
}
// void get_env(char **args)
// {
	
// }
// void print_pwd() 
// {
//     char str[1024];
// 	getcwd(str,sizeof(str));
// 	printf("%s\n",str);
// }
// void change_dir(char **args)
// {
// 	if(!chdir(args[1]));
// 	else
// 		perror("error:");
// }

// int main() 
// {
// 	char *alias[1024];
// 	init();
// 	while(1)
// 	{
				
// 		printf("%s ",PS1);
// 		print_pwd();
// 		char* args[1024];
// 		ssize_t bufsize=1024;
// 		char *inbuilt[1024]={"exit","cd","clear","history",NULL};
// 		char *ptr;
// 		int i=0;	
// 		char *str;
// 		getline(&str,&bufsize,stdin);
		
// 		char *out = strstr(str, ">");
// 		//tokenize
// 		ptr= strtok(str, " \n");

// 		while(ptr != NULL)
// 		{
			
// 			args[i]=ptr;	
// 			ptr = strtok(NULL, " \n");
// 			i++;
// 		}
// 		args[i]=NULL;

// 		//tokenized
// 		char variable[1024];
// 		if(str[0]=='\n')//on enter
// 			continue;
// 		for(int i=0;args[i];i++)///association of ~ with home
// 		{
// 			if(!strcmp(args[i],"~"))
// 				args[i]=HOME;
// 		}
// 		if(!strcmp(args[0],"alias"))//alias handle using function
// 		{
// 			// char temp[1024];
// 			// int tempi=0;
// 			// int alindex=0;
// 			// //strcpy(temp,args[3]);
// 			// for(int j=0;args[3][j];j++)
// 			// {
// 			// 	if(args[3][j]!=34)
// 			// 		{
// 			// 			temp[tempi++]=args[3][j];
// 			// 		}

// 			// }
// 			// temp[tempi]='\0';
// 			// alias[alindex++]=args[1];
// 		}
// 		if(!strcmp(args[0],"open"))
// 		{
// 			char *searchstr=strstr(args[1],".mp4");
// 			if(searchstr)
// 			{
// 				args[0]=opens[0];
// 			}
// 			searchstr=strstr(args[1],".txt");
// 			if(searchstr)
// 			{
// 				args[0]=opens[1];
// 			}
// 			searchstr=strstr(args[1],".pdf");
// 			if(searchstr)
// 			{
// 				args[0]=opens[1];
// 			}

// 		}

// 		if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$USER")))
// 		{
// 			args[1]=USER;
// 			command_exec(args);
// 		}
// 		else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$HOME")))
// 		{
// 			args[1]=HOME;
// 			command_exec(args);
// 		}
// 		else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$PATH")))
// 		{
// 			args[1]=PATH;
// 			command_exec(args);
// 		}
// 		else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$HOSTNAME")))
// 		{
// 			args[1]=HOME;
// 			command_exec(args);
// 		}
// 		else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$PS1")))
// 		{
// 			args[1]=PS1;
// 			command_exec(args);
// 		}
// 			else if((!strcmp(args[0],"USER"))&&(!strcmp(args[1],"="))&&(i>=2))//i is no. of argument
// 			{
// 				//change path in envirn
// 				set_env("USER",args);

// 			}
// 			else if((!strcmp(args[0],"HOSTNAME"))&&(!strcmp(args[1],"="))&&(i>=2))//i is no. of argument
// 			{
// 				//change path in envirn
// 				set_env("HOSTNAME",args);

// 			}
// 			else if((!strcmp(args[0],"PATH"))&&(!strcmp(args[1],"="))&&(i>=2))//i is no. of argument
// 			{
// 				//change path in envirn
// 				set_env("PATH",args);

// 			}
// 			else if((!strcmp(args[0],"HOME"))&&(!strcmp(args[1],"="))&&(i>=2))//i is no. of argument
// 			{
// 				//change path in envirn
// 				set_env("HOME",args);

// 			}
// 			else if((!strcmp(args[0],"PS1"))&&(!strcmp(args[1],"="))&&(i>=2))//i is no. of argument
// 			{
// 				//change path in envirn
// 				strcpy(PS1,args[2]);

// 			}
// 			else if((!strcmp(args[0],"echo"))&&(!strcmp(args[1],"$$")))
// 			{
// 				printf("%d\n",getpid() );
// 			}
// 			///~~variables end;
// 			else if(!strcmp(args[0],inbuilt[0]))
// 			{
// 				char *ex[3]={"rm","history.txt",NULL};
// 				command_exec(ex);
// 				exit(0);
// 			}
// 			else if(!strcmp(args[0],inbuilt[1]))///case for cd
// 			{
// 				change_dir(args);
// 			}
// 			else
// 			command_exec(args);
			
// 	}
	
//     return 0;
// }


