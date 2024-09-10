/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:51:21 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 13:11:29 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = b;
	while (len--)
	{
		*tmp_ptr = (unsigned char) c;
		tmp_ptr++;
	}
	return (b);
}
/* As the return value is the first parameter of the function,
 * the use of a temporary variable is necessary (*tmp_ptr) to  write len bytes
 * of value c (converted to an unsigned char) to the string b. */
