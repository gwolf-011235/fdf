#include "fdf.h"

void	test(void)
{
	t_mat4 cam2world;

	t_point up = {0, 1, 0, 0};
	t_point from = {1, 1, 1, 0};
	t_point to = {0, 0, 0, 0};

	lookat(from, to, up, cam2world);
}
