
char	*ft_strchr(const char *s, int c)
{
	char	temp;

	temp = c;
	while (*s != temp)
		if (*s++ == '\0')
			return (0);
	return ((char *)s);
}
