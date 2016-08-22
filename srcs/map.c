/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 13:58:30 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/22 13:59:45 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <fdf.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <libft.h>
#include <get_next_line.h>

t_v3			*map_get_vector_at(t_map *map, int x, int y)
{
	if (map != 0 && x >= 0 && y >= 0 && x < map->width && y < map->height)
	{
		return (map->vectors[(y * map->width) + (x % map->width)]);
	}
	return (0);
}

static void		ft_parse(const int fd, t_list **list, int *error, int color)
{
	t_v3		vector;
	char		*next[2];
	int			ret;
	void		*ptr;

	vector.y = 0;
	while ((ret = get_next_line(fd, &(next[0]))) > 0)
	{
		vector.x = 0;
		next[1] = next[0];
		*error = 0;
		while (*(next[1]) != 0 && *error == 0)
		{
			vector.z = integer_decode(&(next[1]), error);
			vector.color = (*next[1] == ',' && ++next[1]) ?
				integer_decode(&(next[1]), error) : color;
			if (!*error && (ptr = ft_lstnew(&vector, sizeof(t_v3))) != 0)
				ft_lstadd(list, ptr);
			else
				*error = -1;
			vector.x++;
		}
		vector.y++;
		ft_memdel((void**)&(next[0]));
	}
}

int				ft_read_file(t_map *map, t_list **list, char *fname, int color)
{
	t_list	*ltmp;
	int		ret;
	int		fd;
	t_v3	*tmp;

	ret = -2;
	fd = open(fname, O_RDONLY);
	if (fd > 0)
	{
		ft_parse(fd, list, &ret, color);
		ltmp = *list;
		while (ltmp)
		{
			if (ltmp->content_size == sizeof(t_v3))
			{
				tmp = (t_v3*)ltmp->content;
				map->width = (tmp->x > map->width) ? tmp->x + 1 : map->width;
				map->height = (tmp->y > map->height) ? tmp->y + 1 : map->height;
				map->relief = (tmp->z > map->relief) ? tmp->z : map->relief;
			}
			ltmp = ltmp->next;
		}
		close(fd);
	}
	return (ret);
}

static void		map_cpy(t_map *map, t_list *list, int color)
{
	t_v3	*tmp;
	int		pos;

	tmp = (t_v3*)list->content;
	pos = (int)((((int)tmp->y) * map->width) +
		(((int)tmp->x) % map->width));
	tmp->x -= map->width / 2.0;
	tmp->y -= map->height / 2.0;
	if (color == 0 && tmp->color == color)
	{
		if (tmp->z < 0)
			tmp->color = 0x00ff00;
		else if (tmp->z > 0)
			tmp->color = 0xff0000;
		else
			tmp->color = 0x0000ff;
	}
	else if (tmp->color == color)
		tmp->color = color;
	map->vectors[pos] = tmp;
}

int				map_read(t_map *map, char *filename, int color)
{
	t_list	*list;
	t_list	*next;

	list = 0;
	if (ft_read_file(map, &list, filename, color) == 0)
	{
		if (map->width > 0 && map->height > 0 && (map->vectors =
			(t_v3**)ft_memalloc(sizeof(t_v3*) * map->width * map->height)) != 0)
		{
			while (list)
			{
				if ((list)->content_size == sizeof(t_v3))
					map_cpy(map, list, color);
				next = (list)->next;
				ft_memdel((void**)&(list));
				list = next;
			}
			return (1);
		}
	}
	return (0);
}
