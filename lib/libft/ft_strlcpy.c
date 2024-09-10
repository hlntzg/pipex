/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:54:47 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 10:16:08 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = 0;
	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	while (*(src + src_len) && (dstsize - 1))
	{
		*dst = *(src + src_len);
		dst++;
		src_len++;
		dstsize--;
	}
	*dst = '\0';
	while (*(src + src_len))
		src_len++;
	return (src_len);
}
/* The function returns the len of src, even if the copy has been truncate.
 * Strlcpy copies (dstsize - 1 lenght of) src to dst, NUL-terminating the
 * string if dstsize is not 0. */
