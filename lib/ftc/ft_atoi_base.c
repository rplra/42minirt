/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:07:07 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/22 08:57:33 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	base_index(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

int	ft_atoi_base(const char *s, const char *base)
{
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s++ == '-')
			sign *= -1;
	}
	while (base_index(*s, base) != -1 || base_index(ft_toupper(*s), base) != -1)
	{
		if (base_index(*s, base) != -1)
			nbr = nbr * ft_strlen(base) + base_index(*s++, base);
		else
			nbr = nbr * ft_strlen(base) + base_index(ft_toupper(*s++), base);
	}
	return (nbr * sign);
}
