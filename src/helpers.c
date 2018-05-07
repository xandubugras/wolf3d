/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubugra <adubugra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 20:49:13 by adubugra          #+#    #+#             */
/*   Updated: 2018/05/06 16:45:23 by adubugra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/wolf3d.h>

t_grid	*construct_grid(int num_of_grids)
{
	t_grid	*grid;
	int		i;

	grid = malloc(sizeof(t_grid) * num_of_grids);
	i = 0;
	while (i < num_of_grids)
	{
		grid[i].x = 0;
		grid[i].y = 0;
		grid[i].z = 0;
		grid[i].last = 0;
		grid[i].color = 0;
		i++;
	}
	return (grid);
}
