#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include<fcntl.h>
#include<signal.h>
 
void childSignalHandler(int signum) 
{
    int status;
    pid_t pid;
     
    pid = waitpid(-1, &status, WNOHANG);
}

void command_exec_bg(char **args) 
{ 
    signal(SIGCHLD,childSignalHandler);
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
        perror("\nhierror\n"); 
           
    }   
      exit(0); 
     }
  
} 


// int main() 
// {
//   while(1)
//   {
//     print_pwd();
//     char* args[1024];
//     ssize_t bufsize=1024;
//     char *inbuilt[1024]={"exit","cd","clear"};
//     char *ptr;
//     int i=0; 
//     int back_ground=0; 
//     char *str;
//     getline(&str,&bufsize,stdin);
//     char *out = strstr(str, ">");
//     ptr= strtok(str, " \n");

//     while(ptr != NULL)
//     {

//       if(!strcmp(ptr,"&"))
//         {
//           back_ground=1;
//           i++;
//           break;
//         }
//       args[i]=ptr;  
//       ptr = strtok(NULL, " \n");
//       i++;
//     }
//     args[i]=NULL;
//     // printf("%d\n",i );
//     // if(!strcmp(args[i-1],"&"));
//     // {
//     //   back_ground=1;
//     //   args[i-1]=NULL;
//     // }
    
//     // if(!strcmp(args[0],inbuilt[0]))
//     //   exit(0);
//     // else if(!strcmp(args[0],inbuilt[1]))
//     // change_dir(args);
//     // else
//     if(back_ground)
//      command_exec_bg(args);
//    else
//     command_exec(args);
//   } 
//     return 0;
// }


