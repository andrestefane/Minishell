
#include "Mini.h"

static void	process_input(char *input, t_minishell *minishell, char **env)
{
	t_token	*current;
	char	*status_str;
	char	**my_env;

	add_history(input);
	my_env = copy_env(env);
	minishell->env_list = create_env_list(my_env);
	ft_freedoom(my_env);
	g_status = 0;
	if (!fill_tokens(minishell, input))
	{
		ft_putstr("syntax error: unclosed quote\n", 2);
		free_token_list(minishell->token_list);
		minishell->token_list = NULL;
		return ;
	}
	if (!check_syntax_pipes(minishell->token_list))
	{
		free_token_list(minishell->token_list);
		minishell->token_list = NULL;
		return ;
	}
	current = minishell->token_list;
	ft_execute(minishell);
	if (minishell->pipex_data)
	{
		free_pipex_data(minishell->pipex_data);
		minishell->pipex_data = NULL;
		minishell->command_list = NULL;
	}
	if (minishell->token_list)
	{
		free_token_list(minishell->token_list);
		minishell->token_list = NULL;
	}
	status_str = ft_itoa(g_status);
	add_env_node(&minishell->env_list, "?", status_str, 1);
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

void	mini_loop(t_minishell *minishell, char **env)
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
			close(saved_stdin);
			break ;
		}
		if (input[0] == '\0') // Enter vacío
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
		process_input(input, minishell, env);
		free(input);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argv;
	if (argc != 1)
		exit_with_error("Too many arguments\n", 1, 1);
	ft_bzero(&minishell, sizeof(t_minishell));
	do_signal();
	mini_loop(&minishell, env);
	return (0);
}
