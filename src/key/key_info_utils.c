/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:32:07 by rraja-az          #+#    #+#             */
/*   Updated: 2025/10/15 16:38:54 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	*ft_ftoa(float f)
{
	char	*int_part;
	char	*frac_part;
	char	*temp;
	char	*result;
	int		frac;

	int_part = ft_itoa((int)f);
	frac = (int)((f - (int)f) * 10);
	if (frac < 0)
		frac = -frac;
	frac_part = ft_itoa(frac);
	temp = ft_strjoin(int_part, ".");
	result = ft_strjoin(temp, frac_part);
	free(int_part);
	free(frac_part);
	free(temp);
	return (result);
}

char	*get_info_str(t_vec3 pos)
{
	char	*x;
	char	*y;
	char	*z;
	char	*temp;
	char	*res;

	x = ft_ftoa(pos.x);
	y = ft_ftoa(pos.y);
	z = ft_ftoa(pos.z);
	temp = ft_strjoin(x, ",");
	free(x);
	x = ft_strjoin(temp, y);
	free(temp);
	free(y);
	temp = ft_strjoin(x, ",");
	free(x);
	res = ft_strjoin(temp, z);
	free(temp);
	free(z);
	return (res);
}

static void	*get_char_image(t_rt *rt, char c)
{
	if (c >= '0' && c <= '9')
		return (rt->label.digits[c - '0'].img);
	else if (c == '.')
		return (rt->info.dot.img);
	else if (c == '-')
		return (rt->info.minus.img);
	else if (c == ',')
		return (rt->info.comma.img);
	return (NULL);
}

void	display_digit_xpm(t_rt *rt, char *str, int x, int y)
{
	void	*img;
	int		offset;
	int		i;

	offset = 0;
	i = -1;
	while (str[++i])
	{
		img = get_char_image(rt, str[i]);
		if (img)
		{
			mlx_put_image_to_window(rt->mlx, rt->mlx_win, img, x + offset, y);
			offset += OFFSET;
			if (str[i] == ',')
				offset += SPACE_OFFSET;
			if (str[i] == '.')
				offset -= DOT_OFFSET;
		}
	}
}
