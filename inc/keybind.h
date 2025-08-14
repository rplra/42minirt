/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:47:24 by hsim              #+#    #+#             */
/*   Updated: 2025/08/14 14:23:14 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBIND_H
# define KEYBIND_H


# ifndef MAC
#  if defined(__APPLE__) && defined(__MACH__)
#   define MAC
#  elif defined(__linux__) && !defined(LINUX)
#   define LINUX
#  endif
# endif

# ifdef MAC
#  define KEY_ESC         53
#  define KEY_UP          126
#  define KEY_DOWN        125
#  define KEY_LEFT        123
#  define KEY_RIGHT       124
#  define KEY_SPACE       49
#  define KEY_TAB         48
#  define KEY_W           13
#  define KEY_A           0
#  define KEY_S           1
#  define KEY_D           2
#  define KEY_Q           12
#  define KEY_E           14
#  define KEY_P           35
#  define KEY_R           15
#  define KEY_U           32
#  define KEY_O           31
#  define KEY_P           35
#  define KEY_I           34
#  define KEY_J           38
#  define KEY_K           40
#  define KEY_L           37
#  define KEY_C           8
#  define KEY_X           7
#  define KEY_1           18
#  define KEY_2           19
#  define KEY_3           20
#  define KEY_4           21

#  define KEY_PLUS        24
#  define KEY_MINUS       27
#  define MOUSE_LEFT      1
#  define MOUSE_RIGHT     2
#  define KEY_ARROW_L     43  // comma key
#  define KEY_ARROW_R     47  // period key
// #  define MOUSE_SCROLL_UP 4
// #  define MOUSE_SCROLL_DOWN 5
# elif defined(LINUX)
#  define KEY_ESC			65307
#  define KEY_UP			65362
#  define KEY_DOWN			65364
#  define KEY_LEFT			65361
#  define KEY_RIGHT			65363
#  define KEY_SPACE			32
#  define KEY_TAB			65289
#  define KEY_W				119
#  define KEY_A				97
#  define KEY_S				115
#  define KEY_D				100
#  define KEY_Q				113
#  define KEY_E				101
#  define KEY_P				112
#  define KEY_R				114
#  define KEY_U				117
#  define KEY_O				111
#  define KEY_P				112
#  define KEY_I				105
#  define KEY_J				106
#  define KEY_K				107
#  define KEY_L				108
#  define KEY_C				99
#  define KEY_X				120
#  define KEY_1				49
#  define KEY_2				50
#  define KEY_3				51
#  define KEY_4				52

#  define KEY_PLUS			61
#  define KEY_MINUS			45
#  define MOUSE_LEFT		1
#  define MOUSE_RIGHT		2
#  define KEY_ARROW_L 		44
#  define KEY_ARROW_R 		46
// #  define MOUSE_SCROLL_UP 4
// #  define MOUSE_SCROLL_DOWN 5
# endif

/* ------------------------------- clicks -------------------------------- */
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define MIDDLE_CLICK 3

/* ------------------------------ scrolls -------------------------------- */
# define UP_SCROLL 5
# define DOWN_SCROLL 4

/* -------------------------- mlx X11 events ----------------------------- */
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6

// # include "minirt.h"

# include <stdio.h>
# include <stdbool.h>
# include "../lib/quaternion/ft_vector.h"
# include "render.h"


typedef struct s_rt	t_rt;

typedef enum e_sel_type
{
	SEL_CAMERA,
	SEL_LIGHT,
	SEL_OBJ
}				t_sel_type;

typedef struct s_sel
{
	t_sel_type	type;
	int			obj_index;
	t_obj		*obj_ptr; 
}				t_sel;

typedef struct s_label
{
    t_img   camera;
    t_img   light;
    t_img   sphere;
    t_img   plane;
    t_img   cylinder;
	t_img	digits[10];
}   t_label;

typedef struct s_info
{
	t_img	pos;
	t_img	rot;
	t_img	dot;
	t_img	comma;
	t_img	minus;
}	t_info;


/* __________________ key menu __________________ */
void		draw_panel(t_rt *rt);
void		keybind_guide(t_rt *rt);
void		selection_guide(t_rt *rt);

/* __________________ key configurations __________________ */
int			close_window(int keycode, t_rt *vars);
int			close_window_x(int keycode, t_rt *vars);
int			key_press(int keycode, t_rt *rt);

void		handle_render_mode(t_rt *rt, int keycode);
void		handle_selection(t_rt *rt, int keycode);
void		handle_translation(t_rt *rt, int keycode);
void		handle_scale(t_rt *rt, int keycode);
void		handle_rotation(t_rt *rt, int keycode);
void		handle_show_light(t_rt *rt, int keycode);
void		handle_focus_dist(t_rt *rt, int keycode);
void		handle_render_style(t_rt *rt, int keycode);
void		handle_animate(t_rt *rt, int keycode);

t_vec3		translation_delta(int keycode);
float		scale_factor(int keycode);
int			animate_light(t_rt *rt);


void		print_selected(t_rt *rt);

bool		translation_key(int keycode);
bool		scale_key(int keycode);
bool		focus_dist_key(int keycode);
bool		rotation_key(int keycode);
bool		control_key(int keycode);
bool		style_key(int keycode);

void		get_info(t_rt *rt, int x, int *y, int line_ht);
t_uint		get_obj_index(t_obj *obj, int obj_count, t_uint id);
t_uint		get_light_index(t_obj *obj, int obj_count);
void		update_cam_pos(t_rt *rt, int keycode);

char		*ft_ftoa(float f);
char		*get_info_str(t_vec3 pos);
void		display_digit_xpm(t_rt *rt, char *str, int x, int y);
void		reset_cam(t_rt *rt, int keycode);

#endif