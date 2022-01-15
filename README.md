# pipex

# Help

- [Help](https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe)
- [Kind of cheat](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)

# Exploration

- It looks like `< infile cmd1 | cmd2 > outfile` is equivalent to \
`echo infile | cmd1 | cmd2 > outfile`

## fork and wait

- [About fork](https://linuxhint.com/c_fork_system_call/)
- fork duplicate the process !
	- child process which got `fork` return value to `0`
	- parent process which got `fork` return value to `child pid`

Typical structure

```c
pid_t forkStatus;
forkStatus = fork();
/* Child... */
if (forkStatus == 0)
{
	...
}
/* Parent... */
else if (forkStatus != -1)
{
	...
}
else
	perror("Error while calling the fork function");
```

- `wait` is used in the parent fork to wait for the child to finish.

## access

- [access](https://codeforwin.org/2018/03/c-program-check-file-or-directory-exists-not.html)

## dup / dup2

## pipe

## execve

## unlink

- [link](https://linuxhint.com/unlink-system-call-in-c/)
- It seems to unlink a filename to a file. Which is equivalent to a deletion.


# Structure

```
lst_cmd = {echo;next}>{cmd1;next}>{cmd2;next}>{cmd3;next}
files = {infile;outfile}
```

```
parse + check input
open infile (readonly)
open outfile (writeonly)

```
