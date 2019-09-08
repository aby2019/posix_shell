#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
// int check_redirection(char **args,int arg_count)
// {
//   for(int i=0;i<arg_count;i++)
//   {
//     if(!strcmp(args[i],">"))
//     {
//       return 1;
//     }
//     if(!strcmp(args[i],"<"))
//     {
//       return 2;
//     }
//     if(!strcmp(args[i],">>"))
//     {
//       return 3;
//     }
//     if(!strcmp(args[i],"<<"))
//     {
//       return 4;
//     }
//   }
//   return 0;
// } 

int get_pipe_count(char **args,int arg_count)
{
  int c=0;
  for(int i=0;i<arg_count;i++)
  {
    if(!strcmp(args[i],"|"))
      c++;
  }
  return c;
}
int piping_io(char **args,int arg_count)
{
    int flag=check_redirection(args,arg_count);
    int numpipes=get_pipe_count(args,arg_count);
    char filename[1024];
    strcpy(filename,args[arg_count-1]);
    int count=numpipes+1;
      char **commands =  calloc(100, sizeof(char*));
      for(int i = 0; i < (numpipes +1); i++)
      {
        commands[i] = calloc(100, sizeof(char));
      }
      char **ops =  calloc(100, sizeof(char*));
      for(int i = 0; i < (numpipes +1); i++)
      {
        ops[i] = calloc(100, sizeof(char));
      }
      int inx=0;  
      int i=0;
 
    for( i=0;i<arg_count-3;i++)
   {
      if(strcmp(args[i],"|"))
      {
        strcat(ops[inx],args[i]);
        if(strcmp(args[i+1],"|"))
        strcat(ops[inx]," ");  
      }
      else
      {
        inx++;
      }
   }
   strcat(ops[inx],args[i]);
   ops[++inx]=NULL;
   
   char temp2[1024];
   char * str2[1024];
   strcpy(temp2,ops[inx-1]);
    int index=0;
  
    char *ptr2= strtok(temp2," \n");
    while(ptr2 != NULL)
    {
      
      str2[index]=ptr2;  
      ptr2 = strtok(NULL, " \n");
      index++;
    }
    str2[index]=NULL;
   
   char temp1[1024];
   char * str1[1024];
   // strcpy(temp1,commands[inx-1]);

   // index=0;
   // char *ptr1= strtok(temp1," \n");
   //  while(ptr1 != NULL)
   //  {
      
   //    str1[index]=ptr1;  
   //    ptr1 = strtok(NULL, " \n");
   //    index++;
   //  }
   //  str1[index]=NULL;
   //  printf("hi");
   //  printf("%d",count);
    int fd;
    
    // int k=0;
    // while(str2[k]!=NULL)
    //   printf("%s\n",str2[k++] );


    int k=0;
  ///////////////
     pid_t pid3=fork();
     if(!pid3)
     {
        for( i=0;i<count-1; i++)
        {     
              int pd[2];
               pipe(pd);
            pid_t pid1 =fork();
            if (!pid1) 
            {
              char *str[1024];
              char temp[1024];
              strcpy(temp,ops[i]);
                ////////////////tokenize
             int index=0;
             char *ptr= strtok(temp," \n");
              while(ptr != NULL)
              {
                str[index]=ptr;  
                ptr = strtok(NULL, " \n");
                index++;
              }
            str[index]=NULL;
            dup2(pd[1], 1);
            close(pd[0]);
            execvp(str[0],str);
            perror("exec");
            abort();
            }
            wait(NULL);
            dup2(pd[0], 0);
            close(pd[1]);

          }
            if(flag==1)
            {
              if((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)//ls | sort | wc -l < file.txt
              {
              perror("open error");
              }

              dup2(fd, 1);
              close(fd);
              execvp(str2[0],str2);
              perror("exec");
               abort();
            }
            ///////////////////////////////////
       else if(flag==2)
        {

              if((fd = open(filename,O_RDONLY, 0644)) < 0)
              {
                  perror("open error");
                  
              }

                dup2(fd, 0);
                close(fd);
                execvp(str2[0], str2);
                perror("execvp error");
                _exit(EXIT_FAILURE);    
      
        }
    else if(flag==3)
    {

      if((fd = open(filename, O_APPEND|O_CREAT | O_WRONLY, 0644)) < 0)
      {
          perror("open error");
          
      }
        dup2(fd, 1);
        close(fd);
        execvp(str2[0], str2);
        perror("execvp error");
        _exit(EXIT_FAILURE);       
    }
    else if(flag==4)
    {

        if((fd = open(filename, O_RDONLY, 0644)) < 0)
        {
            perror("open error");
            
        }
          dup2(fd, 0);
          close(fd);
          execvp(str2[0], str2);
          perror("execvp error");
          _exit(EXIT_FAILURE);    
        
     }
     else
     {
            execvp(str2[0],str2);
            perror("exec");
             abort();
     }
  }
      else
      {
        wait(NULL);
      }
    
}



// void io_redirection(char **args,int operation,int arg_count)
// {
//     int fd,fd2;
//     int flag=0;
//     char *filename=args[arg_count-1];
//     // printf("%s%d\n",filename,arg_count);
  
//     for(int i=0;i<arg_count;i++)
//     {
//       if(!strcmp(args[i],">"))
//       {
//         args[i]=NULL;
//         break;
//       }
//       if(!strcmp(args[i],"<"))
//       {
//         args[i]=NULL;
//         break;
//       }
//       if(!strcmp(args[i],">>"))
//       {
//         args[i]=NULL;
//         break;
//       }
//       if(!strcmp(args[i],"<<"))
//       {
//         args[i]=NULL;
//         break;
//       }   
//     }
    
//     pid_t pid = fork();  

//     if (pid == -1) 
//   { 
//           perror("\nerror\n"); 
//           return; 
//   } 
//   else if (pid == 0) 
//   { 
//     if(operation==1)        
//     {
//       if((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
//       {
//           perror("open error");
          
//       }

//         dup2(fd, 1);
//         close(fd);
//         execvp(args[0], args);
//         perror("execvp error");
//         _exit(EXIT_FAILURE);    
//     }
//     else if(operation==2)
//     {

//       if((fd = open(filename,O_RDONLY, 0644)) < 0)
//       {
//           perror("open error");
          
//       }

//         dup2(fd, 0);
//         close(fd);
//         execvp(args[0], args);
//         perror("execvp error");
//         _exit(EXIT_FAILURE);    
       
//     }
//     else if(operation==3)
//     {

//       if((fd = open(filename, O_APPEND|O_CREAT | O_WRONLY, 0644)) < 0)
//       {
//           perror("open error");
          
//       }

//         dup2(fd, 1);
//         close(fd);
//         execvp(args[0], args);
//         perror("execvp error");
//         _exit(EXIT_FAILURE);    
        
//     }
//     else if(operation==4)
//     {

//       if((fd = open(filename, O_RDONLY, 0644)) < 0)
//       {
//           perror("open error");
          
//       }
//         dup2(fd, 0);
//         close(fd);
//         execvp(args[0], args);
//         perror("execvp error");
//         _exit(EXIT_FAILURE);    
//     }
//   }
//   else 
//   {  
//           wait(NULL);  
//           return ;
//   } 
// }
// int main() 
// {
//   int arg_count=0;
//   while(1)
//   {
    
//     char* args[1024];
//     ssize_t bufsize=1024;
//     char *inbuilt[1024]={"exit","cd","clear"};
    
//     char *ptr;
//     int i=0;  
//     char *str;
//     getline(&str,&bufsize,stdin);      
//     ptr= strtok(str, " \n");
//     while(ptr != NULL)
//     {      
//       args[i]=ptr;  
//       ptr = strtok(NULL, " \n");
//       i++;
//     }
//     arg_count=i;
//     args[i]=NULL;
//       //int operation=check_redirection(args,arg_count);//1- (>) 2-(<) 3 - (>>) 4- (<<);
//       //io_redirection(args,operation,arg_count);
//     int pipe_count= get_pipe_count(args,arg_count);
//     if(pipe_count>0)
//     {    

//     piping(args,arg_count);

//     }
//   } 
//     return 0;
// }
