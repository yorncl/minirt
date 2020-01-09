#include <vec3.h>

int		v3intrange(t_vec3 v, int min, int max)
{
	return (
		v.x >= min && v.x <= max &&
		v.y >= min && v.y <= max &&
		v.z >= min && v.z <= max);
}

int		v3drange(t_vec3 v, double min, double max)
{
	return (
		v.x >= min && v.x <= max &&
		v.y >= min && v.y <= max &&
		v.z >= min && v.z <= max);
}