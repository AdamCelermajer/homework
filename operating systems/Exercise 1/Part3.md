Custom Shell Implementation in C
===============================

Overview
--------

In this project, you will develop a simple command-line interpreter, or shell, named `myshell.c`. This custom shell will handle basic Linux commands like `ls`, `cat`, and `sleep` without supporting pipes or complex commands. The shell will be implemented in C using `fork()` and will extend its functionality by including certain directories in its environment variables.

Objectives
----------

* Implement a custom shell in C that can execute basic Linux commands.
* Handle additional directories as part of the environment variables for command execution.
* Implement specific shell commands (`history`, `cd`, `pwd`, `exit`) without using default Unix implementations.
* Ensure all commands run in the foreground and handle errors appropriately.

Environment Variables
---------------------

* The shell should accept any number of command-line arguments, each representing a path to a folder.
* These paths will be added to the environment variables, enabling the shell to execute commands located within these directories.

Custom Commands
---------------

You need to implement the following shell commands without using the Unix defaults:

* **`history`**: Display the list of commands that have been entered during the session.
* **`cd`**: Change the current directory within the shell environment.
* **`pwd`**: Print the current working directory.
* **`exit`**: Exit the shell.

These commands should be implemented using appropriate system calls and library functions available in C.

Command Execution
-----------------

* Commands should be executed in the foreground using `exec()` in a forked process.
* For commands not explicitly handled (`history`, `cd`, `pwd`, `exit`), the shell should use `exec()` to invoke them with the passed arguments.
* Use `strtok()` with a space delimiter to parse the command into its core components.

Error Handling
--------------

* If a system call fails, the shell should use `perror()` to print an error message indicating which system call failed, e.g., `perror("fork failed")`.

Output Specifications
---------------------

* The shell should not print anything except the required output from commands or error messages.
* The prompt should be displayed as follows:
```c
  printf("$ ");
  fflush(stdout);
```

Assumptions
-----------

*   The shell will handle up to 100 commands, with each command's length also limited to 100 characters.
*   There are no spaces in the names of directories and files passed as arguments to the shell.

Restrictions
------------

*   Adding new environment variables for command execution should not affect the existing ones prior to running the program.
*   Changes to the current directory (`cd`) within the shell should not affect the working directory after the shell is closed.