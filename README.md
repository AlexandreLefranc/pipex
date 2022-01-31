# pipex

- Recode behavior of `< file1 cmd1 | cmd2 > file2`.
- One bonus is extending it to `< file 1 cmd1 | cmd2 | ... | cmdn > file2`.
- Function allowed :
	- access
	- open
	- close
	- unlink
	- read
	- write
	- malloc
	- waitpid
	- wait
	- free
	- pipe
	- dup
	- dup2
	- execve
	- fork
	- perror
	- strerror
	- exit


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
- Return 0 when success and -1 on fail.
- On fail, errno is set to 2 (No such file or directory) or 13 (Permission denied)

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


# Pseudo-code

Main

```c
main(argc, argv, envp):
	check_input(argc, argv, envp)
	list = parse_input(argc, argv, envp)
	run_pipex(list, argc, argv, envp)
```

check input

```c
if argc < 5:
	print_usage
	exit
```

parse_input

```c
list = create_list(argv)
```

run_pipex

```
get_infilename
get_outfilename
while there are commands:
	access and open infile
	if failed:
		print error
		find a way to
		continue
	duplicate fd_infile in STDIN_FILENO
	run the command to fd_tmp
	duplicate fd_tmp to
```


```
run first command:
	pipe
	open infile
	if open fail:
		close pipe write_end
		return pipe read_end
	fork
	child:
		close pipe read_end
		dup infile in stdin + close
		dup pipe write_end in stdout + close
		execve cmd
		perror and exit
	parent:
		wait child
		close infile
		close pipe write end
		return pipe read end

while there are commands:
	run mid commands:
		pipe
		fork
		child:
			dup previous_pipe_read_end in stdin + close
			dup pipe write_end in stdout
			execve cmd
			perror and exit
		parent:
			wait child
			close prev_pipe_read_end
			close pipe write_end
			return pipe read_end

end:
	open outfile
	dup outfile in stdout
	read previous fd
	close outfile
	exit 0

```

OR

For each command, write in in temporary file and at each new command, treat this temporary file as infile. And at the end, copy the content in outfile.

# List of tests

## Normal use

```
./pipex pipex "ls -l" "grep txt" "wc -l" out_mine
< pipex ls -l | grep txt | wc -l > out_real
```

---

```
echo "Hey\nje suis\nasdkl\n\n ds\n trer\n" > infile

./pipex infile "tr 'a' 'e'" "grep e" "wc -l" out_mine
< infile tr 'a' 'e' | grep e | wc -l > out_real
```

## Error use

```
touch wronly
chmod 222 wronly

./pipex wronly "ls -l" "grep txt" "wc -l" out_mine
< wronly ls -l | grep txt | wc -l > out_real
```


```
touch rdonly
chmod 444 rdonly

./pipex pipex "ls -l" "wc -l" rdonly
< pipex ls -l | wc -l > rdonly
```


```
./pipex pipex "" "wc -l" out_mine
< pipex | wc -l > out_real
```


Not behave well :
```
./pipex pipex "" "" out_mine
< pipex | > out_real
```