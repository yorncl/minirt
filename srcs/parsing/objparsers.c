#include <parser.h>

#include <stdio.h>

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
		v3new(fovx, 2 * atan(tan(fovx / 2) * rt->resy / rt->resx ), 0)) == ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}

int		parse_light(t_world *w, char *line)
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
	if ((rd = parse_color(&c, line)) == ERROR)
		return (ERROR);
	if (add_ligth(w, pos, intensity * MAX_LIGHT_INTENSITY, c.v) == ERROR)
		return (ERROR);
	line += rd;
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}

int		parse_sphere(t_world *w, char *line)
{
	t_vec3	pos;
	double	radius;
	t_color	c;
	int		rd;

	if ((rd = parse_vec3(&pos, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_double(&radius, line)) == ERROR)
		return (ERROR);
	line += rd;
	if ((rd = parse_color(&c, line)) == ERROR)
		return (ERROR);
	line += rd;
	if (add_sphere(w, pos, radius, c.v) == ERROR)
		return (ERROR);
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	return (SUCCESS);
}