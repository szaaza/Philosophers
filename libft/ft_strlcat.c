/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sazanjan <<sazanjan@student.42heilbronn    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:42:19 by szanjani          #+#    #+#             */
/*   Updated: 2025/07/22 16:59:55 by sazanjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_length;
	size_t	src_len;
	size_t	space;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	dst_length = ft_strlen(dst);
	if (dst_length >= size)
		return (size + src_len);
	space = size - dst_length - 1;
	if (space == 0)
		return (src_len + size - 1);
	while (space != 0 && src[i] != '\0')
	{
		dst[dst_length + i] = src[i];
		i++;
		space--;
	}
	dst[dst_length + i] = '\0';
	return (dst_length + src_len);
}
