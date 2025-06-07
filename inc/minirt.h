/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:49:25 by rraja-az          #+#    #+#             */
/*   Updated: 2025/06/07 10:51:05 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "../lib/inc/libft.h"
# include "../lib/gnl/get_next_line.h"
# include "config.h"
# include "keymap.h"
# include "utils.h"
# include "scene.h"
# include "parse.h"

# define RED "\033[31m"
# define RESET "\033[0m"

# define YES	1
# define NO		0

typedef unsigned int uint;

typedef	struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_rt
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_camera	camera;
}				t_rt;


#endif