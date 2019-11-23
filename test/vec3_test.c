#include <vec3.h>
#include <stdio.h>
#include <assert.h>

void	assertv3(vec3 *a,vec3 *b)
{
	assert(a->x == b->x);
	assert(a->y == b->y);
	assert(a->z == b->z);
}

int		main()
{
	printf("LAUNCHING TESTS\n");
	
	printf("v3new\n");
	vec3 *ptr = v3new(5,6,7);
	vec3 *r = v3new(0,1,2);
	free(ptr);
	printf("\e[32;1mDaijobu !\e[0m\n");
	
	printf("v3add\n");
	vec3 *a = v3new(1,1,1);
	vec3 *b = v3new(-1,0,1);
	v3set(r,0,1,2);
	v3add(a, b);
	assertv3(a , r);
	printf("\e[32;1mDaijobu !\e[0m\n");
	
	printf("v3sub\n");
	v3set(a,1,1,1);
	v3set(b,-1,0,1);
	v3set(r,2,1,0);
	v3sub(a, b);
	assertv3(a, r);
	printf("\e[32;1mDaijobu !\e[0m\n");

	printf("v3cross 1\n");
	v3set(a, 0,0,0);
	v3set(b,0,0,0);
	v3set(r,0,0,0);
	vec3 *c = v3cross(a, b);
	assertv3(c, r);
	free(c);
	printf("v3cross 2\n");
	v3set(a, 5,-2,1);
	v3set(b,1,0,0);
	v3set(r,0,1,2);
	c = v3cross(a, b);
	assertv3(c, r);
	free(c);
	printf("v3cross 3\n");
	v3set(a, 5,-2,1);
	v3set(b,6,-7,40);
	v3set(r,-73,-194,-23);
	c = v3cross(a, b);
	assertv3(c, r);
	free(c);
	printf("\e[32;1mDaijobu !\e[0m\n");
	
	printf("scale\n");
	v3set(a, 1,2,3);
	v3set(r, 3, 6, 9);
	v3scale(a, 3);
	assertv3(a, r);
	printf("\e[32;1mDaijobu !\e[0m\n");
	
	printf("v3dot 1\n");
	v3set(a, 1,2,3);
	v3set(b,1,5,7);
	assert(v3dot(a, b) == 32);
	printf("v3dot 2\n");
	v3set(a, -1,-2,3);
	v3set(b,4,0,-8);
	assert(v3dot(a, b) == -28);
	printf("v3dot 3\n");
	v3set(a, 1,0,0);
	v3set(b,0,1,0);
	assert(v3dot(a, b) == 0);
	printf("\e[32;1mDaijobu !\e[0m\n");

	printf("\e[32;1m==== END ====\e[0m\n");
}