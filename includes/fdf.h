/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 18:11:38 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/26 18:11:58 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <camera.h>
# include <map.h>
# include <graphics.h>
# include <libft.h>
# include <get_next_line.h>
# include <mlx.h>
# include <errno.h>
# include <stdio.h>

typedef struct	s_env
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
	t_cam		*cam;
	t_map		*map;
}				t_env;

int				key_hook(int keycode, void *param);
int				expose_hook(void *param);
int				integer_decode(char **s, int *error);

#endif
