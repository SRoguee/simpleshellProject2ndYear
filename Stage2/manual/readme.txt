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

      
      I/O Redirection:

            The shell allows you to redirect input and output using the following symbols

            input = "<"
            output (overwrite files) = ">"
            output (without overwriting) = ">>"

            An example of input redircetion is shown below:

                  python3 test.py < input.txt 

            in this example the python program "test.py" would take some input with the "input()" function normally from the keyboard
            however with "input.txt" it auto =matically feeds the inputs into the program going line by line through the text file.

            Note that if the input file does not exist the command will fail

            An example of output redirection is shown below:

                  dir > out.txt

            in this example the output of the command "dir" is written into the file "out.txt" if the file does not exist already it will be created
            if it does exist, any text in it will be overwritten, to avoid this you may use the ">>" arrow instead which adds the output onto the 
            end of the file.

            you may also use input and output redirection together for example

                  python3 test.py < input.txt >> out.txt

            this command would send inputs into the program "test.py" and then the outputs of "test.txt" would be stored in "out.txt"

            the following internal commands support redirection

            dir
            environ
            help
            echo

      Background Command Execution:

            Commands can be executed in the background using the & symbol at the end of a command line
            
                  e.g. sudo rm -rf & (maybe don't try this command)

            this means that you can run a command like this and it will execute in the background and the shell will not wait for it to finish so you 
            will be sent back to the command prompt to enter another command straight away

            normally you must wait for a command to finish before executing another command in the same window

      Program environment

            Environment variables store information used by the shell and programs.

            this program sets the location of the shell to the environment variable "shell"
            when executing external commands a new environment variable called "parent" is set which is the location of the parent process a.k.a. the shell.
            pwd is also set to the current directory anytime the user changes directories
.
    
===================================================================
===================================================================

#Eoghan hughes, 20729, I acknowledge the dcu academic integrity policy
