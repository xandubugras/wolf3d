/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <adubugra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 11:57:16 by adubugra          #+#    #+#             */
/*   Updated: 2018/05/06 18:21:11 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"
#define UP 126
#define DOWN 125
#define RIGHT 124
#define LEFT 123
#define ESC 53
#define SPEED 0.4
#define ROT_SPEED 0.1

int		on_key(int key, t_pointers *pt)
{
	double		tmp;

	if (key == ESC)
	{
		mlx_destroy_window(pt->mlx_ptr, pt->win_ptr);
		pt->mlx_ptr = 0;
		free(pt->player);
		free_grid(pt->grid);
		free(pt);
		exit(0);
	}
	if (key == UP)
		move(pt, 1);
	if (key == DOWN)
		move(pt, -1);
	if (key == RIGHT)
		rotate(pt, -1);
	if (key == LEFT)
		rotate(pt, 1);
	return (1);
}

int		on_click(int button, int x, int y, t_pointers *pt)
{
	return (0);
}

int		exit_handler(t_pointers *pt)
{
	mlx_destroy_window(pt->mlx_ptr, pt->win_ptr);
	pt->mlx_ptr = 0;
	free(pt->player);
	free_grid(pt->grid);
	free(pt);
	exit(0);
	return (1);
}

void	rotate(t_pointers *pt, int order)
{
	double tmp;

	tmp = pt->player->dir_x;
	pt->player->dir_x = pt->player->dir_x * cos(order * ROT_SPEED) -
						pt->player->dir_y * sin(order * ROT_SPEED);
	pt->player->dir_y = tmp * sin(order * ROT_SPEED) +
						pt->player->dir_y * cos(order * ROT_SPEED);
	tmp = pt->player->plane_x;
	pt->player->plane_x = pt->player->plane_x * cos(order * ROT_SPEED) -
						pt->player->plane_y * sin(order * ROT_SPEED);
	pt->player->plane_y = tmp * sin(order * ROT_SPEED) +
						pt->player->plane_y * cos(order * ROT_SPEED);
	render(pt->player, pt->grid, pt);
}

void	move(t_pointers *pt, int order)
{
	if (pt->grid[(int)(pt->player->x + order * pt->player->dir_x * SPEED)]
	[(int)pt->player->y].z == 0)
		pt->player->x += order * pt->player->dir_x * SPEED;
	if (pt->grid[(int)pt->player->x][(int)(pt->player->y + order *
	pt->player->dir_y * SPEED)].z == 0)
		pt->player->y += order * pt->player->dir_y * SPEED;
	render(pt->player, pt->grid, pt);
}
