/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:31 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/28 08:17:18 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
#include "libft.h"

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (!*str)
		return (0);
	while (**str == 32 || (**str >= 9 && **str <= 13))
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign *= -1;
		(*str)++;
	}
	return (sign);
}

float	ft_atof(const char *str)
{
	float	result;
	float	num;
	float	divisor;
	int		sign;

	sign = parse_sign(&str);
	result = 0.0f;
	num = 0.0f;
	divisor = 10.0f;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0f + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			num += (*str - '0') / divisor;
			divisor *= 10.0f;
			str++;
		}
	}
	return ((result + num) * sign);
}


/* int	main(void)
{
	float	val;
	float	f;
	
	char *str = "1.45";
	val = ft_atof(str);
	f = atof(str);
	printf("Before atof		: %s \n", str);
	printf("After ft_atof	: %f \n", val);
	printf("After atof		: %f \n", f);

	// OUTPUT
	// Before atof		: 1.45 
	// After ft_atof	: 1.450000 
	// After atof		: 1.450000
}
*/
