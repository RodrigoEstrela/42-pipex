/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:13 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/25 11:45:36 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmds	*cmds_initializer(t_cmds *cmds, char **av, char **envp)
{
	cmds->cmd1 = ft_split(av[2], ' ');
	cmds->cmd2 = ft_split(av[3], ' ');
	free(cmds->cmd1[0]);
	free(cmds->cmd2[0]);
	cmds->cmd1[0] = check_commands(av[2], envp);
	arranjar_cmd(cmds->cmd1);
	cmds->cmd2[0] = check_commands(av[3], envp);
	arranjar_cmd(cmds->cmd2);
	return (cmds);
}

void	free_cmds(t_cmds *cmds)
{
	int	i;

	i = -1;
	while (cmds->cmd1[++i])
		free(cmds->cmd1[i]);
	i = 0;
	free(cmds->cmd1);
	while (cmds->cmd2[i])
		free(cmds->cmd2[i++]);
	free(cmds->cmd2);
	free(cmds);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	t_cmds	*cmds;

	if (ac != 5)
	{	
		write(1, "wrong number of args\n", 21);
		exit(0);
	}
	cmds = malloc(sizeof(t_cmds) * 1);
	if (!cmds)
		exit(0);
	cmds = cmds_initializer(cmds, av, envp);
	if (pipe(fd) == -1)
		exit(0);
	child_one(cmds, av[1], fd, envp);
	child_two(cmds, av[4], fd, envp);
	close(fd[0]);
	close(fd[1]);
	free_cmds(cmds);
	exit(0);
}
