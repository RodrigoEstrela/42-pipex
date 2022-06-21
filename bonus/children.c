/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:35 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/06/21 13:41:48 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void	child_one(t_cmds *cmds, char *file_in, int fd[2], char **envp)
{
	int	fdin;
	int	pid1;
	int	i;

	i = -1;
	pid1 = fork();
	if (pid1 == 0)
	{
		fdin = open(file_in, O_RDWR);
		dup2(fdin, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(cmds->cmd1[0], cmds->cmd1, envp);
		while (cmds->cmd1[++i])
			free(cmds->cmd1[i]);
		i = -1;
		while (cmds->cmd2[++i])
			free(cmds->cmd2[i]);
		close(fdin);
	}
}

void	child_two(t_cmds *cmds, char *file_out, int fd[2], char **envp)
{
	int	fdout;
	int	pid2;
	int	i;

	pid2 = fork();
	if (pid2 == 0)
	{
		fdout = open(file_out, O_TRUNC | O_CREAT | O_RDWR, 404);
		dup2(fdout, 1);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve(cmds->cmd2[0], cmds->cmd2, envp);
		close(fdout);
		i = -1;
		while (cmds->cmd1[++i])
			free(cmds->cmd1[i]);
		i = -1;
		while (cmds->cmd2[++i])
			free(cmds->cmd2[i]);
	}
}
