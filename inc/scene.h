/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:32:00 by rraja-az          #+#    #+#             */
/*   Updated: 2025/05/22 17:44:54 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct	s_vector
{
	double			x;
	double			y;
	double			z;
}				t_vector;


#endif

| Struct Name  | Purpose                                |
| ------------ | -------------------------------------- |
| `t_scene`    | Root struct holding all scene elements |
| `t_camera`   | Camera info (position, direction, FOV) |
| `t_light`    | Point light info                       |
| `t_ambient`  | Global ambient light                   |
| `t_object`   | Generic object wrapper (type, union)   |
| `t_sphere`   | Sphere geometry                        |
| `t_plane`    | Plane geometry                         |
| `t_cylinder` | Cylinder geometry                      |
| `t_color`    | RGB color (as ints or floats)          |
| `t_vec3`     | 3D vector/point                        |
