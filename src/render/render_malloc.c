/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/10 19:17:17 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

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
