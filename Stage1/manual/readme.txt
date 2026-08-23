===================================================================
                     simpleshell  USER MANUAL
===================================================================
    help:
          
          Displays this manual page.
          Press space to move to the next page.,
          Press enter to go to next line,
          Press b to go to previous page,
          Press q to exit the manual.

    cd <directory>:

          Changes the current working directory to <directory>.
          If no argument is given, it will print the current
          working directory to the terminal.
    
    echo <text ...>:

          Displays the supplied text on the screen followed by
          a newline. Consecutive tabs or spaces are replaced
          by a single space.

    pause:

          Pause the shell until the Enter key is pressed.
    
    quit:

          Exits the shell.
    
    clr:

          Clears the terminal screen.

    dir <directory>:

          Lists all the contents of <directory> via the command
          'Ls -al'. If no argument <directory> is given then
          the contents of the current directory will be listed.

    environ:

          Lists all of the environment strings.

    ../simpleshell <batchfile>:

          When running the simpleshell you may run it with a
          batchfile argument that is a file with commands
          stored in it and the shell will run it automatically
          and then quit.

    NOTES

          * The shell sets the environment variable
            shell=<full-path-to-simpleshell>
            on startup.
          * External commands are not supported.
    
===================================================================
===================================================================

#Eoghan hughes, 20729, I acknowledge the dcu academic integrity policy
