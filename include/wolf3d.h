/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <adubugra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 16:29:38 by adubugra          #+#    #+#             */
/*   Updated: 2018/05/06 18:20:34 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libft/libft.h"
# include "../miniLibX/mlx.h"
# include <math.h>
# include <stdio.h>
# define FOCAL_DISTANCE 10
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define SCALE 10

typedef	struct	s_pointers
{
	void			*mlx_ptr;
	void			*win_ptr;
	struct s_player	*player;
	struct s_grid	**grid;
}				t_pointers;

typedef struct	s_grid
{
	int				x;
	int				y;
	int				z;
	int				color;
	int				last;
	struct s_grid	*next;
}				t_grid;

/*
**x and y are the actual positions in the map
**dirx and diry are the direction the player is looking at
**planex and planey
*/
typedef struct	s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}				t_player;

typedef struct	s_ray
{
	double	camera;
	double	ray_x;
	double	ray_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
}				t_ray;

void			free_grid(t_grid **grid);
/*
**---------------------CONTROLLERS------------------
*/
int				on_click(int button, int x, int y, t_pointers *param);

int				on_key(int key, t_pointers *param);

int				exit_handler(t_pointers *pt);

void			rotate(t_pointers *pt, int order);

void			move(t_pointers *pt, int order);
/*
**---------------------GET_GRID------------------
*/
t_grid			**get_grid(char *file_name);

int				get_grid_height(char *file_name);

int				get_grid_width_and_split(char ***splitted_line, int fd);

t_grid			*construct_grid(int num_of_grids);
/*
**---------------------DRAWING------------------
*/
void			draw_line(t_pointers *p, t_grid *grid, int x2, int y2);

void			link_points(t_pointers *p, t_grid **grid);

int				find_max_height(t_grid **grid);

void			convert_to_3d(t_grid **grid);

/*
**---------------------CONSTRUCTORS------------------
*/
t_pointers		*create_pointers(t_grid **grid, t_player *player);

t_player		*create_player(int x, int y);

t_player		*set_player(int x, int y);

t_ray			*set_ray(t_ray *ray, t_player *player, int screen_x);

t_ray			*set_step_side_dist(t_ray *ray, t_player *player,
				int map_x, int map_y);
/*
**---------------------RENDER------------------
*/
void			render(t_player *player, t_grid **grid, t_pointers *p);

int				find_obstacles(t_ray *ray, int *map_x, int *map_y,
				t_grid **grid);

int				*set_height(t_player *player, int map[2],
				t_grid **grid, t_ray *ray);

void			set_color(t_grid *grid, t_ray *ray);

#endif
