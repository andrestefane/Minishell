/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:50:06 by astefane          #+#    #+#             */
/*   Updated: 2025/04/30 19:50:29 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_outfile(t_pipex *data, t_token *token)
{
	t_token	*last;

	last = token;
	while (last && last->next)
		last = last->next;

	if (!last || !last->value)
		free_struct(data, ERRO_OUFILE, 1, 2);

	if (data->heredoc == 1)
		data->outfile = open(last->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		data->outfile = open(last->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);

	if (data->outfile == -1)
		free_struct(data, ERRO_OUFILE, 1, 2);
}
