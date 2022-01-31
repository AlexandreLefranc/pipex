#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void ft_putstr_fd(char *str, int fd)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int redir_file_to_stdin(char *file)
{
	ssize_t	r;
	ssize_t fd;
	char	buffer[1024];

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "fd is -1\n", 10);
		return (-1);
	}
	r = read(fd, buffer, 1023);
	while (r != 0)
	{
		buffer[r] = '\0';
		ft_putstr_fd(buffer, 0);
		r = read(fd, buffer, 1023);
	}
	close(fd);
	return (0);
}

int main()
{
	char *filename = "test.txt";
	char *cmd[] = {"/bin/ls","-l"};

	// int fdout = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// dup2(fdout, STDIN_FILENO);
	redir_file_to_stdin(filename);
	execve(cmd[0], cmd, NULL);
}
