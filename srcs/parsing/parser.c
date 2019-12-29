#include <parser.h>

// int		parse_world(t_world *w, char *path)
// {
// 	int		fd;
// 	int		r;
// 	char	**line;
	
// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 		return (ERROR);
// 	while (1)
// 	{
// 		r = get_next_line(fd, line);
		
// 		if (r == -1 || parse_line(w, *line) == -1)
// 		{
// 			free(line);
// 			return (ERROR);
// 		}
// 		if (r == 0)
// 			return (SUCCESS)
// 	}
// }
 q
i nt		parse_double(double *v, char *line)
{
	double a;
	double coef;

	a = 0;
	coef = 1;
	if (!ft_isdigit(*line))
		return (ERROR);
	while (ft_isdigit(*line))
		a = a * 10 + *(line++) - '0';
	if (*line++ == '.')
		while (ft_isdigit(*line))
		{
			coef /= 10;
			a += (double)((*(line++) - '0') * coef);
		}
	*v = a;
	return (SUCCESS);
}