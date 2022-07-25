/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arranjar_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:24:50 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/06/20 16:46:41 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

char	**barra_um(char	**cmd, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = cmd[i];
	tmp2 = ft_strjoin(" ", cmd[i + 1]);
	cmd[i] = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	free(cmd[i + 1]);
	cmd[i + 1] = NULL;
	return (cmd);
}

char	**barra_two(char **cmd, int i)
{
	int		counter;
	char	*tmp;
	char	*tmp2;

	tmp = cmd[i];
	tmp[ft_strlen(tmp) - 1] = '\0';
	tmp2 = ft_strjoin(" ", cmd[i + 1]);
	cmd[i] = ft_strjoin(tmp, tmp2);
	counter = 1;
	while (cmd[i + ++counter])
		cmd[i + counter - 1] = cmd[i + counter];
	free(cmd[i + counter - 1]);
	cmd[i + counter - 1] = NULL;
	free(tmp2);
	free(tmp);
	return (cmd);
}

char	**barra_three(char **cmd, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_str_barra(cmd[i]);
	tmp2 = ft_str_after_barra(cmd[i]);
	cmd[i] = ft_strjoin(tmp, tmp2);
	cmd[i + 1] = NULL;
	free(tmp);
	free(tmp2);
	return (cmd);
}

void	arranjar_cmd(char **cmd)
{
	int		i;
	int		tc;

	i = 0;
	while (cmd[++i])
	{
		tc = is_barra_e_hihfen(cmd[i], cmd[i + 1]);
		if (tc == 1)
		{
			cmd = barra_um(cmd, i);
			arranjar_cmd(cmd);
		}
		else if (tc == 2)
		{
			cmd = barra_two(cmd, i);
			arranjar_cmd(cmd);
		}
		else if (tc == 3)
		{
			cmd = barra_three(cmd, i);
			arranjar_cmd(cmd);
		}
	}
}
