/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:13 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/27 19:09:53 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int		*i_fd1_fd2;

	i_fd1_fd2 = (int [3]){0, 0, 0};
	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i_fd1_fd2[0] = 3;
			i_fd1_fd2[2] = open_file(av[ac - 1], 0);
			ft_here_doc(av[2], ac);
		}
		else
		{
			i_fd1_fd2[0] = 2;
			i_fd1_fd2[1] = open_file(av[1], 2);
			i_fd1_fd2[2] = open_file(av[ac - 1], 1);
			dup2(i_fd1_fd2[1], STDIN_FILENO);
		}
		while (i_fd1_fd2[0] < ac -2)
			child_one(av[i_fd1_fd2[0]++], envp);
		dup2(i_fd1_fd2[2], STDOUT_FILENO);
		execute(av[ac - 2], envp);
	}
}
