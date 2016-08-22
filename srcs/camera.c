/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 14:14:33 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/22 14:20:18 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <camera.h>
#include <stdlib.h>
#include <math.h>

t_cam			*cam_init(int width, int height)
{
	t_cam	*cam;

	if ((cam = (t_cam*)malloc(sizeof(t_cam))) != 0)
	{
		cam->x = 0.5;
		cam->y = 0.5;
		cam->scale = 20;
		cam->offset_x = width / 2.0;
		cam->offset_y = height / 2.0;
	}
	return (cam);
}

void			cam_scale_to_obj(t_cam *cam, int width, int height)
{
	double x_size;
	double y_size;

	y_size = height / (cam->offset_y * 1.4);
	x_size = width / (cam->offset_x * 1.4);
	cam->scale = x_size;
	if (y_size > cam->scale)
		cam->scale = y_size;
	cam->scale = 1 / cam->scale;
}

void			cam_zoom(t_cam *cam, double value)
{
	cam->scale += value;
	if (cam->scale < 0.0)
		cam->scale -= value;
}

t_pt			*cam_render(t_cam *cam, t_v3 *vector)
{
	t_pt	*ret;
	double	z;

	ret = 0;
	if (cam != 0 && vector != 0 && (ret = (t_pt*)malloc(sizeof(t_pt))) != 0)
	{
		ret->color = vector->color;
		z = -sin(cam->y) * vector->x + cos(cam->y) * vector->z;
		ret->x = (int)(((cos(cam->y) * vector->x +
			sin(cam->y) * vector->z) * cam->scale) + cam->offset_x);
		ret->y = (int)(((cos(cam->x) * vector->y -
			sin(cam->x) * z) * cam->scale) + cam->offset_y);
	}
	return (ret);
}
