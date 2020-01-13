/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsparsers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:15:36 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/13 14:48:50 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int		parse_vec3(t_vec3 *v, char *line)
{
	int		rd;
	int		r;
	int		i;
	double	*p;

	rd = 0;
	i = 3;
	p = &v->x;
	while (i--)
	{
		if ((r = parse_double(p, line)) == ERROR)
			return (ERROR);
		rd += r;
		line += r;
		if (i != 0 && *line++ != ',')
			return (ERROR);
		if (i != 0)
			rd++;
		p++;
	}
	return (rd);
}

int		parse_color(unsigned int *c, char *line)
{
	t_vec3	v;
	t_color color;
	int		r;

	if ((r = parse_vec3(&v, line)) == ERROR || !v3drange(v, 0, 255))
		return (ERROR);
	color.color.r = v.x;
	color.color.g = v.y;
	color.color.b = v.z;
	*c = color.v;
	return (r);
}

// Check for double size
int		parse_double(double *v, char *line)
{
	double	a;
	double 	coef;
	int		read;
	double	sign;

	a = 0;
	read = 0;
	coef = 1;
	sign = 1;
	while ((ft_isspace (*line) || *line == '-' || *line == '+') && ++read)
		if (*line++ == '-')
			sign *= -1;
	if (!ft_isdigit(*line))
		return (ERROR);
	while (ft_isdigit(*line) && ++read)
		a = a * 10 + *(line++) - '0';
	if (*line++ == '.' && ++read)
		while (ft_isdigit(*line))
		{
			coef /= 10;
			a += (double)((*(line++) - '0') * coef);
			read++;
		}
	// if (*[line - 1] )
	*v = a * sign;
	return (read);
}
