/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 13:21:15 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/22 13:21:17 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "vectors.h"

typedef struct	s_cam
{
	double		offset_x;
	double		offset_y;
	double		x;
	double		y;
	double		scale;
}				t_cam;

t_cam			*cam_init(int width, int height);
void			cam_scale_to_obj(t_cam *cam, int width, int height);
void			cam_zoom(t_cam *cam, double value);
t_pt			*cam_render(t_cam *cam, t_v3 *vector);

#endif
