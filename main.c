
#include "Mini.h"

static void	process_input(char *input, t_minishell *minishell)
{
	t_token	*current;

	add_history(input);
	if (!fill_tokens(minishell, input))
	{
		ft_putstr("syntax error: unclosed quote\n", 2);
		free_tokens(minishell->token_list);
		return ;
	}
	if (!check_syntax_pipes(minishell->token_list))
	{
		free_tokens(minishell->token_list);
		return ;
	}
	current = minishell->token_list;
	while (current)
	{
		printf("Token: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
	minishell->command_list = parse_single_command(minishell);
	if (!minishell->command_list)
		return ;
	ft_execute(minishell);
	// free_minishell(minishell);
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

void	mini_loop(t_minishell *minishell)
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
			ft_putstr("\nLeaving...\n", 1);
			close(saved_stdin);
			free_minishell(minishell);
			break ;
		}
		if (g_status == SIGINT)
		{
			g_status = 0;
			free(input);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			continue ;
		}
		process_input(input, minishell);
		free(input);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

int	main(int argc, char **argv, char **env)
{
	char		**my_env;
	t_minishell	*minishell;

	(void)argv;
	if (argc != 1)
		exit_with_error("Too many arguments\n", 1, 1);
	minishell = init_minishell();
	if (!minishell)
	{
		free_minishell(minishell);
		return(1);
	}
	my_env = copy_env(env);
	minishell->env_list = create_env_list(my_env);
	do_signal();
	mini_loop(minishell);
	free(minishell);
	ft_freedoom(my_env);
	return (0);
}
