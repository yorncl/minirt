/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparsers1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:09:36 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/28 13:21:16 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int		parse_camera(t_minirt *rt, char *line)
{
	t_vec3	pos;
	t_vec3	rot;
	double	fovx;
	int		rd;

	if ((rd = parse_vec3(&pos, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_vec3(&rot, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_double(&fovx, line)) == ERROR)
		return (ERROR);
	line += rd;
	if (!v3drange(rot, -1, 1) || fovx < 0 || fovx > 180)
		return (ERROR);
	if (add_t_camera(rt->world, pos, v3scale(rot, 2 * M_PI),
		v3new(fovx, 2 * atan((tan((fovx * M_PI / 180) / 2) *
		(double)rt->resy) / (double)rt->resx) * 180 / M_PI, 0))
			== ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}

int		parse_light(t_minirt *rt, char *line)
{
	t_vec3	pos;
	double	intensity;
	t_color	c;
	int		rd;

	c.v = 0;
	if ((rd = parse_vec3(&pos, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_double(&intensity, line)) == ERROR
			|| intensity < 0 || intensity > 1)
		return (ERROR);
	line += rd;
	if ((rd = parse_color(&c.v, line)) == ERROR)
		return (ERROR);
	if (add_ligth(rt->world, pos,
			intensity * MAX_LIGHT_INTENSITY, c.v) == ERROR)
		return (ERROR);
	line += rd;
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}

int		parse_ambient(t_minirt *rt, char *line)
{
	double	intensity;
	t_color	c;
	int		rd;

	c.v = 0;
	if ((rd = parse_double(&intensity, line)) == ERROR
			|| intensity < 0 || intensity > 1)
		return (ERROR);
	line += rd;
	if ((rd = parse_color(&c.v, line)) == ERROR)
		return (ERROR);
	if (add_ambient(rt->world, intensity, c.v) == ERROR)
		return (ERROR);
	line += rd;
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}

int		parse_sphere(t_minirt *rt, char *line)
{
	t_objargs	args;
	double		radius;
	int			rd;

	if ((rd = parse_vec3(&args.pos, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_double(&radius, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_color(&args.color, line)) == ERROR)
		return (ERROR);
	line += rd;
	if (add_sphere(rt->world, args, radius) == ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}

int		parse_plane(t_minirt *rt, char *line)
{
	t_objargs	args;
	int			rd;

	if ((rd = parse_vec3(&args.pos, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_vec3(&args.rot, line)) == ERROR)
		return (ERROR);
	line += rd;
	if (!v3drange(args.rot, -1, 1))
		return (ERROR);
	if ((rd = parse_color(&args.color, line)) == ERROR)
		return (ERROR);
	line += rd;
	args.rot = v3scale(args.rot, 2 * M_PI);
	if (add_plane(rt->world, args) == ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}
