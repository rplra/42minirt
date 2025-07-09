/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:04:45 by hsim              #+#    #+#             */
/*   Updated: 2025/07/09 20:50:04 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* mallocs a sph_ptr */
int	malloc_sph_ptr(t_sphere **dest, int num)
{
	if (num <= 0)
		return (0);
	*dest = (t_sphere *)malloc(sizeof(t_sphere) * num);
	if (!(*dest))
	{
		ft_perror("🚨 malloc_sph_ptr failed!", 0, 0);
		return (0);
	}
	return (1);
}

/* mallocs a obj_ptr up to num count */
int	malloc_obj_ptr(t_obj **dest, int num)
{
	if (num <= 0)
		return (0);
	*dest = (t_obj *)malloc(sizeof(t_obj) * num);
	if (!(*dest))
	{
		ft_perror("🚨 malloc_obj_ptr failed!", 0, 0);
		return (0);
	}
	return (1);
}
