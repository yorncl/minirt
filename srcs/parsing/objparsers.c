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
	if (!v3drange(rot, -1, 1) || fovx < 0 || fovx > 180)
		return (ERROR);
	if (add_t_camera(rt->world, pos, v3scale(rot, 2 * M_PI),
		v3new(fovx, 2 * atan(tan(fovx / 2) * rt->resy / rt->resx ), 0)) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int		parse_light(t_world *w, char *line)
{
	t_vec3	pos;
	double	intensity;
	t_vec3	colorv;
	t_color

}