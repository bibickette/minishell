🇫🇷 Version française disponible [ici](README_FR.md)
* * *

# Project presentation - `minishell`
## **Description**

This project consists of creating a **miniature Unix shell** in C.

The goal is to implement a fully functional command-line interpreter that executes commands, handles built-ins, pipes, redirections, environment variables, and signals. It mimics the behavior of a real shell while emphasizing memory management, process handling, and input parsing.

This project involves:
- Parsing user input and tokenizing commands
- Handling child processes and inter-process communication
- Managing signals (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- Implementing input/output redirections (`<`, `>`, `>>`, `<<`)
- Supporting pipes (`|`)
- Expanding environment variables (`$VAR`) and `$?` (last exit status)
- Implementing mandatory built-in commands
- Displaying a prompt and maintaining a working command history

* * *
## Languages & Technologies

**Language**
- C (C99 standard)

**Technologies**
- Makefile
- Unix system calls (`fork`, `execve`, `pipe`, `dup2`, `waitpid`)
- I/O redirection
- Signal handling (`SIGINT`, `SIGQUIT`)
- Environment variable management
- Linked lists (for managing commands and tokens)
- Dynamic memory management
- String parsing and manipulation

* * *
## Shell Features

### Prompt & Command Input
- The shell displays a prompt when waiting for a new command.
- Commands are read from standard input.
- History is maintained during the session.

### Built-in commands

| Command |                        Description                        |
|:-------:|:---------------------------------------------------------:|
|  echo   |      Prints text to the terminal; supports -n option      |
|   cd    | Changes the current directory (relative or absolute path) |
|   pwd   |           Prints the current working directory            |
| export  |                Sets environment variables                 |
|  unset  |               Removes environment variables               |
|   env   |              Displays environment variables               |
|  exit   |                      Exits the shell                      |

### Command execution
The program :
- executes external commands using `execve`
- searches executables either via `$PATH` or using relative/absolute paths
- handles only one global variable to store received signals (`SIGINT`, `SIGQUIT`); the handler does not access the main data structures

### Redirections
- `<` redirects **input**
- `>` redirects **output** (overwrite)
- `>>` redirects **output** (append)
- `<<` (`here-doc`) : reads input until a line containing the delimiter is seen. History is not updated for `here-doc` input.

### Pipes
- Commands can be chained using `|` : each command’s output is connected to the next command’s input via a pipe

### Quotes & Special characters
- **Single** quotes `'...'` prevent interpretation of meta-characters
- **Double** quotes `"..."` prevent interpretation of meta-characters **except** `$` for environment variable expansion
- Other meta-characters such as `\` and `;` are not interpreted
- Wildcards (`*`) are not supported

### Environment variables
- `$VAR` expands to the variable’s value.
- `$?` expands to the exit status of the most recently executed foreground pipeline.

### Signal handling
- `Ctrl-C` displays a new prompt on a new line.
- `Ctrl-D` exits the shell.
- `Ctrl-\` does nothing in interactive mode.

* * *
## Notes
Understanding and implementing [pipex](https://github.com/bibickette/pipex) is extremely useful for `minishell`, as it introduces core concepts such as pipes, process creation, and I/O redirection. These mechanisms are fundamental to `minishell` for executing pipelines (`cmd1 | cmd2`) and managing input/output redirections. Completing [pipex](https://github.com/bibickette/pipex) first provides a strong foundation for building minishell.

* * *
# Using `minishell`
## Makefile rules
1. **all** as *default rule*: builds the project, compiles all `.c` files into `.o`, then **creates**  the program (`minishell`)
2. **clean** : removes compiled object files (`.o`)
3. **fclean** : *clean* rule and removes the executable (`minishell`)
4. **re** : *fclean* then *all* rule

* * *

## How to use `minishell`

*Note : the `minishell` project works on its own and uses the [libft](https://github.com/bibickette/libft) library. Since the library is added as a submodule, you need to clone the repository with it.*
1. Clone `minishell` in a folder first  : `git clone --recurse-submodules git@github.com:bibickette/minishell.git`
2. Go to the `minishell` folder then compile it : `cd minishell && make`
3. Run `./minishell` without any argument
4. You can now type any commands like in a normal shell : `echo  "hello world ! " | cat -e`

### Valgrind & memory checks

*`minishell` was tested using **Valgrind** to ensure there are no memory leaks and that all allocated memory is properly freed. Like the [pipex](https://github.com/bibickette/pipex) project, it relies on system calls such as `fork`, `execve`,  `pipe`... some memory may still appear as reachable due to system-level allocations performed by the system and libraries. To obtain clean and meaningful results, a **suppression file** is used.*

You can run `minishell` with **Valgrind** using the following command : `valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=all.supp ./minishell`

The `all.supp` file filters out known and unavoidable leaks, this allows **Valgrind** to focus only on real memory leaks caused by the project itself.

You can now test my `minishell` !

* * *
*Project validation date : October 2, 2024*
