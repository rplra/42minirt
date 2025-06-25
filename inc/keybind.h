/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:47:24 by hsim              #+#    #+#             */
/*   Updated: 2025/06/25 11:08:18 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBIND_H
# define KEYBIND_H

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

# include "minirt.h"

typedef struct s_rt	t_rt;

/* __________________ key configurations __________________ */
int			close_window(int keycode, t_rt *vars);
int			close_window_x(int keycode, t_rt *vars);
int			key_press(int keycode, void *param);

#endif