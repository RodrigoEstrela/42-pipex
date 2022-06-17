/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:47:40 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/06/15 15:48:39 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *ft_str_cmdpath(const char *s1)
{
    char    *str;
    size_t  i;
    size_t  a;
    str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 2));
    if (!str)
        return (NULL);
    str[0] = '/';
    i = 1;
    a = -1;
    while (s1[++a] && s1[a] != ' ')
        str[i++] = s1[a];
    str[i] = 0;
    return (str);
}

char    *check_commands(char *raw_cmd, char **envp)
{
    short int   i;
    char        **paths;
    char        *path;
    char        *cmd;
    char        *tmp;
    i = -1;
    while(ft_memcmp(envp[++i], "PATH=", 5))
        ;
    path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
    paths = ft_split(path, ':');
    cmd = ft_str_cmdpath(raw_cmd);
    int a = -1;
    while (paths[++a])
    {
        tmp = ft_strjoin(paths[a], cmd);
        if (access(tmp, X_OK) == 0)
        {
            int i = -1;
            while(paths[++i])
                free(paths[i]);
            free(paths);
            free(cmd);  
            free(path);
            return(tmp);
        }
        free(tmp);
    }
    exit(0);
}

int     is_barra_e_hihfen(char *s1, char *s2)
{
    int i;
    i = -1;
	while (s1[++i])
    {
        if (s1[i] == '/' && s2 && s2[0] != '-')
            return (1);
        else if (s1[i] == 92 && s1[i + 1] == '\0')
            return (2);
		else if (s1[i] == 92 && s1[i+1] != 92 && s1[i])
		{
//			printf("%c\n%c\n", s1[i], s1[i + 1]);
			return (3);
		}
    }
    return (0);
}

char	*ft_str_barra(const char *s1)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != 92)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_str_after_barra(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	fds;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	fds = 0;
	while (s1[i] && s1[i] != 92)
		i++;
	i++;
	while (s1[i])
	{
		str[fds++] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

void    arranjar_cmd(char **cmd)
{
    int i;
    char    *tmp;
    char    *tmp2;
    int     tc;
	int counter;

	i = 0;
    while (cmd[++i])
    {
        tc = is_barra_e_hihfen(cmd[i], cmd[i + 1]);
		if (tc == 1)
        {
            tmp = cmd[i];
            tmp2 = ft_strjoin(" ", cmd[i  +   1]);
            cmd[i] = ft_strjoin(tmp, tmp2);
            free(tmp);
            free(tmp2);
            free(cmd[i + 1]);
            cmd[i + 1] = NULL;
			arranjar_cmd(cmd);
        }
        else if (tc == 2)
        {
            tmp = cmd[i];
            tmp[ft_strlen(tmp) - 1] = '\0';
            tmp2 = ft_strjoin(" ", cmd[i  +   1]);
            cmd[i] = ft_strjoin(tmp, tmp2);
			counter = 1;
			while (cmd[i + ++counter])
				cmd[i + counter - 1] = cmd[i + counter];
			cmd[i + counter - 1] = NULL;
			arranjar_cmd(cmd);
        }
		else if (tc == 3)
		{
			tmp = ft_str_barra(cmd[i]);
			tmp2 = ft_str_after_barra(cmd[i]);
//			printf("%s\n%s\n", tmp, tmp2);
//			len = ft_strlen(cmd[i]) - ft_strlen(ft_strchr(cmd[i], 92));
//			tmp[len] = '\0';
//			tmp2 = ft_substr(cmd[i], len + 1, ft_strlen(cmd[i]));
			cmd[i] = ft_strjoin(tmp, tmp2);
//			printf("%s\n", cmd[i]);
			cmd[i + 1] = NULL;
			arranjar_cmd(cmd);
		}
    }
//	for (int j=1;cmd[j];j++)
//		printf("%s\n", cmd[j]);
}
