/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 13:00:23 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/26 13:00:42 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static t_env	*ft_use_env(int action)
{
	static t_env		*env;

	if (action == 1)
	{
		env = (t_env*)ft_memalloc(sizeof(t_env));
		env->width = 600;
		env->height = 490;
		if ((env->cam = cam_init(env->width, env->height)) != 0 &&
			(env->map = (t_map*)ft_memalloc(sizeof(t_map))) != 0)
		{
			env->map->width = 0;
			env->map->height = 0;
		}
		else
			action = 2;
	}
	if (action == 2 && env != 0)
	{
		ft_memdel((void**)&(env->cam));
		ft_memdel((void**)&(env->map->vectors));
		ft_memdel((void**)&(env->map));
		ft_memdel((void**)&(env));
	}
	return (env);
}

int				key_hook(int keycode, void *param)
{
	t_env		*env;

	env = ft_use_env(0);
	if (env->cam != 0 && param == &(*param))
	{
		if (keycode == 126)
			env->cam->x += 1 / 50.0;
		if (keycode == 125)
			env->cam->x -= 1 / 50.0;
		if (keycode == 123)
			env->cam->y += 1 / 50.0;
		if (keycode == 124)
			env->cam->y -= 1 / 50.0;
		if (keycode == 69)
			cam_zoom(env->cam, 0.5);
		if (keycode == 78)
			cam_zoom(env->cam, -0.5);
	}
	if (keycode == 53)
	{
		ft_use_env(2);
		exit(1);
	}
	expose_hook(0);
	return (0);
}

static void		render_lines(t_env *env, int x, int y, int row)
{
	t_pt		*start;
	t_pt		*end;

	start = cam_render(env->cam, map_get_vector_at(env->map, x, y));
	end = cam_render(env->cam, map_get_vector_at(env->map,
		(row == 1) ? x + 1 : x, (row == 0) ? y + 1 : y));
	if (start && end)
		mlx_line_put(env->mlx_ptr, env->win_ptr, start, end);
	ft_memdel((void**)&(start));
	ft_memdel((void**)&(end));
}

int				expose_hook(void *param)
{
	t_env		*env;
	int			x;
	int			y;

	env = ft_use_env(0);
	param = 0;
	mlx_clear_window(env->mlx_ptr, env->win_ptr);
	x = 0;
	while (x < env->map->width)
	{
		y = 0;
		while (y < env->map->height)
		{
			if ((x + 1) < env->map->width)
				render_lines(env, x, y, 1);
			if ((y + 1) < env->map->height)
				render_lines(env, x, y, 0);
			y++;
		}
		x++;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_env		*env;
	int			color;

	errno = 0;
	if (argc > 1 && (env = ft_use_env(1)) != 0)
	{
		color = (argc > 2) ? integer_decode(&(argv[2]), 0) : 0;
		if (map_read(env->map, argv[1], color))
		{
			env->mlx_ptr = mlx_init();
			if (env->mlx_ptr != 0 && (env->win_ptr =
				mlx_new_window(env->mlx_ptr, env->width,
					env->height, "fdf")) != 0)
			{
				cam_scale_to_obj(env->cam, env->map->width, env->map->height);
				mlx_key_hook(env->win_ptr, key_hook, 0);
				mlx_expose_hook(env->win_ptr, expose_hook, 0);
				mlx_loop(env->mlx_ptr);
			}
		}
		perror("Error");
	}
	ft_putstr("Usage : fdf filename [color]\n");
	ft_use_env(2);
	return (0);
}
