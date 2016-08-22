/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 13:42:38 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/22 13:43:01 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "vectors.h"

int		mlx_grad(int start, int end, double steps);
void	mlx_line_put(void *mlx_ptr, void *win_ptr, t_pt *start, t_pt *end);

#endif
