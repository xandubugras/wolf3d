/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <adubugra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 20:34:03 by adubugra          #+#    #+#             */
/*   Updated: 2018/05/06 17:20:18 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

t_pointers	*create_pointers(t_grid **grid, t_player *player)
{
	t_pointers	*ptrs;

	ptrs = malloc(sizeof(t_pointers));
	ptrs->mlx_ptr = mlx_init();
	ptrs->win_ptr = mlx_new_window(ptrs->mlx_ptr, WIN_WIDTH, WIN_HEIGHT,
															"wolf3d");
	ptrs->player = player;
	ptrs->grid = grid;
	return (ptrs);
}

t_player	*set_player(int x, int y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->x = x;
	player->y = y;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	return (player);
}

t_ray		*set_step_side_dist(t_ray *r, t_player *pl, int map_x, int map_y)
{
	if (r->ray_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (pl->x - map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (map_x + 1.0 - pl->x) * r->delta_dist_x;
	}
	if (r->ray_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (pl->y - map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (map_y + 1.0 - pl->y) * r->delta_dist_y;
	}
	return (r);
}

t_ray		*set_ray(t_ray *ray, t_player *player, int screen_x)
{
	if (!ray)
		ray = malloc(sizeof(t_ray));
	ray->camera = 2 * screen_x / (double)WIN_WIDTH - 1;
	ray->ray_x = player->dir_x + player->plane_x * ray->camera;
	ray->ray_y = player->dir_y + player->plane_y * ray->camera;
	ray->delta_dist_x = fabs(1 / ray->ray_x);
	ray->delta_dist_y = fabs(1 / ray->ray_y);
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	return (ray);
}
