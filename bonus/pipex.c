/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:13 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/04 15:22:32 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_cmds	*cmds_initializer(t_cmds *cmds, char **av, char **envp, int i)
{
	cmds->cmd1 = ft_split(av[i], ' ');
	free(cmds->cmd1[0]);
	cmds->cmd1[0] = check_commands(av[i], envp);
	arranjar_cmd(cmds->cmd1);
	return (cmds);
}

void	free_cmds(t_cmds *cmds)
{
	int	i;

	i = -1;
	while (cmds->cmd1[++i])
		free(cmds->cmd1[i]);
	free(cmds->cmd1);
}

int	main(int ac, char **av, char **envp)
{
	t_cmds	*cmds;
	int		i;
	int		fd[2];
	int		fd1;
	int		fd2;

	cmds = malloc(sizeof(t_cmds) * 1);
	
	if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		i = 2;
		fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		ft_here_doc(av[2]);
	}
	
	else
	{
		i = 1;
		fd1 = open(av[1], O_RDONLY, 0777);
		fd2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	while (++i < ac - 2)
	{
		cmds = cmds_initializer(cmds, av, envp, i);
		if (pipe(fd) == -1)
			exit(0);
		child_one(cmds, fd, envp);
		free_cmds(cmds);
	}

	cmds = cmds_initializer(cmds, av, envp, ac - 2);
	dup2(fd2, 1);
	execve(cmds->cmd1[0], cmds->cmd1, envp);
	free(cmds);
	exit(0);
}
