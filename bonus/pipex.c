/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:13 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/21 15:59:42 by rdas-nev         ###   ########.fr       */
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

void	do_cmds_things(t_cmds *cmds, char **envp, int *fd)
{
	if (pipe(fd) == -1)
		exit(0);
	child_one(cmds, fd, envp);
	free_cmds(cmds);
}

void	do_the_things(t_cmds *cmds, t_chars *strs, int *i_fd1_fd2, int *fd)
{
	while (++i_fd1_fd2[0] < strs->ac - 2)
	{
		cmds = cmds_initializer(cmds, strs->av, strs->env, i_fd1_fd2[0]);
		do_cmds_things(cmds, strs->env, fd);
	}
	cmds = cmds_initializer(cmds, strs->av, strs->env, strs->ac - 2);
	dup2(i_fd1_fd2[2], 1);
	execve(cmds->cmd1[0], cmds->cmd1, strs->env);
	free(cmds);
	free(strs);
}

int	main(int ac, char **av, char **envp)
{
	t_cmds	*cmds;
	t_chars	*strs;
	int		fd[2];
	int		*i_fd1_fd2;

	i_fd1_fd2 = (int [3]){0, 0, 0};
	cmds = malloc(sizeof(t_cmds) * 1);
	strs = malloc(sizeof(t_chars) * 1);
	strs->ac = ac;
	strs->av = av;
	strs->env = envp;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		i_fd1_fd2[0] = 2;
		i_fd1_fd2[2] = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 777);
		ft_here_doc(av[2]);
	}
	else
	{
		i_fd1_fd2[0] = 1;
		i_fd1_fd2[1] = open(av[1], O_RDONLY, 777);
		i_fd1_fd2[2] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 777);
	}
	do_the_things(cmds, strs, i_fd1_fd2, fd);
	exit(0);
}
