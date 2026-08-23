#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>

//global variables

#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // separators for args to be tokenised on 
extern char **environ;                         // environment variables
char manual_path[MAX_BUFFER];                 // path of the shell manual
extern char * inputFile;
extern char * outputFile;
extern bool append;

// function prototypes

//internal commands
void listDir(char * dirList[]);
void environShow();
void echoIt(char * argList[]);
void changeDir(char * argList[]);
void pauseIt();
void helpIt();

// hellper functions
int getCurDir(char prompt[]);
void printPrompt(char *prompt, int batchfile);
bool tokeniser(char buf[], char * args[]);
int countArgs(char* args[]);
void getManualPath(char executable[]);

//external Commands
void externalCommand(char * args[], pid_t pid, bool background, char *prompt, int batchfile);

// IO Redirection
bool checkIO(char ** args, char **inputFile, char **outputFile);
void openIO();

// Eoghan hughes, 20729, I acknowledge the dcu academic integrity policy
