#include "simpleshell.h"

// INTERNAL COMMANDS
//
void echoIt(char * argList[]){
  for(char **arg = argList; *arg != NULL; arg++){   //loops through arglist and prints 
    printf("%s ", *arg);                            //each arg with a space inbetween them
  }
  printf("\n");                                     //prints newline when finished
}

void pauseIt(){
  printf("The shell is paused, press enter to unpause.");
  fflush(stdout);                                   //forces stdout to be written to its destination
  int c;
  while ((c = getchar()) != '\n' && c != EOF);      //constantly checks for a newline character (enter)
}                                                   //or end of file and when its satisfied the shell
                                                    //resumes

void helpIt(){
    char cmd[MAX_BUFFER + 8];                       
    snprintf(cmd, sizeof(cmd), "more \"%s\"", manual_path); //formats the command to display the manual with more filter
    system(cmd);                                            // and assigns it to cmd which then is executed by system.

}

void listDir(char * dirList[]){
  char cmd[MAX_BUFFER + 8];
  if (dirList[1]){                                  // If there is a directory argument open the directory
    DIR *d = opendir(dirList[1]);
    snprintf(cmd, sizeof(cmd), "ls -al %s", dirList[1]);  //format the command 
    if (d) {                                              // check directory opened 
       closedir(d);
       system(cmd);                                         // execute command
    }
    else {
       printf("Error no such directory '%s' found \n", dirList[1]); // else, directory wasn't found.
    }
  }
  else {
    system("ls -al"); // if there was no directory argument just list the contents of the current directory.
  }
}

void environShow(){
  for (char ** env = environ; *env != NULL; env++){ // loop through each environment var and print with newline char
    printf("%s\n", *env);
  }
}

void changeDir(char * argList[]){
  char cmd[MAX_BUFFER + 8];
  if (argList[1]){
    if (chdir(argList[1]) == -1){ // if fail to change directory return error failed to find directory, otherwise changedir.
      printf("Failed to find directory named '%s'\n", argList[1]);
    }
  }
  else{
    printf("%s\n", getcwd(cmd, MAX_BUFFER)); // else print the current directory path
  }
  setenv("PWD", getcwd(cmd, MAX_BUFFER), 1); //set PWD to the current directory path.
}

// HELPER FUNCTIONS
//
void tokeniser(char buf[], char * args[]){
//function
      int i = 0;
      args[i] = strtok(buf, SEPARATORS); //loops through buf and splits it at each separator and appends each token to args
      while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, SEPARATORS);
      }
}


void getManualPath(char executable[]){
  char exec_path[MAX_BUFFER]; // Get the directory the executable lives in
  realpath(executable, exec_path);
    
  char *last_slash = strrchr(exec_path, '/');// Strip the executable name to get just the directory
  if (last_slash != NULL)
    *last_slash = '\0';
    
  snprintf(manual_path, sizeof(manual_path), "%s/../manual/readme.txt", exec_path);// format the full path to the manual file

}

int getCurDir(char path[]){
  int curDirPlac = 0; 
    for (int i = 0; i < strlen(path); i++){ //loop through the current path
      if (path[i] == '/'){                  // each time a / is found  set curDirPlac to i
       curDirPlac = i;
      }
    }                                       // once the loop ends curDirPlac will be the same value as the index of
                                            // the last / aka the start of the last directory in the path.
    curDirPlac > 0 ? curDirPlac++ : curDirPlac; //if more than 1 / found increase count by 1 else, keep the same
    return curDirPlac;
}
//Eoghan hughes, 20729, I acknowledge the dcu academic integrity policy
