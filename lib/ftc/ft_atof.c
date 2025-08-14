/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:31 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/14 16:06:26 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
#include "libft.h"

static void	handle_whitespace_and_sign(const char **str, int *sign)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
	if (**str == '-')
		*sign *= -1;
	if (**str == '-' || **str == '+')
		(*str)++;
}

static void	process_digits(const char **str, t_atof *atof)
{
	while (ft_isdigit(**str))
	{
		if (!atof->has_dot)
			atof->val = (atof->val * 10) + (**str - '0');
		else
		{
			atof->frac += (**str - '0') / (double)atof->divisor;
			atof->divisor *= 10;
		}
		atof->has_digit = true;
		(*str)++;
	}
}

static bool	process_dot(const char **str, t_atof *atof)
{
	while (**str)
	{
		if (**str == '.')
		{
			if (atof->has_dot)
				return (false);
			atof->has_dot = true;
			(*str)++;
		}
		else if (ft_isdigit(**str))
			process_digits(str, atof);
		else
			break ;
	}
	return (true);
}

float	ft_atof(const char *str, bool *valid)
{
	t_atof	atof;
	int		sign;

	sign = 1;
	atof.val = 0.0;
	atof.frac = 0.0;
	atof.divisor = 10;
	atof.has_dot = false;
	atof.has_digit = false;
	handle_whitespace_and_sign(&str, &sign);
	if (!process_dot(&str, &atof) || !atof.has_digit || *str != '\0')
	{
		*valid = false;
		return (0.0);
	}
	*valid = true;
	return ((atof.val + atof.frac) * sign);
}

/*
int	main(void)
{
	bool	valid;
	int		count;
	float	my_val;
	float	sys_val;

	const char *tests[] = {
		"123.45", "-0.5", ".7", "1.", "1.2.3", "abc", "a.12", "1.2b"
	};
	count = sizeof(tests) / sizeof(tests[0]);
	for (int i = 0; i < count; i++)
	{
		my_val = ft_atof(tests[i], &valid);
		sys_val = atof(tests[i]);
		printf("input: '%s'\n", tests[i]);
		if (valid)
			printf("  ft_atof  => %f\n", my_val);
		else
			printf("  ft_atof  => Invalid input\n");
		printf("  std_atof => %f\n", sys_val);
		printf("\n");
	}
	return (0);
}
*/

// cc -Wall -Wextra -Werror ft_atof.c -I../inc -L.. -lft

/*
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
*/

/* int	main(void)
{
	float	val;
	float	f;
	char	*str;

	str = "1.45";
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
