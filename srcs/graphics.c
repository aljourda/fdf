/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 14:11:19 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/22 14:32:50 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphics.h>
#include <libft.h>
#include <math.h>
#include <mlx.h>

int			mlx_grad(int start, int end, double steps)
{
	double	r;
	double	g;
	double	b;
	int		ret;

	if (steps > 0)
	{
		r = (end >> 16) & 0xff;
		r -= (start >> 16) & 0xff;
		r = round(r / steps);
		g = (end >> 8) & 0xff;
		g -= (start >> 8) & 0xff;
		g = round(g / steps);
		b = (end >> 0) & 0xff;
		b -= (start >> 0) & 0xff;
		b = round(b / steps);
		ret = (int)r;
		ret <<= 8;
		ret += (int)g;
		ret <<= 8;
		ret += (int)b;
		return (ret + start);
	}
	return (end);
}

static int	mlx_line_calc_dir(t_pt *start, t_pt *end)
{
	int		dir;

	dir = abs(end->y - start->y) > abs(end->x - start->x);
	if (dir)
	{
		ft_swap_int(&(start->x), &(start->y));
		ft_swap_int(&(end->x), &(end->y));
	}
	if (start->x > end->x)
	{
		ft_swap_int(&(start->x), &(end->x));
		ft_swap_int(&(start->y), &(end->y));
		ft_swap_int(&(start->color), &(end->color));
	}
	return (dir);
}

void		mlx_line_put(void *mlx_ptr, void *win_ptr, t_pt *start, t_pt *end)
{
	int		dir;
	int		dx;
	int		dy;
	int		err;
	int		ystep;

	dir = mlx_line_calc_dir(start, end);
	dx = end->x - start->x;
	dy = abs(end->y - start->y);
	err = dx / 2;
	ystep = (start->y < end->y) ? 1 : -1;
	while (start->x <= end->x)
	{
		if (dir)
			mlx_pixel_put(mlx_ptr, win_ptr, start->y, start->x, start->color);
		else
			mlx_pixel_put(mlx_ptr, win_ptr, start->x, start->y, start->color);
		if ((err -= dy) < 0)
		{
			start->y += ystep;
			err += dx;
		}
		start->color = mlx_grad(start->color, end->color, (end->x - start->x));
		start->x++;
	}
}
