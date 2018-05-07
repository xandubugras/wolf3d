/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <adubugra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 16:55:19 by adubugra          #+#    #+#             */
/*   Updated: 2018/05/06 17:19:51 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	render(t_player *player, t_grid **grid, t_pointers *p)
{
	t_ray	*ray;
	int		map[2];
	int		x;
	int		*height;

	ray = 0;
	x = 0;
	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	while (x < WIN_WIDTH)
	{
		map[0] = (int)player->x;
		map[1] = (int)player->y;
		ray = set_ray(ray, player, x);
		set_step_side_dist(ray, player, map[0], map[1]);
		find_obstacles(ray, &map[0], &map[1], grid);
		height = set_height(player, map, grid, ray);
		set_color(&(grid[map[0]][map[1]]), ray);
		grid[map[0]][map[1]].x = x;
		draw_line(p, &(grid[map[0]][map[1]]), x, height[1]);
		free(height);
		x++;
	}
	if (ray)
		free(ray);
}

int		find_obstacles(t_ray *ray, int *map_x, int *map_y, t_grid **grid)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			*map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			*map_y += ray->step_y;
			ray->side = 1;
		}
	if (grid[*map_x][*map_y].z > 0)
		break;
	}
	return (ray->side);
}

int		*set_height(t_player *player, int map[2], t_grid **grid, t_ray *ray)
{
	double	perp_wall_dist;
	int		line_height;
	int		*height;

	height = malloc(sizeof(int) * 2);
	if (ray->side == 0)
		perp_wall_dist = (map[0] - player->x + (1 - ray->step_x) / 2) / ray->ray_x;
	else
		perp_wall_dist = (map[1] - player->y + (1 - ray->step_y) / 2) / ray->ray_y;
	line_height = (int)(WIN_HEIGHT / perp_wall_dist);
	height[0] = -line_height / 2 + WIN_HEIGHT / 2;
	if(height[0] < 0)
		height[0] = 0;
	height[1] = line_height / 2 + WIN_HEIGHT / 2;
	if(height[1] >= WIN_HEIGHT)
		height[1] = WIN_HEIGHT - 1;
	grid[map[0]][map[1]].y = height[0];
	return (height);
}


void	set_color(t_grid *grid, t_ray *ray)
{
	int	color;

	if (grid->z == 0)
		color = 0x000000;
	else if (grid->z == 1)
		color = 0x39ff14;
	else if (grid->z == 2)
		color = 0x111e6c;
	else if (grid->z == 3)
		color = 0xed2939;
	else if (grid->z == 4)
		color = 0xfc0fc0;
	if (ray->side == 1)
		color = ft_return_mod(color - 55);
	grid->color = color;
}