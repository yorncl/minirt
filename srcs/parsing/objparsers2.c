/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparsers2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:09:33 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/10 14:12:07 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int		parse_square(t_minirt *rt, char *line)
{
	t_vec3	pos;
	t_vec3	rot;
	double	side;
	t_color	c;
	int		rd;

	if ((rd = parse_vec3(&pos, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_vec3(&rot, line)) == ERROR || !v3drange(rot, -1, 1))
		return (ERROR);
	line += rd;
	if ((rd = parse_double(&side, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_color(&c, line)) == ERROR)
		return (ERROR);
	line += rd;
	if (add_square(rt->world, pos, v3scale(rot, 2 * M_PI),
			side, c.v) == ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}

int		parse_cylinder(t_minirt *rt, char *line)
{
	t_vec3	pos;
	t_vec3	rot;
	double	side;
	t_color	c;
	int		rd;

	if ((rd = parse_vec3(&pos, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_vec3(&rot, line)) == ERROR || !v3drange(rot, -1, 1))
		return (ERROR);
	line += rd;
	if ((rd = parse_double(&side, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_color(&c, line)) == ERROR)
		return (ERROR);
	line += rd;
	if (add_square(rt->world, pos, v3scale(rot, 2 * M_PI),
			side, c.v) == ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}
