/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alg_keep_searching.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: moana <moana@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 16:18:28 by moana         #+#    #+#                 */
/*   Updated: 2020/04/30 17:15:16 by mmarcell      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** -------------------------------------------------------------------------- **
** determines whether it is necessary to search for a new path
**
** params
**	t_graph *graph		struct holding all information about graph
**	t_vert *new_start	pointer to vertix which marks the start of the new
**						potential path
**
** return
**	TRUE
**	FALSE
*/

int		keep_searching(t_graph *graph, t_vert *new_start)
{
	return (graph->path_count < graph->ant_count && graph->ant_count >
		threshold(graph->paths, graph->path_count, new_start->distance));
}
