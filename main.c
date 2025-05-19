
#include "Mini.h"

static void	process_input(char *input, char **env)
{
	t_token	*list;
	t_token	*current;
	t_command	*cmd;

	list = NULL;
	add_history(input);
	if (!fill_tokens(&list, input))
	{
		ft_putstr("syntax error: unclosed quote\n", 2);
		free_tokens(list);
		return ;
	}
	if (!check_syntax_pipes(list))
	{
		free_tokens(list);
		return ;
	}
	current = list;
	while (current)
	{
		printf("Token: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
	cmd = parse_single_command(list);
	if (!cmd)
		return ;
	ft_execute(list, env);
	free_tokens(list);
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

void	mini_loop(char **env)
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
		process_input(input, env);
		free(input);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**my_env;

	(void)argv;
	if (argc != 1)
		exit_with_error("Too many arguments\n", 1, 1);
	my_env = copy_env(env);
	do_signal();
	mini_loop(my_env);
	ft_freedoom(my_env);
	return (0);
}
