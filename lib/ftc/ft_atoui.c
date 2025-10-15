/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:37:58 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/23 22:01:11 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_uint	ft_atoui(const char *str, bool *valid)
{
	t_uint	result;

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
