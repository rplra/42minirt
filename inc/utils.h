/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraja-az <rraja-az@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:42:28 by rraja-az          #+#    #+#             */
/*   Updated: 2025/08/22 08:54:28 by rraja-az         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int			print_error(t_parse *file, char *msg, int param, char **params);
void		exit_with_error(char *msg);
void		perror_exit(char *perrmsg);

void		free_main_img(t_rt *rt);
void		free_label_img(t_rt *rt);
void		free_info_img(t_rt *rt);

int			free_array(char **arr);
void		free_one(void *vars);
void		free_bvh(t_bvh_tree *bvh);
void		cleanup(t_rt *rt);
void		cleanup_and_exit(t_rt *rt, int exit_code);

#endif