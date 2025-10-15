/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:15:24 by hsim              #+#    #+#             */
/*   Updated: 2025/08/17 15:00:15 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	return (lcg(seed) / 4294967296.0);
}

/*
 * returns a random float number within a range, based on lcg algorithm 
 * used for generating rand vals within range; random pos, cols, dirs
 */
float	rand_lcg_range(unsigned int *seed, float min, float max)
{
	return (min + ((max - min) * (lcg(seed) / 4294967296.0)));
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
