/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:18:02 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 09:55:48 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = s;
	while (n--)
	{
		*tmp_ptr = 0;
		tmp_ptr++;
	}
}
/* If n > 0, the function writes zeroed bytes to the string s. It works similar
 * as the memset function (without specitying the character to be written). */
