#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

//global variables

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // separators for args to be tokenised on 
extern char **environ;                         // environment variables
char manual_path[MAX_BUFFER];                  // path of the shell manual

// function prototypes

void listDir(char * dirList[]);
void environShow();
void echoIt(char * argList[]);
void changeDir(char * argList[]);
void pauseIt();
void helpIt();
int getCurDir(char prompt[]);
void tokeniser(char buf[], char * args[]);
void getManualPath(char executable[]);

// Eoghan hughes, 20729, I acknowledge the dcu academic integrity policy
