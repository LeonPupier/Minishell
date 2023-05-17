# Minishell

This project was completed as part of the curriculum at École 42. The goal of the project is to create a simple shell that can execute basic commands and handle redirections, pipes, and signals. 

## Installation

To install and run the program, follow these steps:

1. Clone the repository to your local machine.
2. Open a terminal window and navigate to the root directory of the project.
3. Run the command `make` to compile the program.
4. Run the program using the command `./minishell`.

## Usage

The shell supports the following built-in commands:

- `cd`: change the current working directory.
- `echo`: display a message on the screen.
- `env`: display the environment variables.
- `export`: export and display environment variables.
- `exit`: exit the shell.

In addition to the built-in commands, the shell can execute external commands by entering their name followed by any necessary arguments. The shell also supports redirections using the `>` and `<` operators, as well as pipes using the `|` operator.

## Example

Here's an example of how to use the shell to execute a command and redirect its output to a file:

```bash
$ echo "Hello, world!" > output.txt
```

In this example, the `echo` command is used to display the message "Hello, world!" on the screen, and the output is redirected to a file named "output.txt".

## Credits

This project was completed by Léon Pupier (lpupier) as part of the curriculum at École 42.
