
#include "Mini.h"

int g_exit_status = 0;

static void	process_input(char *input, char **env)
{
	t_token		*list;
	t_token		*current;
	t_command	*cmd;

	list = NULL;
	add_history(input);
	if (!fill_tokens(&list, input))
	{
		free_tokens(list);
		exit_with_error("Tokenization failed\n", 1, 1);
	}
	current = list;
	while (current)
	{
		printf("Token: %s, Type: %d\n", current->value, current->type);
		current = current->next;
	}
	cmd = parse_single_command(list);
	pipex(list, env);
	free_commands(cmd);
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

void	mini_loop(char **my_env)
{
	char	*pront;
	char	*input;
	int		saved_input;

	while (1)
	{
		saved_input = dup(STDIN_FILENO);
		pront = get_prompt();
		input = readline(pront);
		free(pront);
		if (!input)
		{
			ft_putstr("\nLeaving...\n", 1);
			break ;
		}
		process_input(input, my_env);
		free(input);
		dup2(saved_input, STDIN_FILENO);
		close(saved_input);
	}
	close(saved_input);
}

int	main(int argc, char **argv, char **env)
{
	char	**my_env;

	(void)argv;
	if (argc != 1)
		exit_with_error("Alot of arguments\n", 1, 1);
	my_env = copy_env(env);
	mini_loop(my_env);
	ft_freedoom(my_env);
	return (0);
}

/* 	for (int i = 0; my_env[i]; i++)
		printf("%s\n", my_env[i]); */