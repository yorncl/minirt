

#ifndef PARSER_H
# define PARSER_H

# include <get_next_line.h>
# include <world.h>
# include <macro.h>
# include <objs.h>
# include <light.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <libft.h>

int		parse_world(t_world *w, char *path);
int		parse_line(t_world *w, char *line);
int		parse_vec3(t_vec3 *v, char *line);
int		parse_double(double *v, char *line);
int		parse_sphere(t_world *w, char *line);

#endif