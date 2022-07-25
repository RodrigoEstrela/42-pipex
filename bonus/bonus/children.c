/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:35 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/04 12:38:11 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void	child_one(t_cmds *cmds, int fd[2], char **envp)
{
	int	i;

	i = -1;
	cmds->pid1 = fork();
	if (cmds->pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(cmds->cmd1[0], cmds->cmd1, envp);
		while (cmds->cmd1[++i])
			free(cmds->cmd1[i]);
		i = -1;
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}	
}
