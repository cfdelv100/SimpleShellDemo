#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
/*  Here is a array to store path
    from environment variable
*/
char PATH[16][256];
char *argv[16];

/*  Here we are filling the array with paths
    in the PATH environment variable 
*/
int setPath(){
 

  char* s = getenv("PATH");
  char *token;
  char sep[2] = ":";
  
  
  /*if ( s == NULL ) 
    return -1;
  */
  
  token = strtok(s, sep);

  int i = 0;
  
  while( token != NULL )
  {
    strcpy(PATH[i++], token);
    token = strtok( NULL, sep);
  }
 
    return 0;
}

void resetArgv(){
  int  i = 0;
  while ( argv[i] != NULL){
    free(argv[i]);
    argv[i] = NULL;
    i++;
  }
}

/*
    Here we will parse arguments
*/
int setArgs( char * line){
  
  if ( *line == '\n' )
  return 0;
  
  char *token;
  char sep[2] = " ";
  
  token = strtok(line, sep);
  int i = 0;
  
  while( token != NULL )
  {

    argv[i] = (char * )malloc(sizeof(token));
    strcpy(argv[i++], token);
    token = strtok( NULL, sep);
  }
  
  return i;

}

// check if command existes
char * cmdOK( char *loc){
  int  i = 0;
  
  while( PATH[i][0] != '\0' ){
    
    sprintf(loc,"%s/%s",PATH[i],argv[0]);
    
    if( access( loc, F_OK ) != -1 )
      return loc;

    i++;
    if ( i == 16 )
      return NULL;
  }
  return NULL;
}
// defining the command handler
void* cmdHandler(void *line){
line = NULL;
char *token;
char sep[2] = " ";
token = strtok(line, sep);
int i = 0;
while(token != NULL){
   argv[i] = (char *)malloc(sizeof(token));
   strcpy(argv[i++], token);
   token = strtok(NULL, line);

}
  return 0;
}


int main(int argc, char *argv[])
{
  char line[80] = "";
  int count = 0;
  int  i = 0;
  
  if ( setPath() ==  -1 )
  {
    printf("Error getting paths from PATH environment variable\n");
    return 1;
  }
  
  while(1)
  {
    char loc[128]= "";
    
    // cleaning all the buffers 
    fflush(0);
    resetArgv();
    
    printf("myShell$ ");
    
    fgets( line, 80,
 stdin);
    char * ptr = line;
    line[ strlen(line) -1 ] = '\0';
    
    /// skip spaces
    while ( *ptr == ' ') ptr++;
    
    // Checking if there are arguments or just new line char
    if ( (count = setArgs(ptr)) == 0 )
    continue;
  
    // Checks if command existes
    if ( cmdOK(loc) == NULL )
      continue;

    // Here we are creating a child process with threads and running our cmd
    pthread_t myThread;
    // declaring the variable 
    int *commands;
    // creating the thread
    pthread_create(&myThread, NULL, &cmdHandler, (char *) line);
    //pthread_join to stop the thread
    pthread_join(myThread, (void **)&commands);
    //executing the commands
    if(myThread == 0){
      execv(loc, argv);
      exit(0);
    }
    else{
    printf("Error...\n");
    } 

    pthread_exit((void *) cmdHandler);
    return (0);
  }
 }

