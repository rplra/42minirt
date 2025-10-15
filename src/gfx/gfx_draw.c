/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:21:10 by hsim              #+#    #+#             */
/*   Updated: 2025/10/15 18:53:45 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * child function in get_viewport_coords
 * get value of viewport_uv and save to
 * t_vector3d *viewport_u & *viewport_v
 * 
 * brief : calc how big camera's screen is in 3d world 
 * 			and the direction its looking at (cam w)
 * defocus disk (disk is the cam's lens surface - 
 * 			flat circle in 3d world); blur / bokeh
 * camera = where rays originate from and how they were constructed
 * viewport = screen = where rays are aimed at, pixel by pixel
 * 
 * rt->camera.defoc_disk[X] = right edge of lens
 * rt->camera.defoc_disk[Y] = up edge of lens
 * 
 * 1. calculates viewport size in world units
 * 2. computes cam's local coords frame (basis vector)
 * 3. scale the cam's axis to viewport size 
 * 		(entire width and ht of screen) & the defoc disk
 */
static void	get_viewport_uv(t_rt *rt, t_vec3 *viewport_u, \
t_vec3 *viewport_v, t_vec3 *cam_w)
{
	float		width;
	float		defoc_radius;
	float		viewport[2];
	t_vec3		cam[2];

	width = tan(rt->camera.hfov / 2) * rt->camera.focus_dist;
	viewport[W] = 2 * width;
	viewport[H] = (viewport[W] * WIN_HEIGHT) / WIN_WIDTH;
	*cam_w = mult_vec_scalar(rt->camera.lookat, -1);
	if (fabs(scalar_product(*cam_w, rt->camera.vup)) > 0.9999)
		rt->camera.vup = cross_product(new_vec3(1, 0, 0), rt->camera.lookat);
	cam[X] = unit_vec3(cross_product(rt->camera.vup, *cam_w));
	cam[Y] = cross_product(*cam_w, cam[X]);
	*viewport_u = mult_vec_scalar(cam[X], viewport[W]);
	*viewport_v = mult_vec_scalar(cam[Y], viewport[H] * -1);
	defoc_radius = rt->camera.focus_dist * tan(rt->camera.defoc_ang / 2);
	rt->camera.defoc_disk[X] = mult_vec_scalar(cam[X], defoc_radius);
	rt->camera.defoc_disk[Y] = mult_vec_scalar(cam[Y], defoc_radius);
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
 * why we need this?
 * 		we shoot rays through the center of the pixel for better accuracy
 * 
 * 1. get the shape & orientation of the screen in 3d space (previous func)
 * 2. computes how much distance (in world space) each pixel takes
 * 		along the x, y of viewport
 *    vp_d[X] = 4 (units in world) / 800 = 0.005 units = every step right
 * 3. move the camera position forward to get to the center of the screen
 * 4. move halfway left > move halfway up to get to the top left pixel
 * 5. set the start to the center of the top left pixel
 */
void	get_viewport_coords(t_rt *rt, t_vec3 *vp_00_loc, \
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
}

/* 
 * seed = rt.seed;	//grunge
 * seed += add_on;	//slant sketch
*/
static int	custom_style(t_rt rt, t_vec3 target, t_vec3 viewport_d[2], \
int add_on)
{
	t_uint	seed;

	seed = rt.seed;
	if (rt.b_style == 1)
		seed += add_on;
	return (sample_pixels(rt, target, viewport_d, &seed));
}

/*
 * child function in my_render_image
 * viewport_00 = center of pixel 00 in viewport
 * viewport_d = dydx or dudv of viewport (how far to move by 1 pixel)
 * if (rt.b_style == 0) = fine pointilism
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
	t_vec3	pixel_center;

	x = -1;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = 0;
		while (++x < WIN_WIDTH)
		{
			pixel_center = add_vec(viewport_00,
					mult_vec_scalar(viewport_d[X], x));
			pixel_center = add_vec(pixel_center,
					mult_vec_scalar(viewport_d[Y], y));
			if (rt.b_style == 0)
				color = sample_pixels(rt, pixel_center, viewport_d, &rt.seed);
			else
				color = custom_style(rt, pixel_center, viewport_d, x + y);
			ft_mlx_pixel_put(rt, x, y, color);
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
void	render(t_rt *rt)
{
	t_vec3	vp_d[2];
	t_vec3	vp_00_loc;
	t_vec3	vp_top_left;

	get_viewport_coords(rt, &vp_00_loc, &vp_top_left, vp_d);
	ft_draw(*rt, vp_00_loc, vp_d);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, \
rt->img.img, 0, 0);
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, \
rt->img_menu.img, WIN_WIDTH, 0);
	selection_guide(rt);
}
