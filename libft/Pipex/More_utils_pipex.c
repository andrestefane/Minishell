/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   More_utils_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:23:57 by astefane          #+#    #+#             */

/*   Updated: 2025/05/01 18:39:21 by alejaro2         ###   ########.fr       */

/*   Updated: 2025/05/01 18:28:01 by astefane         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	handle_input_redirection(t_token **tmp, t_pipex *data)
{
	if ((*tmp)->type == T_HEREDOC)
		data->heredoc = 1;
	else
		data->heredoc = 0;
	if ((*tmp)->next)
		data->limiter = (*tmp)->next->value;
	*tmp = (*tmp)->next;
	if (*tmp)
		*tmp = (*tmp)->next;
}
