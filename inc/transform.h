/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:06:48 by hsim              #+#    #+#             */
/*   Updated: 2025/07/28 08:33:21 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "../lib/quaternion/ft_vector.h"

typedef struct s_transform
{
	t_vec3		translate;
	t_vec3		scale;
	t_vec3		rotate;
}				t_transform;

#endif