/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <adubugra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:11:18 by adubugra          #+#    #+#             */
/*   Updated: 2018/05/06 18:18:52 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	free_grid(t_grid **grid)
{
	int		i;
	int		j;

	j = 0;
	while (grid[j])
	{
		i = 0;
		while (grid[j][i].last == 0)
			i++;
		free(grid[j]);
		j++;
	}
	free(grid[j]);
}

int		main(int argc, char **argv)
{
	t_pointers	*ptrs;
	t_grid		**grid;
	t_player	*player;

	if (argc != 2)
	{
		ft_putstr("usage: ./wold3d [name_of_map]\n");
		return (1);
	}
	if ((grid = get_grid(argv[1])) == 0)
	{
		ft_putstr("Unknown file\n");
		return (1);
	}
	player = set_player(11, 22);
	ptrs = create_pointers(grid, player);
	render(player, grid, ptrs);
	mlx_key_hook(ptrs->win_ptr, on_key, ptrs);
	mlx_mouse_hook(ptrs->win_ptr, on_click, ptrs);
	mlx_hook(ptrs->win_ptr, 17, 0, exit_handler, ptrs);
	mlx_loop(ptrs->mlx_ptr);
	free(player);
	free(ptrs);
	free_grid(grid);
	return (0);
}
