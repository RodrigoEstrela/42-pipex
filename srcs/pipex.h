/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:31:50 by fde-albe          #+#    #+#             */
/*   Updated: 2022/06/14 15:05:41 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

char  *check_commands(char *raw_cmd, char **envp);
int 	ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *s, char c);
size_t  ft_strlen(const char *str);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1,	char const *s2);
void	arranjar_cmd(char **cmd);

#endif
