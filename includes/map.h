/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 13:28:22 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/22 13:28:52 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "vectors.h"

typedef struct	s_map
{
	int			width;
	int			height;
	int			relief;
	t_v3		**vectors;
}				t_map;

t_v3			*map_get_vector_at(t_map *map, int x, int y);
int				map_read(t_map *map, char *filename, int color);

#endif
