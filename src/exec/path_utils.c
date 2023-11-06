#include "../../include/minishell.h"

bool	access_check(char *path)
{
	if (access(path, X_OK) == 0)
		return (true);
	return (false);
}

bool	path_check(char *path)
{
	if (path[0] != '/')
		return (false);
	return (true);
}

bool	is_splitable(char *path)
{
	if (ft_strchr(path, ':'))
		return (true);
	return (false);
}

char	*single_path(char *path, char *name)
{
	if (!path_check(path))
		return (NULL);
	ft_strlcat(path, "/", ft_strlen(path) + 2);
	ft_strlcat(path, name, ft_strlen(path) + ft_strlen(name) + 1);
	if (!access_check(path))
		return (NULL);
	return (path);
}

char	*path_join(char *dest, char *src1, char *src2)
{
	char	*dest1;
	char	*dest2;

	dest1 = ft_strjoin(dest, src1);
	if (!dest1)
		return (NULL);
	dest2 = ft_strjoin(dest1, src2);
	if (!dest2)
		return (free(dest1), NULL);
	return (free(dest1), dest2);
}
