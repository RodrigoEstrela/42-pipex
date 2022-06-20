/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ficheirodasbarraspontoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:03:14 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/06/20 15:50:34 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex_bonus.h"

int	is_barra_e_hihfen(char *s1, char *s2)
{
	int	i;

	i = -1;
	while (s1[++i])
	{
		if (s1[i] == '/' && s2 && s2[0] != '-')
			return (1);
		else if (s1[i] == 92 && s1[i + 1] == '\0')
			return (2);
		else if (s1[i] == 92 && s1[i + 1] != 92 && s1[i])
			return (3);
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
