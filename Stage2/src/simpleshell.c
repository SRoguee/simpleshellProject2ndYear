/* 
********************************************************************
version: 1.0
date:    March 2026
author:  Eoghan hughes
student number: 20729
eoghan.hughes2@mail.dcu.ie
*******************************************************************/
#include "simpleshell.h"


char *inputFile = NULL;         // set the input and output filesfor IO redirection globally
char *outputFile = NULL;      
bool append = false;              // set append to false initially
int main (int argc, char ** argv)
{
  char fullPath[100];                           //full path of the shell environment variable
  char buf[MAX_BUFFER];                        // line buffer
  char * args[MAX_ARGS];                       // pointers to arg strings
  char prompt[100];                           // initialise the prompt
  int batchfile = 0;                              // set batchfile to 0
  FILE *fptr;
  bool background = false;                // background is false
  
    if (argv[1]){
      // Open a file in read mode
      fptr = fopen(argv[1], "r");
      if (!fptr){
        printf("Error, unable to open file '%s'\n", argv[1]);
        return -1;
      }
      batchfile = 1;
    }
    getManualPath(argv[0]);                             //gets the path to the simplshell manual
    setenv("shell", getcwd(fullPath, MAX_BUFFER), 1);   //sets the environment variable shell to the path of the shell
    /* keep reading input until "quit" command or eof of redirected input */
    //if batchfile present do smthn
    while (1) { 
         /* get command line from input */
      printPrompt(prompt, batchfile);
      
      if (batchfile){                                   // if the batchfile was opened successfully, try read it
        if (!fgets(buf, MAX_BUFFER, fptr)){             // tries to read one line from the batchfile to buf
          fclose(fptr);
          break;                                        // if it fails break the while loop and quit.
        }
      }
      else{                                     
        if (!fgets(buf, MAX_BUFFER, stdin)) {           // tries to read from stdin to buf if it fails break the loop.
          break;                              
        }
      }
      background = tokeniser(buf, args);                //splits buf into tokens on the space, newline and tab chars.
      inputFile = NULL;                                     // set input output and append to null and false before checking for IO redirection args
      outputFile = NULL;
      append = false;
      append = checkIO(args, &inputFile, &outputFile);
      

      if (args[0]) {                                    // if there's any commands to attempt to execute then execute them.
          /* check for internal/external command */
        if (!strcmp(args[0],"clr")) {                   // "clear" command clears the terminal
          system("clear");
          continue;
        }
        if (!strcmp(args[0], "dir")) {                  // "dir" command lists the contents of a given directory
          openIO();                                     //checks if there is  io direction for this command
          listDir(args);                                // or the current one
          fflush(stdout);                                   // sets stdout back to normal so output doesnt keep going into a file
          freopen("/dev/tty", "w", stdout);
          continue;
        }
        if (!strcmp(args[0], "environ")) {              //"environ" command prints the list of environment strings
          openIO();
          environShow();
          fflush(stdout);
          freopen("/dev/tty", "w", stdout);
          continue;
        }
        if (!strcmp(args[0], "cd")) {                   //"cd" command changes the directory path to the gen arg or
          changeDir(args);                              //prints the current path if no directory is given
          continue;
        }
        if (!strcmp(args[0], "pause")) {                //"pause" command, freezes the shell until you press enter
          pauseIt();
          continue;
        }
        if (!strcmp(args[0], "echo")) {                 //"echo" command, prints any arguments that come after it
          openIO();
          echoIt(args + 1);                             // to the terminal separated by single space characters.
          fflush(stdout);
          freopen("/dev/tty", "w", stdout);
          continue;
        }
        if (!strcmp(args[0], "help")) {                 //"help" command, shows the manual for this shell.
          openIO();
          helpIt();
          fflush(stdout);
          freopen("/dev/tty", "w", stdout);
          continue;
        }
        if (!strcmp(args[0],"quit"))                    // "quit" command, quits the shell
          break;
        else{                                           //if the args don't match any case try to execute as an external command
          pid_t pid = fork();
          externalCommand(args, pid, background, prompt, batchfile);
          
        }
      }
    }
  }

// Eoghan hughes, 20729, I acknowledge the dcu academic integrity policy

