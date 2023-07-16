#include "parse.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	char *p;
	size_t index;
	unsigned int _strlen;

	if (!s)
		return (NULL);
	_strlen = strlen(s);
	if (len + start > _strlen)
		len += _strlen - len - start;
	if (start > _strlen)
		len = 0;
	p = (char *)malloc((sizeof(char) * (1 + len)));
	if (!p)
		return (NULL);
	p[len] = '\0';
	index = 0;
	while (index < len)
	{
		p[index] = s[start + index];
		index++;
	}
	return (p);
}

static int count_strlen(char *str, char c, int str_in)
{
	int len;

	len = 0;
	while (str[str_in] != '\0')
	{
		if (str[str_in] == c)
			return (len);
		len++;
		str_in++;
	}
	return (len);
}

static char *ft_strndup(char *str, size_t str_len)
{
	char *newsrc;
	size_t i;

	i = 0;
	newsrc = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!newsrc)
		return (0);
	while (i < str_len)
	{
		newsrc[i] = str[i];
		i++;
	}
	newsrc[i] = '\0';
	return (newsrc);
}

static int get_count(char const *s, char c)
{
	int count;
	int len;
	int flag;

	count = 0;
	flag = 0;
	len = strlen(s);
	while (len--)
	{
		if (s[len] == c)
			flag = 0;
		else if (s[len] != c && !flag)
		{
			flag = 1;
			count++;
		}
	}
	return (count);
}

static char **null_free(char **res)
{
	size_t j;

	j = 0;
	while (res[j])
	{
		free(res[j]);
		j++;
	}
	free(res);
	return (NULL);
}

char **ft_split(char const *s, char c)
{
	char **result;
	int str_in;
	int res_in;
	int flag;
	int count;

	count = get_count((char *)s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (0);
	result[count] = 0;
	str_in = 0;
	res_in = 0;
	while (res_in < count && s[str_in])
	{
		while (s[str_in] == c)
			str_in++;
		flag = str_in;
		while (s[str_in] != c && s[str_in])
			str_in++;
		result[res_in] = ft_strndup((char *)s + flag, str_in - flag);
		if (result[res_in++] == 0)
			return (null_free(result));
	}
	return (result);
}

char *ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (unsigned char)c)
		return ((char *)str);
	return (NULL);
}

int ft_count_char(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
		if (str[i++] == c)
			count++;
	return (count);
}

void *ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i)
		{
			((unsigned char *)dst)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	return (dst);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	char *p;
	int len_s1;
	int len_s2;

	len_s1 = strlen(s1);
	len_s2 = strlen(s2);
	p = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!p)
		return (0);
	memcpy(p, s1, len_s1);
	memcpy(p + len_s1, s2, len_s2);
	p[len_s1 + len_s2] = '\0';
	return (p);
}
