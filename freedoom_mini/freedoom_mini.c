#include "../Mini.h"

void	free_minishell(t_minishell *m)
{
	if (!m)
		return ;
	if (m->env_list)
	{
		free_env_list(m->env_list);
		m->env_list = NULL;
	}
	if (m->t_list)
	{
		free_t_list(m->t_list);
		m->t_list = NULL;
	}
	if (m->command_list)
	{
		/* Sólo liberamos command_list si no coincide con pipex_data->commands.
			Esto evita doble‐free cuando ‘command_list’ y ‘pipex_data->commands’
			apuntan al mismo bloque. */
		if (!(m->pipex_data && m->command_list == m->pipex_data->commands))
		{
			free_command_list(m->command_list);
		}
		m->command_list = NULL;
	}
	if (m->pipex_data)
	{
		free_pipex_data(m->pipex_data);
		m->pipex_data = NULL;
	}
	if (m->tokenizer)
	{
		free_tokenizer(m->tokenizer);
		m->tokenizer = NULL;
	}
	/* curr_token, new_token, new_node, current, head, tmp y curr apuntan
		a nodos dentro de t_list o command_list, así que ya quedaron liberados
		cuando borramos las listas. Sólo dejamos en NULL para evitar uso tras free: */
	m->curr_token = NULL;
	m->new_token = NULL;
	m->new_node = NULL;
	m->current = NULL;
	m->head = NULL;
	m->tmp = NULL;
	m->curr = NULL;
}

void	free_tokenizer(t_tokenizer *tok)
{
	if (!tok)
		return ;
	free(tok);
}
void	free_and_reset_token_list(t_minishell *mini)
{
	if (!mini)
		return ;
	if (mini->t_list)
	{
		free_t_list(mini->t_list);
		mini->t_list = NULL;
	}
}
