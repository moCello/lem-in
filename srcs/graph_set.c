/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graph_set.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: moana <moana@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/27 17:47:58 by moana          #+#    #+#                */
/*   Updated: 2020/03/30 17:49:59 by moana         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"
#include <stdlib.h>

/* 
// depending on the algorithm, this might not be necessary
static void	is_duplicate(t_edge *new_edge, t_vert *vert)
{
	t_edge	**walk;

	*walk = vert->connections;
	while ((*walk) != NULL)
	{
		if ((*walk)->head == new_edge->head)
			return (TRUE);
		(*walk) = (*walk)->next_conn;
	}
	return (FALSE);
}
 */

static void	edge_set(t_edge *edge, t_graph *graph)
{
	edge->invert->tail = edge->head;
	edge->invert->head = edge->tail;
	edge->next_edge = graph->edge_list;
	graph->edge_list = edge;
	edge->next_conn = edge->tail->connections;
	edge->tail->connections = edge;
	edge->invert->next_conn = edge->invert->tail->connections;
	edge->invert->tail->connections = edge->invert;	
}

static int	edge_new(char **input_line, t_graph *graph)
{
	t_edge  *edge;
	t_edge  *edge_invert;

	edge = (t_edge*)ft_memalloc(sizeof(t_edge));
	if (edge == NULL || input_line[0] == NULL || input_line[1] == 0
		|| input_line[2] != 0)
		return (ERROR);
	edge_invert = (t_edge*)ft_memalloc(sizeof(t_edge));
	if (edge_invert == NULL)
	{
		free(edge);
		return (ERROR);
	}
	edge->invert = edge_invert;
	edge_invert->invert = edge;
	edge->tail = hmap_get(graph->vertices, input_line[0]);
	edge->head = hmap_get(graph->vertices, input_line[1]);
	if (edge->tail == NULL || edge->head == NULL
		/* || is_duplicate(edge, edge->tail) == TRUE */)
	{
		edge_del(&edge);
		return (ERROR);
	}
	edge_set(edge, graph);
	ft_strarrdel(&input_line);
	return (OK);
}

static int	vert_new(char **input_line, t_graph *graph)
{
	t_vert		*vert;

	vert = (t_vert*)ft_memalloc(sizeof(t_vert));
	if (vert == 0 || input_line == 0 || *input_line == 0 ||
		input_line[1] == 0 || ft_isint(input_line[1]) == 0 ||
		input_line[2] == 0 || ft_isint(input_line[2]) == 0 ||
		input_line[3] != 0)
		return (ERROR);
	vert->name = ft_strdup(input_line[0]);
	vert->x_coord = ft_atoi(input_line[1]);
	vert->y_coord = ft_atoi(input_line[2]);
	vert->distance = -1;
	vert->next_vert = graph->vert_list;
	graph->vert_list = vert;
	if (hmap_set(graph->vertices, vert->name, vert) != 0)
		return (ERROR);
	ft_strarrdel(&input_line);
	return (OK);
}

int		graph_set(t_graph *graph, t_input_info *input)
{
	t_input_line	*walk;

	if (graph == NULL || input == NULL)
		return (ERROR);
	graph->vertices = hmap_new(input->room_count);
	if (graph->vertices == NULL)
		return (ERROR);
	walk = input->rooms;
	while (walk != NULL)
	{
		if (vert_new(ft_strsplit(walk->line, ' '), graph) == ERROR)
			return (ERROR);
		walk = walk->next_room;
	}
	graph->source = hmap_get(graph->vertices, input->start->room_name);
	graph->sink = hmap_get(graph->vertices, input->end->room_name);
	walk = input->links;
	while (walk != NULL)
	{
		if (walk->line[0] == '-' || walk->line[ft_strlen(walk->line) - 1] == '-'
			|| edge_new(ft_strsplit(walk->line, '-'), graph) == ERROR)
			return (ERROR);
		walk = walk->next_link;
	}
	return (OK);
}