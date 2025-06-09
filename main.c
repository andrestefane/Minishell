/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:45:06 by astefane          #+#    #+#             */
/*   Updated: 2025/06/09 14:45:07 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mini.h"

void	print_token_list(t_token *head)
{
	int	i;

	i = 0;
	if (!head)
	{
		printf("Token list is empty.\n");
		return ;
	}
	while (head)
	{
		printf("Token %d:\n", i);
		if (!head)
		{
			printf("  Invalid head pointer\n");
			break ;
		}
		if (!head->value)
			printf("  value: (null)\n");
		else
			printf("  value: %s\n", head->value);
		printf("  type: %d\n", head->type);
		printf("  quote: %d\n", head->quote);
		printf("  expansion: %d\n", head->expansion_type);
		head = head->next;
		i++;
	}
}

static void	process_input(char *input, t_minishell *minishell)
{
	char	*status_str;

	add_history(input);
	g_status = 0;
	if (!fill_tokens(minishell, input))
	{
		ft_putstr("syntax error: unclosed quote\n", 2);
		free_t_list(minishell->t_list);
		minishell->t_list = NULL;
		return ;
	}
	if (!check_syntax_pipes(minishell->t_list))
	{
		free_t_list(minishell->t_list);
		minishell->t_list = NULL;
		return ;
	}
	ft_execute(minishell);
	status_str = ft_itoa(g_status);
	add_env_node(minishell, "?", status_str, 1);
	free(status_str);
}

char	*get_prompt(void)
{
	char	*cwd;
	char	*pront;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		pront = ft_strdup("Minishell> ");
	else
	{
		pront = ft_strjoin(cwd, " Minishell> ");
		free(cwd);
	}
	return (pront);
}

void	mini_loop(t_minishell *mini)
{
	char	*prompt;
	char	*input;
	int		saved_stdin;

	while (1)
	{
		saved_stdin = dup(STDIN_FILENO);
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			(free_env_list(mini->env_list),
				free_tokenizer(mini->tokenizer), free_tokens(mini->t_list),
				close(saved_stdin), free_pipex_data(mini->pipex_data));
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			continue ;
		}
		if (g_status == 128 + SIGINT)
		{
			g_status = 0;
			free(input);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			continue ;
		}
		process_input(input, mini);
		free(input);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

int	main(int argc, char **argv, char **env)
{
	char		**my_env;
	t_minishell	minishell;
	char		*status_str;

	(void)argv;
	if (argc != 1)
		exit_with_error("Too many arguments\n", 1, 1);
	minishell = init_minishell();
	my_env = copy_env(env);
	minishell.env_list = create_env_list(my_env, &minishell);
	status_str = ft_itoa(g_status);
	add_env_node(&minishell, "?", status_str, 1);
	ft_freedoom(my_env);
	free(status_str);
	do_signal();
	mini_loop(&minishell);
	return (0);
}
