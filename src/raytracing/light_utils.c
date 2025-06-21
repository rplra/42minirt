/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:47:46 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/21 18:48:25 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// reflect(I, N) = 2 * dot(N, I) * N - I
t_vector reflect(t_vector I, t_vector N)
{
	return vector_subtract(vector_scale(N, 2 * dot_product(N, I)), I);
}
