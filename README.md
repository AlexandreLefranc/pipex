# pipex

# Help

- [Help](https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe)
- [Kind of cheat](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901)
- https://elearning.intra.42.fr/notions/57/subnotions/245/videos/203

# TODO

-

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

- [stackoverflow](https://stackoverflow.com/questions/7861611/can-someone-explain-what-dup-in-c-does)
- `new_fd = dup(fd)` duplique dans un nouveau fd libre (new_fd). Par exemple, si fd = 3, `dup(3)` creera un nouveau fd, new_fd = 4 identique a fd. On peut donc fermer fd et utiliser new_fd.
- `dup2(fd, STDIN_FILENO)` duplique fd dans STDIN_FILENO. Ainsi, STDIN_FILENO devient fd.

## pipe

- [Geeksforgeeks](https://www.geeksforgeeks.org/pipe-system-call/)

## execve

- [video intra minishell1](https://elearning.intra.42.fr/notions/minishell/subnotions)
- [video intra minishell2](https://cdn.intra.42.fr/video/video/203/low_d_ft_sh2.mp4)
- [No path search](https://stackoverflow.com/questions/10068327/what-does-execve-do)
- [execve using stdin](https://stackoverflow.com/questions/36083984/execve-with-redirected-stdin-from-file)

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
