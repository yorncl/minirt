#include <parser.h>

#include <stdio.h>

int		parse_world(t_minirt *rt, char *path)
{
	int		fd;
	int		r;
	int		n;
	char	*line;
	
	n = 1;
	fd = open(path, O_RDONLY);
	line = 0;
	if (fd == -1)
		return (ERROR);
	while (1)
	{
		r = get_next_line(fd, &line);
		if (r == -1 || parse_line(rt, line, n) == -1)
		{
			free(line);
			return (ERROR);
		}
		n++;
		if (r == 0)
			return (SUCCESS);
	}
	return (SUCCESS);
}

int		parse_line(t_minirt *rt, char *line, int n)
{
	if (line[0] == 'R' && parse_resolution(rt, line + 1) == ERROR)
		return ((parsing_error("resolution not good", n)));
	else if (line[0] == 'c' && parse_camera(rt, line + 1) == ERROR)
		return ((parsing_error("camera not good", n)));
	else if (line[0] == 'l' && parse_light(rt, line + 1) == ERROR)
		return ((parsing_error("light not good", n)));
	
	return (SUCCESS);
}


int		parse_resolution(t_minirt *rt, char *line)
{
	rt->resx = 0;
	rt->resy = 0;
	while (ft_isspace(*line))
		line++;
	while (*line && ft_isdigit(*line))
	{
		rt->resx = rt->resx * 10 + *line - '0';
		line++;
	}
	while (ft_isspace(*line))
		line++;
	while (*line && ft_isdigit(*line))
	{
		rt->resy = rt->resy * 10 + *line - '0';
		line++;
	}
	while (*line)
		if (!ft_isspace(*line++))
			return (ERROR);
	if (rt->resx == 0 || rt->resy == 0)
		return (ERROR);
	return (SUCCESS);
}

int		parsing_error(char *msg, int n)
{
	char *str;

	str = ft_itoa(n);
	write(1, "\e[1;31m", 7);
	write(1, msg, ft_strlen(msg));
	if (str)
	{
		write(1, " at line: ", 10);
		write(1, str, ft_strlen(str));
	}
	write(1, "\n\e[0m", 5);
	return (ERROR);
}

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