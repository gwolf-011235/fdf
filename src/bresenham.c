/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 08:30:08 by gwolf             #+#    #+#             */
/*   Updated: 2023/03/03 12:04:00 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_pixel	ft_convert_pixel(t_vec3f point)
{
	t_pixel	ret;

	ret.x = point.x;
	ret.y = point.y;
	ret.color.a = (point.color >> 24) & 0xFF;
	ret.color.r = (point.color >> 16) & 0xFF;
	ret.color.g = (point.color >> 8) & 0xFF;
	ret.color.b = point.color & 0xFF;
	return (ret);	
}

void	ft_swap_pixel(t_pixel *one, t_pixel *two)
{
	t_pixel temp;

	temp = *one;
	*one = *two;
	*two = temp;
}

void ft_init_bresvars(t_bresvars *vars, t_pixel start, t_pixel end)
{
	vars->delta[X] = end.x - start.x;
    if (vars->delta[X] < 0)
		vars->delta[X] = -vars->delta[X];
	vars->delta[Y] = end.y - start.y;
	if (vars->delta[Y] < 0)
        vars->delta[Y] = -vars->delta[Y];
}

void gradient_line(t_pixel start, t_pixel end, t_bresvars vars, t_img *img)
{
    t_argb delta;

    delta.r = (end.color.r - start.color.r) << 8;
    delta.g = (end.color.g - start.color.g) << 8;
    delta.b = (end.color.b - start.color.b) << 8;


	if (vars.delta[Y] <= vars.delta[X])
	{
        /* We have a line with a slope between -1 and 1
         *
         * Ensure that we are always scan converting the line from left to
         * right to ensure that we produce the same line from P1 to P0 as the
         * line from P0 to P1.
         */
		if (end.x < start.x)
		{
			ft_swap_pixel(&start, &end);
			delta.r = -delta.r;
			delta.g = -delta.g;
			delta.b = -delta.b;
        }
		start.color.r <<= 8;
		start.color.g <<= 8;
		start.color.b <<= 8;

		if (end.y > start.y)
		{
			vars.line_incr = img->line_len;
		} 
		else
		{
			vars.line_incr = -img->line_len;
		}

        vars.decision = 2 * vars.delta[Y] - vars.delta[X];              /* Initial decision variable value  */
        vars.incr[0] = 2 * vars.delta[Y];               /* Increment to move to E pixel     */
        vars.incr[1] = 2 * (vars.delta[Y] - vars.delta[X]);       /* Increment to move to NE pixel    */

        delta.r /= vars.delta[X];
        delta.g /= vars.delta[X];
        delta.b /= vars.delta[X];

        /* Draw the first point at (x1,y1)  */
        vars.scr_pos = img->addr + (start.y * img->line_len + start.x * img->bytes);

        vars.scr_pos[1] = start.color.r >> 8;
        vars.scr_pos[2] = start.color.g >> 8;
        vars.scr_pos[3] = start.color.b >> 8;

        start.color.r += delta.r;
        start.color.g += delta.g;
        start.color.b += delta.b;

        /* Incrementally determine the positions of the remaining pixels */
		start.x++;
		while (start.x <= end.x)
		{
			vars.scr_pos += img->bytes;
			if (vars.decision < 0)
			{
				vars.decision += vars.incr[0];
			}
			else
			{
				vars.decision += vars.incr[1];
				vars.scr_pos += vars.line_incr;
			}
			vars.scr_pos[1] = start.color.r >> 8;
			vars.scr_pos[2] = start.color.g >> 8;
			vars.scr_pos[3] = start.color.b >> 8;

			start.color.r += delta.r;
			start.color.g += delta.g;
			start.color.b += delta.b;
			start.x++;
		}
	}
	else
    {
        /* We have a line with a slope between -1 and 1 (ie: includes
         * vertical lines). We must swap our x and y coordinates for this.
         *
         * Ensure that we are always scan converting the line from left to
         * right to ensure that we produce the same line from P1 to P0 as the
         * line from P0 to P1.
         */

		if (end.y < start.y)
		{
			ft_swap_pixel(&start, &end);
			delta.r = -delta.r;
			delta.g = -delta.g;
			delta.b = -delta.b;
        }

		start.color.r <<= 8;
		start.color.g <<= 8;
		start.color.b <<= 8;

		if (end.x > start.x)
		{
			vars.line_incr = img->bytes;
		} 
		else
		{
			vars.line_incr = -img->bytes;
		}

        vars.decision = 2 * vars.delta[X] - vars.delta[Y];              /* Initial decision variable value  */
        vars.incr[0] = 2 * vars.delta[X];               /* Increment to move to E pixel     */
        vars.incr[1] = 2 * (vars.delta[X] - vars.delta[Y]);       /* Increment to move to NE pixel    */

        delta.r /= vars.delta[Y];
        delta.g /= vars.delta[Y];
        delta.b /= vars.delta[Y];

        /* Draw the first point at (x1,y1)  */
        vars.scr_pos = img->addr + (start.y * img->line_len + start.x * img->bytes);

        vars.scr_pos[1] = start.color.r >> 8;
        vars.scr_pos[2] = start.color.g >> 8;
        vars.scr_pos[3] = start.color.b >> 8;

        start.color.r += delta.r;
        start.color.g += delta.g;
        start.color.b += delta.b;

        /* Incrementally determine the positions of the remaining pixels
         */
		start.y++;
		while (start.y <= end.y)
		{
			vars.scr_pos += img->line_len;
			if (vars.decision < 0)
			{
				vars.decision += vars.incr[0];
			}
			else
			{
				vars.decision += vars.incr[1];
				vars.scr_pos += vars.line_incr;
			}
			vars.scr_pos[1] = start.color.r >> 8;
			vars.scr_pos[2] = start.color.g >> 8;
			vars.scr_pos[3] = start.color.b >> 8;

			start.color.r += delta.r;
			start.color.g += delta.g;
			start.color.b += delta.b;
			start.y++;
		}
    }
}
