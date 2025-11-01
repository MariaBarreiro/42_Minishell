## Links ##

https://aosabook.org/en/v1/bash.html

-> Bash processing is much like a shell pipeline: after being read from the terminal or a script, data is pssed through a number of stages, transformed at each step, until the shell finally executes a command and collects its return status.

<img width="567" height="450" alt="Screenshot from 2025-11-01 11-21-00" src="https://github.com/user-attachments/assets/4123fea2-3b0a-4a6c-9812-ad0be9f53368" />

- Variables and parameters-
    -> Variable values are strings (name=value).
    -> Value is optional. Omitting it assigns the empty string to name. (unset variables)
    -> $WORD introduces a variable or parameter reference. The word including the dolar sign is replaced with the value of the named variable.
    -> Bash uses hash tables to store and retrieve shell variables, and linked lists of these hash tables to implement variable scoping.
