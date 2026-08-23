#include "simpleshell.h"

// INTERNAL COMMANDS
//
void echoIt(char * argList[]){
  for(char **arg = argList; *arg != NULL; arg++){           //loops through arglist and prints 
    printf("%s ", *arg);                                    //each arg with a space inbetween them
  }
  printf("\n");                                             //prints newline when finished
}

void pauseIt(){
  printf("The shell is paused, press enter to unpause.");
  fflush(stdout);                                           //forces stdout to be written to its destination
  int c;
  while ((c = getchar()) != '\n' && c != EOF);              //constantly checks for a newline character (enter)
}                                                           //or end of file and when its satisfied the shell
                                                            //resumes

void helpIt(){
    char cmd[MAX_BUFFER + 8];                       
    snprintf(cmd, sizeof(cmd), "more \"%s\"", manual_path); //formats the command to display the manual with more filter
    system(cmd);                                            // and assigns it to cmd which then is executed by system.

}

void listDir(char * dirList[]){
  char cmd[MAX_BUFFER + 8];
  if (dirList[1]){                                          // If there is a directory argument open the directory
    DIR *d = opendir(dirList[1]);
    snprintf(cmd, sizeof(cmd), "ls -al %s", dirList[1]);    //format the command 
    if (d) {                                                // check directory opened 
       closedir(d);
       system(cmd);                                         // execute command
    }
    else {
       printf("Error no such directory '%s' found \n", dirList[1]); // else, directory wasn't found.
    }
  }
  else {
    system("ls -al");                                       // if there was no directory argument just list the contents of the current directory.
  }
}

void environShow(){
  for (char ** env = environ; *env != NULL; env++){         // loop through each environment var and print with newline char
    printf("%s\n", *env);
  }
}

void changeDir(char * argList[]){
  char cmd[MAX_BUFFER + 8];
  if (argList[1]){
    if (chdir(argList[1]) == -1){                           // if fail to change directory return error failed to find directory, otherwise changedir.
      printf("Failed to find directory named '%s'\n", argList[1]);
    }
  }
  else{
    printf("%s\n", getcwd(cmd, MAX_BUFFER));                // else print the current directory path
  }
  setenv("PWD", getcwd(cmd, MAX_BUFFER), 1);                //set PWD to the current directory path.
}

// HELPER FUNCTIONS
//
bool tokeniser(char buf[], char * args[]){
//function
  bool background = false;
  int i = 0;
  args[i] = strtok(buf, SEPARATORS);                        //loops through buf and splits it at each separator and appends each token to args
  while (args[i] != NULL) {
    i++;
    args[i] = strtok(NULL, SEPARATORS);
  }
  //check for ampersand (if its  a background task)
  if (i > 0){                                               //first check if there are arguments
    char *last = args[i - 1];                               // get the last argument
    if (strcmp(last, "&") == 0){                            //if last arg is an & symbol set it to null to delete it
      args[i - 1] = NULL;                                      //then it is a background task
      background = true;
    }
    else if(strcmp(&last[strlen(last) - 1], "&") == 0){     //else if the last argument has an & symbol at the end e.g. "dir&"
      last[strlen(last) - 1] = '\0';                        //set the & symbol to empty null character
      background = true;                                    //set as a background task
    }
  }
  return background;
}


void printPrompt(char *prompt, int batchfile){
  getcwd(prompt, MAX_BUFFER);                               // get the current path
    int curDirPlac = getCurDir(prompt);                     // find the position of the last directory in the path

    if (!batchfile){                                        // add spacer between prompt and text input
      strcat(prompt, " ");
    }
    else{
      strcat(prompt, " \n");
    }
    if (!batchfile){
      fputs(prompt + curDirPlac, stdout);                   // display prompt
      fflush(stdout);
    }
}


void getManualPath(char executable[]){
  char exec_path[MAX_BUFFER];                               // Get the directory the executable lives in
  realpath(executable, exec_path);
    
  char *last_slash = strrchr(exec_path, '/');               // Strip the executable name to get just the directory
  if (last_slash != NULL)
    *last_slash = '\0';
    
  snprintf(manual_path, sizeof(manual_path), "%s/../manual/readme.txt", exec_path);// format the full path to the manual file

}

int getCurDir(char path[]){
  int curDirPlac = 0; 
    for (int i = 0; i < strlen(path); i++){                 //loop through the current path
      if (path[i] == '/'){                                  // each time a / is found  set curDirPlac to i
       curDirPlac = i;
      }
    }                                                       // once the loop ends curDirPlac will be the same value as the index of
    if (curDirPlac > 0) { 
      curDirPlac++;
    }                                                       // the last / aka the start of the last directory in the path.
    return curDirPlac;                                      //if more than 1 / found increase count by 1 else, keep the same
    
}

int countArgs(char *args[]) {                               // loo[ through list and count up each iteration to get length]
    int i = 0;
    while (args[i] != NULL) {
        i++;
    }
    return i;
}


// EXTERNAL COMMANDS
//
void externalCommand(char * args[], pid_t pid, bool background, char *prompt, int batchfile){
  if (pid < 0){
    printf("Failed to create child process, command failed"); //if pid < 0 send error
  }
  else if (pid == 0){                                       // check if in the child process 
    char * shellPath = getenv("shell");                     // get the path of the parent
    setenv("parent", shellPath, 1);                         // then set parent environment variable to the path
    openIO();                                                           // check for IO redirection and then set stdin and stdout to their respective files if needed
    execvp(args[0], args);                                      // replace the child process with the external command
    printf("Error unkown command");                   //if the external command doe snot exist then print this error and exit                                        
    exit(1);
  }
  else {
    if (!background){                                             // in the parent process if its not. abackground process wait for the child to finish
      wait(NULL);
    }
    else {                                                                // if it is a background process continue
      printf("Background process started with pid %d\n", pid);
      fflush(stdout);
      printPrompt(prompt, batchfile);
    }
  }
}


// IO REDIRECTION
bool checkIO(char ** args, char **inputFile, char **outputFile){ //function to check if IO redirection needs to be done
  bool appending = false;                                                                // sets variables
  int length = countArgs(args);
  for (int i = 0; i < length; i++){                                                         // loops throught args and checks if IO redirection is needed
    if (strcmp(args[i], "<") == 0) {                                                    // if there is an "<" check if ther is also an input file arg after it
      if (args[i + 1] == NULL) {                                                            // otherwise print error
        fprintf(stderr, "Syntax error: no input file\n");
      }
      else{                                                                                           //if there is an input file then set the variable inputFile to it
        *inputFile = args[i + 1];
        args[i] = NULL;                                                                       // remove the "<"
      }
    }
    else if (strcmp(args[i], ">") == 0) {                                           // same as input but for output checking for ">"
      if (args[i + 1] == NULL) {
        fprintf(stderr, "Syntax error: no output file\n");
      }
      else{
        *outputFile = args[i + 1];
        appending = false;
        args[i] = NULL;
      }
    }                                                                                                   // same as the two previous except checking for ">>"
    else if (strcmp(args[i], ">>") == 0) {
        if (args[i + 1] == NULL) {
        fprintf(stderr, "Syntax error: no output file\n");
       }
       else {
        *outputFile = args[i + 1];
        appending = true;                                                                   // sets append to true which means output file will be appended to not overwritten
        args[i] = NULL;
       }
      }
    }
  return appending;                                                                         // return whether append is true or false
}

void openIO(){
  if (outputFile != NULL) {                                                             // if ther eis an output file
    if (append){                                                                                // and we are appending
      if (freopen(outputFile, "a", stdout) == NULL){                      //open it in append mode and all stdout goes into it
        perror("Failed to open output file");                                   // if it fails display error
        exit(1);
      }
    }
    else  {                                                                                      // if not in append mode
      if(freopen(outputFile, "w", stdout) == NULL){                   //  open it in normal write mode
        perror("Failed to open output file");                                 // if it fails display error
        exit(1);
      }
    }
  }

  if (inputFile != NULL) {                                                        // check if there is an inputfile
    if (freopen(inputFile, "r", stdin) == NULL) {                     // open it in read mode
      perror("Failed to open input file");                                // if fail to open file send error and exit.
      exit(1);
    }
  }
}
//Eoghan hughes, 20729, I acknowledge the dcu academic integrity policy
