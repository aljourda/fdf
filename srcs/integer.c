/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljourda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/28 16:31:16 by aljourda          #+#    #+#             */
/*   Updated: 2016/07/28 16:31:52 by aljourda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int		ft_getinbase(int c, int base)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'Z' && base > 10)
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'z' && base > 10)
		return (c - 'a' + 10);
	return (0);
}

static int		ft_isinbase(int c, int base)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z' && base > 10)
		return (1);
	if (c >= 'a' && c <= 'z' && base > 10)
		return (1);
	return (0);
}

int				integer_decode(char **s, int *error)
{
	long	result;
	int		base;
	int		sign;

	base = 10;
	result = 0;
	sign = 1;
	while (ft_isspace(**s))
		(*s)++;
	if (**s == '0' && (*(*s + 1) == 'x' || *(*s + 1) == 'b'))
	{
		base = (*(*s + 1) == 'x') ? 16 : 2;
		*s += 2;
	}
	if ((**s == '-' || **s == '+') && ft_isinbase(*(*s + 1), base)
		&& *((*s)++) == '-' && base == 10)
		sign = -1;
	else if (error && (**s == '-' || **s == '+'))
		*error = -1;
	if (error && !ft_isinbase(**s, base) && **s)
		*error = -2;
	else
		while (ft_isinbase(**s, base))
			result = (result * base) + ft_getinbase(*(*s)++, base);
	return (result * sign);
}
