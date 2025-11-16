/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_coll_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:48:22 by monabati          #+#    #+#             */
/*   Updated: 2025/11/05 05:14:30 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_garbage	*garbage_last_node(t_garbage *garbage)
{
	t_garbage	*tmp;

	if (!garbage)
		return (NULL);
	tmp = garbage;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

static void	garbage_add_back(t_garbage **garbage, t_garbage *node)
{
	t_garbage	*tmp;

	if (garbage == NULL)
		return ;
	if (*garbage == NULL)
	{
		*garbage = node;
		return ;
	}
	else
	{
		tmp = garbage_last_node(*garbage);
		tmp->next = node;
	}
}

void	*ft_malloc(size_t size, t_garbage **garb_lst)
{
	t_garbage	*tmp;

	tmp = NULL;
	tmp = malloc(sizeof(t_garbage));
	if (!tmp)
	{
		perror("malloc");
		return (NULL);
	}
	tmp->value = malloc(size);
	if (!tmp->value)
		perror("malloc");
	tmp->next = NULL;
	garbage_add_back(garb_lst, tmp);
	return (tmp->value);
}
