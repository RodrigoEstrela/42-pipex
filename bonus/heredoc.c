/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:13 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/20 14:53:12 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

void	ft_here_doc(char *limiter)
{
	int		fd[2];
	int		reader;
	char	*line;

	if (pipe(fd) == -1)
		exit(0);
	reader = fork();
	if (reader == 0)
	{	
		close(fd[0]);
		line = get_next_line(0);
		while (ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			write(fd[1], line, ft_strlen(line));
			free(line);
			line = get_next_line(0);
		}
		free(line);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}
