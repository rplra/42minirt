/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:47:46 by rraja-az          #+#    #+#             */
/*   Updated: 2025/07/02 10:06:04 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// reflect(I, N) = 2 * dot(N, I) * N - I
// computes the direction of the reflected vector
t_vec3 reflect(t_vec3 I, t_vec3 N)
{
	return (subtract_vec(mult_vec_scalar(N, 2 * scalar_product(N, I)), I));
}
