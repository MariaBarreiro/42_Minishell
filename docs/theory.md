# Parsing, Lexing, and Shell Notes

## Links
- https://pubs.opengroup.org/onlinepubs/9699919799.2018edition/utilities/V3_chap02.html#tag_18_10
- https://tomassetti.me/guide-parsing-algorithms-terminology/
- https://en.wikipedia.org/wiki/Lexer_hack

## Structure of a Parser
A parser is usually composed of two parts:
- **Lexer** (scanner or tokenizer)
- **Parser**

Some parsers do not depend on a separate lexer and combine the two steps. These are called **scannerless parsers**.

A lexer and a parser work in sequence: the lexer scans the input and produces tokens; the parser scans the tokens and produces the parsed result.

Example:
```
123 + 456  --(LEXER)-->  123(NUM)  +(PLUS)  456(NUM)  --(PARSER)-->  <sum-expression>
```

The definitions used by lexers and parsers are called **rules** or **productions**. In the example above, a lexer rule specifies that a sequence of digits corresponds to a token of type `NUM`, while a parser rule specifies that a sequence of tokens `NUM PLUS NUM` corresponds to a sum expression.

## Types of Tokens
- **Keywords**: reserved words the language treats as special (e.g., `if`, `while`) that cannot be used as identifiers.
- **Identifiers**: names you define for variables, functions, classes, etc.
- **Literals / Constants**: fixed values in code. Examples:
  - Numeric: `32`, `0.3`
  - Characters: `'a'`, `'b'`
  - Strings: `"Hello, World!"`
  - Booleans: `true`, `false`
- **Operators**: symbols that perform operations (e.g., `+`, `-`, `!`, `||`).
- **Delimiters / Separators / Punctuation**: `(`, `)`, `{`, `}`, `[`, `]`, `;`, `,`
- **Comments**
- **Preprocessor tokens**: handled before compilation (e.g., `#define`, `#if`, `#include`, `#endif`).

## Left-Recursive Rules
A rule is **left-recursive** if it starts with a reference to itself.

Illustrative evaluation for `5 + 3 * 2` (abstracted):
```
expression -> expression + term
term       -> term * factor | factor
factor     -> NUM | '(' expression ')'
```
Possible derivation:
```
expression
=> expression + term
=> term + term
=> factor + term
=> NUM(5) + term
=> NUM(5) + term * factor
=> NUM(5) + factor * factor
=> NUM(5) + NUM(3) * NUM(2)
=> 5 + 3 * 2  ==>  11   (with standard precedence/associativity)
```

## Embedded Actions
**Embedded actions** are snippets of code executed every time a rule is matched. They’re used to build AST nodes, emit bytecode, accumulate values, perform checks, etc.

Example (Yacc/Bison style, conceptual):
```yacc
expr
  : expr '+' term   { $$ = $1 + $3; }
  | term            { $$ = $1; }
  ;
```

## BNF
**BNF (Backus–Naur Form)** is a notation for formal grammar specifications. Variants include EBNF and ABNF. Typical forms:
```bnf
<expr>   ::= <expr> "+" <term> | <term>
<term>   ::= <term> "*" <factor> | <factor>
<factor> ::= NUM | "(" <expr> ")"
```

## Videos
- https://www.youtube.com/watch?v=xCySbqj9BKI&list=PL2POs8ZJ4I2JJK3lICRW0b-L2y9mLiDmU

## Books
- **Unix and Linux System Administration Handbook**

### Pipes and Redirection (p. 33)
- Standard streams: `STDIN`(0), `STDOUT`(1), `STDERR`(2).
- Most commands read from `STDIN` and write to `STDOUT`.
- Shell interprets:
  - `<` connect command's `STDIN` to a file.
  - `>` redirect `STDOUT` and replace file contents.
  - `>>` append `STDOUT` to file.
  - `|` pipe `STDOUT` of left command to `STDIN` of right command.  
    Example: `ps -ef | grep httpd`
  - `&&` run the next command only if the previous succeeds (exit status 0).
  - `||` run the next command only if the previous fails (nonzero exit status).

### Variables and Quoting
- Assign unmarked; reference with `$name` or `${name}`.
  ```sh
  etcdir='/etc'
  echo "$etcdir"
  echo "Saved ${rev}th version of mdadm.conf."
  ```
- All caps conventionally indicate environment variables.
- Lowercase with underscores suggest local variables.
- Quoting:
  - Single quotes: no expansion.
  - Double quotes: expand variables and command substitutions, and allow globbing.
- Backquotes `` `cmd` `` execute and substitute output (modern form `$(cmd)` preferred):
  ```sh
  echo "There are $(wc -l < /etc/passwd) lines in the passwd file."
  ```

### Common Filter Commands
Any well-behaved command that reads `STDIN` and writes `STDOUT` can be used as a filter in a pipeline.

---

## The Unix Programming Environment

### Pipes
- A **pipe** connects the output of one program to the input of another without temporary files.
- A **pipeline** is two or more programs connected by pipes.
- Programs in a pipeline run concurrently.
- Common command form: `command [optional-arguments] [optional-filenames]`.
  If no filenames are given, the command reads from standard input.

### Processes
- A **program** is code; a **process** is a running instance.
- Multiple instances of a program are separate processes with distinct PIDs.
- TTY: terminal associated with the process.
- Process hierarchy: each process has a parent; shells spawn children.

### Tailoring the Environment
- `.profile` in your home directory runs at login.
- Shell variables control behavior (e.g., `PS1` for the prompt).
- Special variables:
  - `HOME`: your home directory.
  - `MAIL`: your mailbox file.
  - `PATH`: search path for commands.

### The File System — What's in a file?
Example outputs relate to:
- The directory containing a program (e.g., `/bin`)
- The binary executable (e.g., `/bin/ed`)
- Source code (e.g., `/usr/src/cmd/ed.c`)
- Manual page (e.g., `/usr/man/man1/ed.1`)

### Using the Shell — Metacharacters
- `*` match any string in filenames.
- `>` redirect standard output.
- `>>` append standard output.
- `<` redirect standard input.
- `|` connect `STDOUT` to `STDIN` of next command.
- `<<str` here-document terminator `str`.
- `?` match any single character in filenames.
- `[ccc]` match any single character from the set.
- `;` command terminator; run sequentially.
- `&` run in background.
- `` `...` `` command substitution.
- `( ... )` run in a subshell.
- `$1..$9` positional parameters in shell scripts.
- `$var` value of variable `var`.
- `\c` escape next character `c`.
- `'...'` take literally.
- `"..."` take literally except `$`, backquotes, and `\` processed.
- `#` start of comment.
- `var=value` variable assignment.
- `p1 && p2` run `p2` if `p1` succeeds.
- `p1 || p2` run `p2` if `p1` fails.

### Echo
- Ends with newline by default; use `-n` to suppress.

### Creating New Commands
- Shell reads commands from a file if named as an argument:
  ```sh
  echo 'who | wc -l' > nu
  sh < nu     # feed nu to sh via stdin
  sh nu       # execute nu as a script file
  ```
- Make a script executable:
  ```sh
  chmod +x nu
  ./nu
  ```
- Executable text files are run by spawning a subshell.

### Command Arguments and Parameters
- Use positional parameters in scripts:
  ```sh
  # cx: make a file executable
  echo 'chmod +x $1' > cx
  sh cx cx        # make cx itself executable
  echo 'echo Hi, there!' > hello
  ./hello         # cannot execute yet
  sh cx hello     # or chmod +x hello
  ./hello
  ```

### Program Output as Arguments
```sh
echo "At the tone the time will be $(date)."
```

### Shell Variables
- Positional parameters `$1`..`$9` are for script arguments.
- Variable scope: a child shell does not inherit variables unless exported.
  ```sh
  x=Hello
  sh           # new shell
  echo "$x"    # empty unless exported
  exit
  echo "$x"    # Hello
  ```
- To affect the current shell, **source** a file:
  ```sh
  . games      # same as: source games
  ```
- Temporary environment for a command:
  ```sh
  VAR=value command
  ```
- `export` to pass to subshells:
  ```sh
  export x
  ```

### More on I/O Redirection
- Default fds: 0 stdin, 1 stdout, 2 stderr.
- Forms:
  - `>file`, `>>file`, `<file`, `p1|p2`
  - `n>file`, `n>>file`
  - `n>&m` merge output from fd `n` into fd `m`
  - `n<&m` merge input from fd `n` from fd `m`
  - `<<s` here-document until a line starting with `s`
  - `<<\s` or `<<'s'` here-document with no substitution
