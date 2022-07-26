/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:31:50 by fde-albe          #+#    #+#             */
/*   Updated: 2022/07/25 11:55:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_cmds
{
	char	**cmd1;
	char	**cmd2;
}			t_cmds;

char	*check_commands(char *raw_cmd, char **envp);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *str);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strdup(const char *s1);

char	*ft_strjoin(char const *s1,	char const *s2);

int		is_barra_e_hihfen(char *s1, char *s2);

char	*ft_str_barra(const char *s1);

char	*ft_str_after_barra(const char *s1);

void	arranjar_cmd(char **cmd);

char	*ft_strchr(const char *s, int c);

void	child_one(t_cmds *cmds, char *str, int fd[2], char **envp);

void	child_two(t_cmds *cmds, char *str, int fd[2], char **envp);

void	*ft_calloc(size_t count, size_t size);

#endif
