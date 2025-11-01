# External Functions Reference

## **readline**
```c
char *readline(const char *prompt) → #include <stdio.h>
```
- Reads a line from the terminal and returns it.
- If `prompt` is NULL, no prompt is issued.
- Line is allocated with `malloc()` → caller **must free** it.
- Automatically removes the newline.

---

## **rl_clear_history**
```c
void rl_clear_history(void)
```
- Clears the history list by deleting all entries.
- Frees private data that Readline saves in the history list.

---

## **rl_on_new_line**
```c
int rl_on_new_line(void)
```
- Informs update functions that we’ve moved onto a new (empty) line.
- Usually used after outputting a newline.

---

## **rl_replace_line**
```c
void rl_replace_line(const char *text, int clear_undo)
```
- Replaces the contents of `rl_line_buffer` with `text`.  
  *`rl_line_buffer` is the line gathered so far.*
- Preserves point and mark where possible.
- If `clear_undo` ≠ 0, clears the undo list.

---

## **rl_redisplay**
```c
void rl_redisplay(void)
```
- Updates the display to match the current contents of `rl_line_buffer`.

---

## **add_history**
```c
void add_history(char *s)
```
- Saves the given line in history.
- Basically the C version of pressing “↑” in bash.

---

## **access**
```c
int access(const char *pathname, int mode) → #include <unistd.h>
```
- Checks if the process can access `pathname`.
- Follows symbolic links.
- `mode` can be:
  - `F_OK`: check existence.
  - `R_OK`, `W_OK`, `X_OK`: check read, write, execute permission.
- Uses the real UID/GID of the caller.

---

## **open**
```c
int open(const char *path, int flags, …, mode_t mode) → #include <fcntl.h>
```
- Opens the file specified by `path`.  
  Optionally creates it if `O_CREAT` is in `flags`.
- Returns a file descriptor (lowest unused one).
- Descriptor remains open across `execve()` unless flagged otherwise.
- `flags` must include one of `O_RDONLY`, `O_WRONLY`, or `O_RDWR`.

---

## **read**
```c
ssize_t read(int fd, void *buf, size_t count) → #include <unistd.h>
```
- Reads up to `count` bytes from file descriptor `fd` into `buf`.
- Returns `0` if at end of file.
- Increments file offset by bytes read.

---

## **close**
```c
int close(int fd) → #include <unistd.h>
```
- Closes a file descriptor so it can be reused.
- If last reference, resources are freed.
- Returns `0` on success, `-1` on error.

---

## **fork**
```c
pid_t fork(void) → #include <unistd.h>
```
- Creates a new process (child).
- Returns child PID to parent, `0` to child, `-1` on error.
- Parent and child have separate memory spaces.

---

## **wait**
```c
pid_t wait(int *wstatus) → #include <sys/wait.h>
```
- Waits for a child process to change state.
- Returns immediately if a child already changed state.
- Blocks otherwise until a child terminates or a signal interrupts it.

---

## **waitpid**
```c
int waitpid(pid_t pid, int *wstatus, int options) → #include <sys/wait.h>
```
- Like `wait`, but allows specifying which child.
- `pid` values:
  - `< -1`: any child in group `|pid|`
  - `-1`: any child
  - `0`: any child in same process group
  - `> 0`: specific child

---

## **wait3 / wait4**
```c
pid_t wait3(int *wstatus, int options, struct rusage *rusage)
pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)
```
- `wait3`: waits for any child, can return resource usage.
- `wait4`: same, but can target a specific child.

---

## **signal**
```c
sighandler_t signal(int signum, sighandler_t handler) → #include <signal.h>
```
- Sets handler for a signal (`SIG_IGN`, `SIG_DFL`, or custom).
- `SIGKILL` and `SIGSTOP` can’t be caught or ignored.

---

## **sigaction**
```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
```
- Defines how to handle a signal.
- Uses `struct sigaction`:
  ```c
  struct sigaction {
      void (*sa_handler)(int);
      void (*sa_sigaction)(int, siginfo_t *, void *);
      sigset_t sa_mask;
      int sa_flags;
      void (*sa_restorer)(void);
  };
  ```
- `SA_SIGINFO` enables use of `sa_sigaction`.

---

## **sigemptyset / sigaddset**
```c
int sigemptyset(sigset_t *set)
int sigaddset(sigset_t *set, int signo)
```
- `sigemptyset` initializes a signal set.
- `sigaddset` adds a signal to it.

---

## **kill**
```c
int kill(pid_t pid, int sig) → #include <signal.h>
```
- Sends signal `sig` to a process or group:
  - `pid > 0`: that process.
  - `pid == 0`: current group.
  - `pid == -1`: all permitted processes.
  - `pid < -1`: group `|pid|`.
  - `sig == 0`: no signal, just permission check.

---

## **exit**
```c
void exit(int status) → #include <stdlib.h>
```
- Terminates the process.
- Returns least significant byte of `status` to parent.

---

## **getcwd / chdir**
```c
char *getcwd(char *buf, size_t size)
int chdir(const char *path)
```
- `getcwd`: copies absolute path of current directory into `buf`.
- `chdir`: changes current directory.

---

## **stat / lstat / fstat**
```c
int stat(const char *path, struct stat *statbuf)
int lstat(const char *path, struct stat *statbuf)
int fstat(int fd, struct stat *statbuf)
```
- Get file info.
- `lstat` → for symbolic link itself.
- `fstat` → via file descriptor.

---

## **unlink**
```c
int unlink(const char *path)
```
- Removes a file name. Deletes file when no links or open fds remain.

---

## **execve**
```c
int execve(const char *path, char *const argv[], char *const envp[])
```
- Replaces current process with a new program.

---

## **dup / dup2**
```c
int dup(int oldfd)
int dup2(int oldfd, int newfd)
```
- `dup`: duplicates a file descriptor (lowest free number).
- `dup2`: duplicates to a specific descriptor.

---

## **pipe**
```c
int pipe(int pipefd[2])
```
- Creates a unidirectional communication channel.
- `pipefd[0]` = read end, `pipefd[1]` = write end.

---

## **opendir / readdir / closedir**
```c
DIR *opendir(const char *name)
struct dirent *readdir(DIR *dirp)
int closedir(DIR *dirp)
```
- `opendir`: open a directory stream.
- `readdir`: read entries (`struct dirent`).
- `closedir`: close the stream.

---

## **strerror / perror**
```c
char *strerror(int errnum)
void perror(const char *s)
```
- `strerror`: returns string for error number.
- `perror`: prints descriptive error to stderr.

---

## **isatty / ttyname / ttyslot**
```c
int isatty(int fd)
char *ttyname(int fd)
int ttyslot(void)
```
- Terminal-related functions.
- `isatty`: checks if fd is terminal.
- `ttyname`: gets terminal path.
- `ttyslot`: finds user’s terminal index.

---

## **ioctl**
```c
int ioctl(int fd, unsigned long op, …) → #include <sys/ioctl.h>
```
- Controls device parameters.
- `op`: operation code, device-dependent.
- Third arg: pointer to memory.

---

## **getenv**
```c
char *getenv(const char *name) → #include <stdlib.h>
```
- Returns environment variable value.

---

## **tcsetattr / tcgetattr**
```c
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p)
int tcgetattr(int fd, struct termios *termios_p)
```
- Get or set terminal attributes.

---

## **tgetent / tgetflag / tgetnum / tgetstr / tgoto / tputs**
```c
int tgetent(char *bp, const char *name)
int tgetflag(const char *id)
int tgetnum(const char *id)
char *tgetstr(const char *id, char **area)
char *tgoto(const char *cap, int col, int row)
int tputs(const char *str, int affcnt, int (*putc)(int))
```
- Terminal capabilities (termcap/terminfo).
- Use `tgetent` first, then the others to query or print terminal features.
