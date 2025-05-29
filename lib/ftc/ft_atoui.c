/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:37:58 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/29 15:01:24 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint	ft_atoui(const char *str, bool *valid)
{
	uint	result;

	result = 0;
	if (*str == '\0')
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		*valid = false;
		return (0);
	}
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if (*str != '\0')
		*valid = false;
	else
		*valid = true;
	return (result);
}
