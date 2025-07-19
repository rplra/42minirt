/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:21:10 by hsim              #+#    #+#             */
/*   Updated: 2025/07/14 21:43:43 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in get_viewport_coords
 * get value of viewport_uv and save to
 * t_vector3d *viewport_u & *viewport_v
 */
// defocus disk (disk is the cam's lens surface - flat circle in 3d world); blur / bokeh
// camera = where rays originate from and how they were constructed
// viewport = screen = where rays are aimed at, pixel by pixel
// brief : calc how big camera's screen is in 3d world and the direction its looking at (cam w)
// 1. calculates viewport size in world units
// 2. computes cam's local coords frame (basis vector)
// 3. scale the cam's axis to viewport size (entire width and ht of screen) & the defoc disk
static void	get_viewport_uv(t_rt *vars, t_vec3 *viewport_u, \
t_vec3 *viewport_v, t_vec3 *cam_w)
{
	float		h;				// viewport half ht
	float		defoc_radius;	// depth of field
	float		viewport[2];	// width, height
	t_vec3		cam[2];			// cam[X] = u (right), cam[Y] = v (up)

	// compute viewport w/h in world units
	h = tan(vars->camera.vfov / 2) * vars->camera.focus_dist;
	// get full width, scale ht based on width
	viewport[H] = 2 * h;
	viewport[W] = (viewport[H] * WIN_WIDTH) / WIN_HEIGHT;
	// for hfov method, push changes later
	// viewport[W] = 2 * h;
	// viewport[H] = (viewport[W] * WIN_HEIGHT) / WIN_WIDTH;

	// /*debug*/printf("h:%f, viewport: %f %f\n", h, viewport[X], viewport[Y]);
	// compute forward direction (camera is looking away from - backwards)
	*cam_w = unit_vec3(subtract_vec(vars->camera.pos, vars->camera.lookat));
	/*debug*/printf("cam_w: %f %f %f\n", (*cam_w).x, (*cam_w).y, (*cam_w).z);

	// compute right vector (horizontal)
	cam[X] = unit_vec3(cross_product(vars->camera.vup, *cam_w));
	/*debug*/printf("cam[X]: %f %f %f\n", cam[X].x, cam[X].y, cam[X].z);
	
	// compute up vector (vertical)
	cam[Y] = mult_vec_scalar(cross_product(*cam_w, cam[X]), -1); // -v
	/*debug*/printf("cam[Y]: %f %f %f\n", cam[Y].x, cam[Y].y, cam[Y].z);

	// scale camera's right and up axis to match viewport size
	*viewport_u = mult_vec_scalar(cam[X], viewport[W]);
	*viewport_v = mult_vec_scalar(cam[Y], viewport[H]);
	// /*debug*/printf("cam_w: %f %f %f\n", (*cam_w).x, (*cam_w).y, (*cam_w).z);
	// /*debug*/printf("cam_u: %f %f %f\n", cam[X].x, cam[X].y, cam[X].z);
	// /*debug*/printf("cam_v: %f %f %f\n", cam[Y].x, cam[Y].y, cam[Y].z);

	// compute defocus disk vectors, used for depth of field blur (lens simulation)
	// calc how wide the defoc circle is, based on defoc angle
	// wider defocus angle = larger aperture = more blur.
	defoc_radius = vars->camera.focus_dist * tan(vars->camera.defoc_ang / 2);
	
	// set up the size of the defoc disk in 3d space
	vars->camera.defoc_disk[X] = mult_vec_scalar(cam[X], defoc_radius); // right vector
	vars->camera.defoc_disk[Y] = mult_vec_scalar(cam[Y], defoc_radius); // up vector

	// *viewport_u = new_vector3d(viewport[X], 0, 0);
	// *viewport_v = new_vector3d(0, -viewport[Y], 0);
	/*debug*/printf("vp_uv in: %f %f %f, %f %f %f\n", (*viewport_u).x, (*viewport_u).y, (*viewport_u).z, (*viewport_v).x, (*viewport_v).y, (*viewport_v).z);
}

/*
 * child function in my_render_image
 * get starting values of viewport (viewport top_left)
 * & center of top_left_pixel (viewport_00_loc)
 */
// vp_00_loc: Output → location of pixel (0,0) in world space
// vp_top_left: Output → location of top-left corner of the screen (viewport)
// vp_d[X] and vp_d[Y]: Output → how far to move one pixel right/down in world units
// gets the coords to start drawing (center of top left of cam view)
// and how to start drawing from that point
// why we need this? we shoot rays through the center of the pixel for better accuracy
static void	get_viewport_coords(t_rt *vars, t_vec3 *vp_00_loc, \
t_vec3 *vp_top_left, t_vec3 vp_d[2])
{
	t_vec3	vp[2];
	t_vec3	cam_w;

	// get the shape and orientation of the screen in 3d space (previous func)
	get_viewport_uv(vars, &vp[X], &vp[Y], &cam_w);

	// computes how much distance (in world space) each pixel takes along the x, y of viewport
	// vp_d[X] = 4 (units in world) / 800 = 0.005 units → every step right
	vp_d[X] = div_vec_scalar(vp[X], WIN_WIDTH); 	// move one pixel right
	vp_d[Y] = div_vec_scalar(vp[Y], WIN_HEIGHT); 	// move one pixel down

	// move the camera position forward to get to the center of the screen
	*vp_top_left = subtract_vec(vars->camera.pos, \
mult_vec_scalar(cam_w, vars->camera.focus_dist));
	// move halfway left > move halfway up to get to the top left pixel
	*vp_top_left = subtract_vec(*vp_top_left, div_vec_scalar(vp[X], 2));
	*vp_top_left = subtract_vec(*vp_top_left, div_vec_scalar(vp[Y], 2));

	// set the start to the center of the top left pixel
	//pixel center
	*vp_00_loc = add_vec(*vp_top_left, \
div_vec_scalar(add_vec(vp_d[X], vp_d[Y]), 2));

	// /*debug*/debug_print_vec("viewport_x:", vp[X]);
	// /*debug*/debug_print_vec("viewport_y:", vp[Y]);
	// /*debug*/debug_print_vec("viewport_dx:", vp_d[X]);
	// /*debug*/debug_print_vec("viewport_dy:", vp_d[Y]);
	// /*debug*/debug_print_vec("00_loc:", *vp_00_loc);
}

/*
 * child function in my_render_image
 * viewport_00 = center of pixel 00 in viewport
 * viewport_d = dydx or dudv of viewport
 */
// viewport_00: the 3D world position of the center of pixel (0, 0)
// viewport_d[0] (or viewport_d[X]): how far to move right by 1 pixel
// viewport_d[1] (or viewport_d[Y]): how far to move down by 1 pixel
// interate through pixel, calculate 3d target point for each pixel, calc the col and draw it
static void	ft_draw(t_rt vars, t_vec3 viewport_00, t_vec3 viewport_d[2])
{
	int		x;
	int		y;
	int		color;
	t_vec3	target;		// starting point

	x = -1;
	y = -1;
	target = viewport_00;

	// target.z = viewport_00.z + (x * viewport_d[X].z) + (y * viewport_d[Y].z);
	// loop through every row
	while (++y < WIN_HEIGHT)
	{
		x = 0;
		// we move from top left then add dx.y (how much y pos change when moving right (x), 
		//							  add dy.y (how much y pos change when moving down (y))
		// viewport_00.y = 10 (starting height). 
		// dx.y = 0.01 (each step right raises the y slightly).
		// dy.y = -0.02 (each step down lowers the y).
		// dx.y and dy.y accounts for perspective of camera tilt
		target.y = viewport_00.y + (x * viewport_d[X].y) + (y * viewport_d[Y].y);
		// target.y = viewport_00.y + (y * viewport_d[Y].y);

		// iterate through column, same concept as above
		while (++x < WIN_WIDTH)
		{
			// target.x = viewport_00.x + (x * viewport_d[X].x); //short
			target.x = viewport_00.x + (x * viewport_d[X].x) + (y * viewport_d[Y].x);
// x = viewport_00.x + (x * dx.x)  |->  + (offset.x * dx.x)
//                   + (y * dy.x)  |->  + (offset.y * dy.x)

			// returns the color of the pixel at that 3d point
			color = sample_pixels(vars, target, viewport_d, x);
			// draw pixel on the screen
			my_mlx_pixel_put(vars, x, y, color);
		}
	}
}

/*
 * vp_00 = center of pixel 00 in viewport
 * vp_d = dydx or dudv of viewport
 */

// vp_d[2];         // Pixel step sizes (dx and dy)
// vp_00_loc;       // World position of the center of pixel (0, 0)
// vp_top_left;     // top left corner of screen in world space

// render the whole scene / img
// calc start, draw every pixel and show result
void	my_render_image(t_rt *vars)
{
	t_vec3	vp_d[2];
	t_vec3	vp_00_loc;
	t_vec3	vp_top_left;

	//clear before draw
	clear_image(*vars, WIN_WIDTH, WIN_HEIGHT, 0x000000);
	// display the black img
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, \
vars->img.img, 0, 0);
	// get the pos to start drawing
	get_viewport_coords(vars, &vp_00_loc, &vp_top_left, vp_d);
	// loops through pixel, shoot, compute col > fill to img buffer
	ft_draw(*vars, vp_00_loc, vp_d);
	//push draw result to window
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, \
vars->img.img, 0, 0);
}
