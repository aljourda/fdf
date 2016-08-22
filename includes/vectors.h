/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 13:18:09 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/22 13:28:22 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_pt
{
	int			x;
	int			y;
	int			color;
}				t_pt;

typedef struct	s_v3
{
	double		x;
	double		y;
	double		z;
	int			color;
}				t_v3;

#endif
