/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmarcell <mmarcell@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 14:09:39 by mmarcell       #+#    #+#                */
/*   Updated: 2020/02/26 14:39:34 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		exit_function(t_room ***graph)
{
	free_graph(graph);
	return (0);
}

int		main(void)
{
	t_room			**graph;
	unsigned int	ant_no;

	graph = 0;
	ant_no = 0;
	if (read_input(&graph, &ant_no) == 0)
		return (exit_function(&graph));
	return (0);
}
