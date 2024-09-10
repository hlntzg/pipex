/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:16:28 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 14:14:08 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp_src;
	char	*tmp_dst;

	tmp_src = (char *) src;
	tmp_dst = (char *) dst;
	if (!dst && !src)
		return (NULL);
	if (tmp_dst > tmp_src)
		while (len--)
			tmp_dst[len] = tmp_src[len];
	else
		while (len--)
			*tmp_dst++ = *tmp_src++;
	return (dst);
}
/* The copy of len bytes from src to dst is done in a non-destructive manner,
 * so both string can overlap in memory and the function does not overwrite
 * part of or the whole string while making the copy. */
