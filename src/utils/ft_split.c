/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulmie <bboulmie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:46:24 by bboulmie          #+#    #+#             */
/*   Updated: 2025/03/02 16:05:32 by bboulmie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			count = count + 1;
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
	{
		len = len + 1;
	}
	return (len);
}

static char	*copy_word(char const *s, int len)
{
	char	*word;
	int		j;

	word = (char *)malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = s[j];
		j = j + 1;
	}
	word[j] = '\0';
	return (word);
}

static char	**do_split(char const *s, char c, int words)
{
	char	**arr;
	int		i;
	int		len;

	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			len = word_len(s, c);
			arr[i] = copy_word(s, len);
			if (arr[i] == NULL)
				return (NULL);
			i = i + 1;
			s = s + len;
		}
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int	words;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	return (do_split(s, c, words));
}
