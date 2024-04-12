# Minishell
Minishell is a simple Unix shell program developed as part of a collaborative project by a group of two at 42 school. It provides a basic command-line interface for users to interact with their operating system.

### Overview
Minishell is a lightweight shell program that supports basic shell commands and features, including command execution, environment variable management, and simple I/O redirection. It aims to provide a user-friendly interface for users to execute commands and manage their system tasks.

### Language : ![C language](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)

### Features
Command execution: Minishell can execute shell commands entered by the user, including built-in commands and external programs.
Environment variables: Users can manage environment variables, including setting them, unsetting them, and displaying their values.
I/O redirection: Minishell supports basic I/O redirection, allowing users to redirect input and output streams to and from files.
Error handling: Minishell provides robust error handling for invalid commands, input/output errors, and other exceptional conditions.

### Built-in Commands
Minishell includes several built-in commands for performing common shell operations:

Echo: Display a line of text and we need to handle the flag -n.
Export: Set or export environment variables.
Env: Display environment variables.
Cd: Change the current working directory.
Unset: Unset environment variables.
Pwd: Print the current working directory.

#### Examples
Echo:
```shell
$> ./minishell
minishell$ echo "Hello, world!"
Hello, world!
minishell$ echo -n "Hello, world!"
Hello, world!minishell$
```

Export:
```shell
$> ./minishell
minishell$ export MY_VAR="Hello, world!"
minishell$ echo $MY_VAR
Hello, world!
```

Env:
```shell
$> ./minishell
minishell$ env
PATH=/usr/bin:/bin
HOME=/home/user
MY_VAR=Hello, world!
```

Cd:
```shell
$> ./minishell
minishell$ cd /path/to/directory
```

Unset:
```shell
$> ./minishell
minishell$ unset MY_VAR
```

Pwd:
```shell
$> ./minishell
minishell$ pwd
/home/user/documents
```
These built-in commands provide essential functionality for navigating the shell environment and managing system tasks directly within Minishell.


### Usage
#### Compilation
To compile the Minishell program, run the following command:

```
make
```

#### Execution
To execute the Minishell program, run the following command:

```
./minishell
```

#### Examples

Executing Shell Commands:

```
$> ./minishell
minishell$ ls
file1.txt file2.txt
minishell$ pwd
/home/user/documents
```

Managing Environment Variables:

```
$> ./minishell
minishell$ export MY_VAR="Hello, world!"
minishell$ echo $MY_VAR
Hello, world!
```

I/O Redirection:

```
$> ./minishell
minishell$ ls > files.txt
minishell$ cat files.txt
file1.txt
file2.txt
```

Multiple Pipes:

```
$> ./minishell
minishell$ ls | grep file | wc -l
2
```

Multiple Here-Documents:

```
$> ./minishell
minishell$ cat <<EOF1 <<EOF2
> Hello from EOF1
> EOF1
> Hello from EOF2
> EOF2
```

Combining Multiple Pipes and Here-Documents:

```
$> ./minishell
minishell$ cat <<EOF1 | grep "Hello" | wc -w <<EOF2
> Hello from EOF1
> EOF1
> Hello from EOF2
> EOF2
4
```

### Help

[the best git hub for help on this project](https://github.com/vietdu91/42_minishell)

### Authors
This project was created collaboratively by @Zotaru and @Lxnchy as part of the course requirements at 42 school (you can find our git hub under).

<p align="center">
  <br/>
  <a href="https://github.com/Zotaru">
    <img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white"/>
  </a>
  <a href="https://github.com/Lxnchy">
    <img src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white" />
  </a>
</p>


