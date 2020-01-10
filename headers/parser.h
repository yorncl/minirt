

#ifndef PARSER_H
# define PARSER_H

# include <get_next_line.h>
# include <world.h>
# include <macro.h>
# include <objs.h>
# include <light.h>
# include <color.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <libft.h>
# include <vec3.h>
# include <raytracerstruct.h>

# define FLAG_RES 1
# define FLAG_AMBIENT 2

int		parse_world(t_minirt *rt, char *path);
int		parse_line(t_minirt *rt, char *line, int n);
int		parse_identifier(
			char *line,
			int	(**parser)(t_minirt *rt, char *str),
			int *offset);
int		is_identifier_known(char *line);
int		parse_vec3(t_vec3 *v, char *line);
int		parse_color(unsigned int *c, char *line);
int		parse_double(double *v, char *line);

int		parsing_error(char *msg, int n);

int		parse_resolution(t_minirt *rt, char *line);

int		parse_camera(t_minirt *rt, char *line);
int		parse_light(t_minirt *rt, char *line);
int		parse_ambient(t_minirt *rt, char *line);

int		parse_sphere(t_minirt *rt, char *line);
int		parse_plane(t_minirt *rt, char *line);
int		parse_square(t_minirt *rt, char *line);
int		parse_triangle(t_minirt *rt, char *line);
int		parse_cylinder(t_minirt *rt, char *line);
#endif