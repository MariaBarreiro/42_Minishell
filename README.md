*This project has been created as part of the 42 curriculum by mlima-si, mda-enca.*

# Minishell

## Description

**Minishell** is a simplified Unix shell developed as part of the curriculum at 42 School.  
The goal of the project is to recreate the core behavior of a Unix shell such as Bash while respecting strict constraints on allowed functions and coding standards.

The program provides an interactive command-line interface where users can execute commands, manage processes, and interact with the system environment.

Key concepts implemented in this project include:

- Command parsing and tokenization
- Execution of programs using `fork` and `execve`
- Built-in commands implementation
- Pipes and file redirections
- Environment variable management
- Signal handling
- Heredoc (`<<`) support

The project focuses heavily on **process control, file descriptors, memory management, and shell parsing**, providing a deep understanding of how Unix shells operate internally.

---

## Features

The implemented features include:

- Interactive prompt using `readline`
- Execution of external programs
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Pipes (`|`)
- Input redirection (`<`)
- Output redirection (`>`)
- Append redirection (`>>`)
- Heredoc (`<<`)
- Environment variable expansion (`$VAR`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)

---

## Instructions

### Requirements

The project was developed and tested on **Linux**.

Required dependencies:

- GCC
- Make
- Readline library

Install readline if needed:

```bash
sudo apt-get install libreadline-dev
```

## Compilation

Clone the repository and compile the project:
```bash
git clone <repository_url>
cd minishell
make
```

This will generate the executable:
```bash
./minishell
```
Running the Shell

Start the shell with:
```bash
./minishell
```

Example session:
```bash
minishell > echo Hello
Hello

minishell > ls | grep minishell

minishell > cat << EOF
hello
world
EOF

minishell > exit
```
## Project Structure

Typical components of the project include:
```
minishell/
│
├── parsing/        # Tokenization and command parsing
├── execution/      # Command execution and pipelines
├── builtins/       # Built-in commands
├── redirections/   # File redirection and heredoc
├── signals/        # Signal handling
├── utils/          # Helper functions
│
├── minishell.h
├── Makefile
└── README.md
```

## Technical Concepts

The project heavily relies on fundamental Unix mechanisms such as:

- fork() for process creation

- execve() for program execution

- pipe() for inter-process communication

- dup2() for file descriptor redirection

- waitpid() for process synchronization

Special care was taken to correctly manage:

- memory allocation and deallocation

- file descriptor lifecycle

- signal propagation between parent and child processes

---
## Resources

The following resources were used during development:

https://harm-smits.github.io/42docs/projects/minishell

https://42-cursus.gitbook.io/guide/3-rank-03/minishell

https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

These references helped understand shell architecture, parsing strategies, and execution models.

---
## AI Usage

AI tools were used only as auxiliary support during development.
Their use included:

- Clarifying behavior of Unix system calls (fork, execve, pipe, dup2)

- Understanding edge cases of shell behavior (redirections, heredocs, signals)

- Reviewing code structure and debugging strategies

- Assisting in documentation writing

All implementation decisions, debugging, and integration were performed manually by the project authors.

---
## Authors

- mlima-si

- mda-enca

Project developed as part of the curriculum of the 42 School.
