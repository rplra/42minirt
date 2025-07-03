/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybind.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:47:24 by hsim              #+#    #+#             */
/*   Updated: 2025/07/03 10:14:03 by rraja-az         ###   ########.fr       */
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
#  define KEY_ESC 65307 //53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_SPACE 49
#  define KEY_TAB   48
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_PLUS 24
#  define KEY_MINUS 27
#  define MOUSE_LEFT 1
#  define MOUSE_RIGHT 2
// #  define MOUSE_SCROLL_UP 4
// #  define MOUSE_SCROLL_DOWN 5
# elif defined(LINUX)
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_SPACE 32
#  define KEY_TAB   65289
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_PLUS 61
#  define KEY_MINUS 45
#  define MOUSE_LEFT 1
#  define MOUSE_RIGHT 2
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

# include "minirt.h"

typedef struct s_rt	t_rt;

/* __________________ key configurations __________________ */
int			close_window(int keycode, t_rt *vars);
int			close_window_x(int keycode, t_rt *vars);
int			key_press(int keycode, void *param);

#endif