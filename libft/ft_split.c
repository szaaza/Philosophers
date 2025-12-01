/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazanjan <<sazanjan@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:10:51 by sazanjan          #+#    #+#             */
/*   Updated: 2025/07/22 16:59:42 by sazanjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **arr, int count)
{
	while (count > 0)
	{
		count--;
		free(arr[count]);
	}
	free(arr);
	return (0);
}

static int	count_words_in_string(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*copy_word(char *dst, char const *src, int i, int len)
{
	int	j;

	j = 0;
	while (len > 0)
	{
		dst[j] = src[i - len];
		j++;
		len--;
	}
	dst[j] = '\0';
	return (dst);
}

static char	**fill_words(char const *s, char c, char **result, int word_count)
{
	int	i;
	int	word_i;
	int	len;

	i = 0;
	word_i = 0;
	len = 0;
	while (word_i < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		result[word_i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!result[word_i])
			return (free_array(result, word_i));
		copy_word(result[word_i], s, i, len);
		len = 0;
		word_i++;
	}
	result[word_i] = 0;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	unsigned int	word_count;

	if (!s)
		return (0);
	word_count = count_words_in_string(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (0);
	return (fill_words(s, c, result, word_count));
}
