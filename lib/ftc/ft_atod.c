/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:26:13 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/29 10:40:20 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static void	handle_whitespace_and_sign(const char **str, int *sign)
{
	while (**str == ' ' || (**str >= '\t' && **str <= '\r'))
		(*str)++;
	if (**str == '-')
		*sign *= -1;
	if (**str == '-' || **str == '+')
		(*str)++;
}

static void	process_digits(const char **str, t_atod *atod)
{
	while (ft_isdigit(**str))
	{
		if (!atod->has_dot)
			atod->val = (atod->val * 10) + (**str - '0');
		else
		{
			atod->frac += (**str - '0') /(double)atod->divisor;
			atod->divisor *= 10;
		}
		atod->has_digit = true;
		(*str)++;
	}
}

static bool	process_dot(const char **str, t_atod *atod)
{
	while (**str)
	{
		if (**str == '.')
		{
			if (atod->has_dot)
				return (false);
			atod->has_dot = true;
			(*str)++;
		}
		else if (ft_isdigit(**str))
			process_digits(str, atod);
		else
			break;
	}
	return (true);
}

double	ft_atod(const char *str, bool *valid)
{
	t_atod	atod;
	int		sign;

	sign = 1;
	atod.val = 0.0;
	atod.frac = 0.0;
	atod.divisor = 10;
	atod.has_dot = false;
	atod.has_digit = false;
	handle_whitespace_and_sign(&str, &sign);
	if (!process_dot(&str, &atod) || !atod.has_digit || *str != '\0')
	{
		*valid = false;
		return 0.0;
	}
	*valid = true;
	return ((atod.val + atod.frac) * sign);
}

/* int main(void)
{
    bool valid;
    const char *tests[] = {"123.45", "-0.5", ".7", "1.", "1.2.3", "abc", "a.12", "1.2b"};
    int count = sizeof(tests) / sizeof(tests[0]);
    int i;
    for (i = 0; i < count; i++)
    {
        double val = ft_atod(tests[i], &valid);
        printf("input: '%s' -> ", tests[i]);
        if (valid)
            printf("after atod: %f\n", val);
        else
            printf("Invalid input for atod\n");
    }
    return 0;
} */
