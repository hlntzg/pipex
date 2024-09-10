/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutzig <hutzig@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:26:29 by hutzig            #+#    #+#             */
/*   Updated: 2024/05/06 13:07:04 by hutzig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_n(int long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			len;
	int long	nb;

	nb = n;
	len = len_n(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[0] = '0';
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	i = len;
	while (nb != 0 && i-- > 0)
	{
		str[i] = (nb % 10) + 48;
		nb = nb / 10;
	}
	str[len] = '\0';
	return (str);
}
/* Itoa function convertes a number into a string after allocating enough
 * memory for the string (ensuring the NUL-terminating chacacter in the end).
 * It's necessary to convert the n parameter to a long so it's to work with
 * INT_MIN and INT_MAX the same way as all the other numbers. */
