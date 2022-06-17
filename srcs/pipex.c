#include "pipex.h"

int main(int ac, char **av, char **envp)
{
	int fd[2];
	int pid1;
	int pid2;
	int  fdin;
	int  fdout;
	char  **cmd1;
	char  **cmd2;
	int		i;
	(void)ac;

	i = -1;
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	free(cmd1[0]);
	free(cmd2[0]);
	cmd1[0] = check_commands(av[2], envp);
	arranjar_cmd(cmd1);
	cmd2[0] = check_commands(av[3], envp);
	arranjar_cmd(cmd2);
	if (pipe(fd) == -1)
		exit(0);
	pid1 = fork();
	if (pid1 == 0)
	{
		fdin = open(av[1], O_RDWR);
		dup2(fdin, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(cmd1[0], cmd1, envp);
		while(cmd1[++i])
			free(cmd1[i]);
		i = -1;
		while(cmd2[++i])
			free(cmd2[i]);
		close(fdin);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		fdout = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 777);
		dup2(fdout, 1);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve(cmd2[0], cmd2, envp);
		close(fdout);
		i = -1;
		while(cmd1[++i])
			free(cmd1[i]);
		i = -1;
		while(cmd2[++i])
			free(cmd2[i]);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	i = -1;
	while(cmd1[++i])
		free(cmd1[i]);
	i = 0;
	free(cmd1);
	while(cmd2[i])
		free(cmd2[i++]);
	free(cmd2);
//	system("leaks -fullContent pipex");
    return 0;
}
