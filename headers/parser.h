

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

int		parse_world(t_minirt *rt, char *path);
int		parse_line(t_minirt *rt, char *line, int n);
int		parse_vec3(t_vec3 *v, char *line);
int		parse_double(double *v, char *line);

int		parsing_error(char *msg, int n);

int		parse_resolution(t_minirt *rt, char *line);

int		parse_camera(t_minirt *rt, char *line);
int		parse_light(t_world *w, char *line);

int		parse_sphere(t_world *w, char *line);
#endif