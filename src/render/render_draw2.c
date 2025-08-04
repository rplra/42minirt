/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:21:10 by hsim              #+#    #+#             */
/*   Updated: 2025/08/03 17:00:04 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// mlx

/*
 * child function in get_viewport_coords
 * get value of viewport_uv and save to
 * t_vector3d *viewport_u & *viewport_v
 * 
 * brief : calc how big camera's screen is in 3d world and the direction its looking at (cam w)
 * defocus disk (disk is the cam's lens surface - flat circle in 3d world); blur / bokeh
 * camera = where rays originate from and how they were constructed
 * viewport = screen = where rays are aimed at, pixel by pixel
 * 
 * 1. calculates viewport size in world units
 * 2. computes cam's local coords frame (basis vector)
 * 3. scale the cam's axis to viewport size (entire width and ht of screen) & the defoc disk
 */
static void	get_viewport_uv(t_rt *rt, t_vec3 *viewport_u, \
t_vec3 *viewport_v, t_vec3 *cam_w)
{
	float		h;
	float		defoc_radius;
	float		viewport[2];
	t_vec3		cam[2];

	h = tan(rt->camera.hfov / 2) * rt->camera.focus_dist;
	// viewport[H] = 2 * h;
	// viewport[W] = (viewport[H] * WIN_WIDTH) / WIN_HEIGHT;
	// for hfov method, push changes later
	viewport[W] = 2 * h;
	viewport[H] = (viewport[W] * WIN_HEIGHT) / WIN_WIDTH;

	// /*debug*/printf("h:%f, viewport: %f %f\n", h, viewport[X], viewport[Y]);
	*cam_w = unit_vec3(subtract_vec(rt->camera.pos, rt->camera.lookat));
	cam[X] = unit_vec3(cross_product(rt->camera.vup, *cam_w));
	cam[Y] = mult_vec_scalar(cross_product(*cam_w, cam[X]), -1); // -v
	
	
	// *cam_w = quaternion_rotate_adv(*cam_w, rt->camera.transform.rotate, 1);
	// cam[X] = quaternion_rotate_adv(cam[X], rt->camera.transform.rotate, 1);
	// cam[Y] = quaternion_rotate_adv(cam[Y], rt->camera.transform.rotate, 1);
	// /*debug*/printf("cam_w: %f %f %f\n", (*cam_w).x, (*cam_w).y, (*cam_w).z);
	// /*debug*/printf("cam[X]: %f %f %f\n", cam[X].x, cam[X].y, cam[X].z);
	// /*debug*/printf("cam[Y]: %f %f %f\n", cam[Y].x, cam[Y].y, cam[Y].z);
	*viewport_u = mult_vec_scalar(cam[X], viewport[W]);
	*viewport_v = mult_vec_scalar(cam[Y], viewport[H]);
	// /*debug*/printf("cam_w: %f %f %f\n", (*cam_w).x, (*cam_w).y, (*cam_w).z);
	// /*debug*/printf("cam_u: %f %f %f\n", cam[X].x, cam[X].y, cam[X].z);
	// /*debug*/printf("cam_v: %f %f %f\n", cam[Y].x, cam[Y].y, cam[Y].z);
	
	defoc_radius = rt->camera.focus_dist * tan(rt->camera.defoc_ang / 2);

	rt->camera.defoc_disk[X] = mult_vec_scalar(cam[X], defoc_radius); // right vector
	rt->camera.defoc_disk[Y] = mult_vec_scalar(cam[Y], defoc_radius); // up vector

	// *viewport_u = new_vector3d(viewport[X], 0, 0);
	// *viewport_v = new_vector3d(0, -viewport[Y], 0);
	// /*debug*/printf("vp_uv in: %f %f %f, %f %f %f\n", (*viewport_u).x, (*viewport_u).y, (*viewport_u).z, (*viewport_v).x, (*viewport_v).y, (*viewport_v).z);
}

/*
 * child function in my_render_image
 * get starting values of viewport (viewport top_left)
 * & center of top_left_pixel (viewport_00_loc)
 * 
 * brief: gets the coords to start drawing (center of top left of cam view)
 * vp_00_loc: location of pixel (0,0) in world space
 * vp_top_left: location of top-left corner of the screen (viewport)
 * vp_d[X] and vp_d[Y]: how far to move one pixel right/down in world units
 * why we need this? we shoot rays through the center of the pixel for better accuracy
 * 
 * 1. get the shape and orientation of the screen in 3d space (previous func)
 * 2. computes how much distance (in world space) each pixel takes along the x, y of viewport
 *    vp_d[X] = 4 (units in world) / 800 = 0.005 units = every step right
 * 3. move the camera position forward to get to the center of the screen
 * 4. move halfway left > move halfway up to get to the top left pixel
 * 5. set the start to the center of the top left pixel
 */
static void	get_viewport_coords(t_rt *rt, t_vec3 *vp_00_loc, \
t_vec3 *vp_top_left, t_vec3 vp_d[2])
{
	t_vec3	vp[2];
	t_vec3	cam_w;

	get_viewport_uv(rt, &vp[X], &vp[Y], &cam_w);	
	vp_d[X] = div_vec_scalar(vp[X], WIN_WIDTH);
	vp_d[Y] = div_vec_scalar(vp[Y], WIN_HEIGHT);
	*vp_top_left = subtract_vec(rt->camera.pos, \
mult_vec_scalar(cam_w, rt->camera.focus_dist));
	*vp_top_left = subtract_vec(*vp_top_left, div_vec_scalar(vp[X], 2));
	*vp_top_left = subtract_vec(*vp_top_left, div_vec_scalar(vp[Y], 2));
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
 * viewport_d = dydx or dudv of viewport (how far to move by 1 pixel)
 * 
 * brief: calculate 3d target point for each pixel > calc col > draw
 * 1. move through every row and col 
 * 2. get the col at the pixel
 * 3. draw pixel on screen
 */
static void	ft_draw(t_rt rt, t_vec3 viewport_00, t_vec3 viewport_d[2])
{
	int		x;
	int		y;
	int		color;
	t_vec3	target;		

	x = -1;
	y = -1;
	target = viewport_00;

	// target.z = viewport_00.z + (x * viewport_d[X].z) + (y * viewport_d[Y].z);
	while (++y < WIN_HEIGHT)
	{
		x = 0;
		target.y = viewport_00.y + (x * viewport_d[X].y) + (y * viewport_d[Y].y);
		// target.y = viewport_00.y + (y * viewport_d[Y].y);
		while (++x < WIN_WIDTH)
		{
			// target.x = viewport_00.x + (x * viewport_d[X].x); //short
			target.x = viewport_00.x + (x * viewport_d[X].x) + (y * viewport_d[Y].x);
// x = viewport_00.x + (x * dx.x)  |->  + (offset.x * dx.x)
//                   + (y * dy.x)  |->  + (offset.y * dy.x)
			color = sample_pixels(rt, target, viewport_d, x);
			my_mlx_pixel_put(rt, x, y, color);
		}
	}
}

/*
 * vp_00 = center of pixel 00 in viewport
 * vp_d = dydx or dudv of viewport (pixel step size)
 * 
 * brief: render whole scene / img
 * get start > draw every pixel > put img to window
 */
void	my_render_image(t_rt *rt)
{
	t_vec3	vp_d[2];
	t_vec3	vp_00_loc;
	t_vec3	vp_top_left;

	//clear before draw
	clear_image(*rt, WIN_WIDTH, WIN_HEIGHT, 0x000000);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, \
rt->img.img, 0, 0);

	//draw
	get_viewport_coords(rt, &vp_00_loc, &vp_top_left, vp_d);
	ft_draw(*rt, vp_00_loc, vp_d);

	//push draw result to window
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, \
rt->img.img, 0, 0);
	draw_panel(rt);
	keybind_guide(rt);
	selection_guide(rt);
}
