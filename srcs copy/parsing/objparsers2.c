/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparsers2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:09:33 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/13 16:23:07 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int		parse_square(t_minirt *rt, char *line)
{
	t_objargs	args;
	double		side;
	int			rd;

	if ((rd = parse_vec3(&args.pos, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_vec3(&args.rot, line)) == ERROR ||
			!v3drange(args.rot, -1, 1))
		return (ERROR);
	line += rd;
	if ((rd = parse_double(&side, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_color(&args.color, line)) == ERROR)
		return (ERROR);
	line += rd;
	args.rot = v3scale(args.rot, 2 * M_PI);
	if (add_square(rt->world, args, side) == ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}

int		parse_cylinder(t_minirt *rt, char *line)
{
	t_objargs	args;
	double		diameter;
	double		height;
	int			rd;

	if ((rd = parse_vec3(&args.pos, line)) == ERROR || !(line += rd))
		return (ERROR);
	if ((rd = parse_vec3(&args.rot, line)) == ERROR ||
			!v3drange(args.rot, -1, 1))
		return (ERROR);
	line += rd;
	if ((rd = parse_double(&diameter, line)) == ERROR || !(line += rd))
		return (ERROR);
	if ((rd = parse_double(&height, line)) == ERROR || !(line += rd))
		return (ERROR);
	if ((rd = parse_color(&args.color, line)) == ERROR)
		return (ERROR);
	line += rd;
	args.rot = v3scale(args.rot, 2 * M_PI);
	if (add_cylinder(rt->world, args, height, diameter / 2) == ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}

int		parse_triangle(t_minirt *rt, char *line)
{
	t_objargs	args;
	t_vec3		p2;
	t_vec3		p3;
	int			rd;

	if ((rd = parse_vec3(&args.pos, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_vec3(&p2, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_vec3(&p3, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_color(&args.color, line)) == ERROR)
		return (ERROR);
	line += rd;
	if (add_triangle(rt->world, args, p2, p3) == ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}
