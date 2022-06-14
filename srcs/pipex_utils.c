#include "pipex.h"

char	*ft_str_cmdpath(const char *s1)
{
	char	*str;
	size_t	i;
	size_t	a;

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

char	*check_commands(char *raw_cmd, char **envp)
{
	short int	i;
	char		**paths;
	char		*path;
	char		*cmd;
	char		*tmp;
	i = -1;
	while(ft_memcmp(envp[++i], "PATH=", 5))
		;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	paths = ft_split(path, ':');
	cmd = ft_str_cmdpath(raw_cmd);
	int	a = -1;
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

int		is_barra_e_hihfen(char *s1, char *s2)
{
	int i;

	i = -1;
	while (s1[++i])
	{
		if (s1[i] == '/' && s2[0] != '-')
			return (1);
		else if (s1[i] == 92)
			return (2);
	}
	return (0);
}

void	arranjar_cmd(char **cmd)
{
	int	i;
	char	*tmp;
	char	*tmp2;
	int		tem_coisas;

	i = 0;
	while (cmd[++i])
	{
		tem_coisas = is_barra_e_hihfen(cmd[i], cmd[i + 1]);
		if (tem_coisas == 1)
		{
			tmp = cmd[i];
			tmp2 = ft_strjoin(" ", cmd[i  +   1]);
			cmd[i] = ft_strjoin(tmp, tmp2);
			free(tmp);
			free(tmp2);
			free(cmd[i + 1]);
			cmd[i + 1] = NULL;
		}
		else if (tem_coisas == 2)
		{
			tmp = cmd[i];
			tmp[ft_strlen(tmp) - 1] = '\0';
			tmp2 = ft_strjoin(" ", cmd[i  +   1]);
			cmd[i] = ft_strjoin(tmp, tmp2);
			cmd[i + 1] = NULL;
		}
	}
}
