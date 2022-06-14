#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = -1;
	while (str[++i] != '\0')
		;
	return (i);
}
