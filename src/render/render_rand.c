/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:15:24 by hsim              #+#    #+#             */
/*   Updated: 2025/07/19 16:28:50 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// brief: random sampling

/*
 * returns a random seed using LCG (linear congruential generator)
 * new_seed = (a * seed + c) mod m
 * 
 * values of a, c, m derived from article below:
 * https://en.wikipedia.org/wiki/Linear_congruential_generator
 * 
 * LCG is a simple pseudo-random number generator
 * updates the seed and returns a new pseudo-random integer
 * used as core random number generator for all random functions
 * 
 * a (multiplier) | c (increment) | m (modulus)
 * 1. old number gets multiplied by fixed (amount a)
 * 2. add a fixed number (constant c)
 * 3. wrap number around if its too big (modulus m) 
 */
static float	lcg(unsigned int *seed)
{
	unsigned int	a;
	unsigned int	c;
	unsigned int	m;

	a = 1664525;
	c = 1013904223;
	m = 0xFFFFFFFF;
	*seed = ((a * (*seed)) + c) % m;
	return (*seed);
}

/*
 * enter a seed number,
 * returns a random float number between 0 to 1, based on lcg algorithm
 * used whenever we need random for jittering, sampling, random directions
 */
float	rand_lcg(unsigned int *seed)
{
	return (lcg(seed) / 4294967295.0);
}

/*
 * returns a random float number within a range, based on lcg algorithm 
 * used for generating rand vals within range; random pos, cols, dirs
 */
float	rand_lcg_range(unsigned int *seed, float min, float max)
{
	return (min + ((max - min) * (lcg(seed) / 4294967295.0)));
}

/* 
 * return a random vector with xyz between 0 to 1 
 * used for generating randoms points / directions
 */
t_vec3	rand_vec(unsigned int *seed)
{
	t_vec3	res;

	res = new_vec3(rand_lcg(seed), rand_lcg(seed), rand_lcg(seed));
	return (res);
}

/* 
 * returns random vec where each component is within range min and max
 * used for generating random points in box / cube in 3d space
 */
t_vec3	rand_vec_range(unsigned int *seed, float min, float max)
{
	t_vec3	res;

	res = new_vec3(rand_lcg_range(seed, min, max), \
rand_lcg_range(seed, min, max), \
rand_lcg_range(seed, min, max));
	return (res);
}

/*
 * brief: randomly picks a point inside a unit sphere, then normalize it to get a random direction with len 1
 * generate & returns a random unit vector (len 1) that lies within the unit sphere
 * random vector points in different direction, uniformly distributed over sphere surface
 * used for random scattering directions (diffuse reflection, monte carlo integration)
 * 
 * (unit_sphere: x sq + y sq + z sq = 1)
 * len_sq <= 1 is to make sure the vector is within sphere (with unit len of 1)
 */
t_vec3	rand_unit_vec(unsigned int *seed)//, t_vector3d surf_norm)
{
	t_vec3	pt;
	float	len_sq;

	while (1)
	{
		pt = rand_vec_range(seed, -1, 1);
		// /*debug*/printf("gen: %f %f %f\n", res.x, res.y, res.z);
		len_sq = (pt.x * pt.x) + \
(pt.y * pt.y) + \
(pt.z * pt.z);
		if (len_sq > 0.0001f && len_sq <= 1)
			return (div_vec_scalar(pt, sqrt(len_sq)));
	}
}

/* returns a random vector that lies on sphere surface */
// t_vector3d	rand_on_hemisphere(unsigned int *seed, t_vector3d surf_norm)
// {
// 	t_vector3d	vec;

// 	vec = new_vector3d(-2, -2, -2);
// 	while (vec.x == -2)
// 		vec = norm_rand_vec(seed);
// 	// /*debug*/printf("rand_on_h:%f %f %f\n", vec.x, vec.y, vec.z);
// 	if (scalar_product(vec, surf_norm) <= 0)
// 		return (multiply_vec_scalar(vec, -1));
// 	// /*debug*/printf("rand_on_h:dot: %f\n", scalar_product(vec, surf_norm));
// 	return (vec);
// }

/* 
 * brief: randomly picks a point inside a unit circle of XY plane
 * generate unit_vectors for lens on camera, ranges -1 to 1 
 * returns a random point inside a unit disk
 * used for simulating camera lens effects (depth of field),
 * ..where ray originate from random points on a disk
 */

t_vec3	rand_unit_disk(unsigned int *seed)
{
	t_vec3	pt;
	float	len_sq;

	while (1)
	{
		pt = rand_vec_range(seed, -1, 1);
		pt.z = 0;
		len_sq = (pt.x * pt.x) + \
(pt.y * pt.y) + \
(pt.z * pt.z);
		if (len_sq < 1)
			return (pt);
	}
}

/*
 * returns random integer between min and max
 * used for picking random obj / colour, index
 */
int	rand_int(unsigned int *seed, int min, int max)
{
	return ((int)rand_lcg_range(seed, min, max + 1));
}
