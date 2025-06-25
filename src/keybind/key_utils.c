/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsim <hsim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:32 by hsim              #+#    #+#             */
/*   Updated: 2025/06/25 11:08:56 by hsim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keybind.h"

/* prints out current keycode number */
int	key_press(int keycode, void *param)
{
	(void)param;
	printf("🟡 keycode is %i\n", keycode);
	// add on other keypress here
	return (0);
}
