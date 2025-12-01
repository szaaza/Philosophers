/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazanjan <<sazanjan@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:46:31 by sazanjan          #+#    #+#             */
/*   Updated: 2025/07/22 17:00:29 by sazanjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	trim_len;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_check_set(*s1, set))
		s1++;
	trim_len = ft_strlen(s1);
	while (trim_len && ft_check_set(s1[trim_len - 1], set))
		trim_len--;
	trimmed_str = (char *)malloc(sizeof(char) * (trim_len + 1));
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, s1, trim_len + 1);
	return (trimmed_str);
}

/*
int main ()
{
	char const	s1[]  = "----  hi!!---  ";
	char const 	set[] = "- !";
	
	printf("%s",ft_strtrim(s1,set));
	return(0);
}
*/