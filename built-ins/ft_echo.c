#include "../Mini.h"

void	ft_echo(t_minishell *mini)
{
	int	new_line;
	int	i;
	int	j;

// empieza en 1 para evitar el comando y el salto de linea
	i = 1;
	new_line = 1;
	printf("hola echo \n");
	while (mini->command_list->argv[i] && !ft_strncmp(mini->command_list->argv[i], "-n", 2))
	{
		//empieza el 2 para saltar la primera n y comprobar
		//que el resto sea solo n
		j = 2;
		while (mini->command_list->argv[i][j] == 'n')
			j++;
		if (mini->command_list->argv[i][j] != '\0')
			break ;
		new_line = 0;
		i++;
	}
	while (mini->command_list->argv[i])
	{
		ft_putstr(mini->command_list->argv[i], 1);
		if (mini->command_list->argv[i + 1])
			ft_putstr(" ", 1);
		i++;
	}
	if (new_line)
		ft_putstr("\n", 1);
}

void	ft_echo_arg(char **argv)
{
	int	new_line;
	int	i;
	int	j;

// empieza en 1 para evitar el comando y el salto de linea
	i = 1;
	new_line = 1;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
	{
		//empieza el 2 para saltar la primera n y comprobar
		//que el resto sea solo n
		j = 2;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr(argv[i], 1);
		if (argv[i + 1])
			ft_putstr(" ", 1);
		i++;
	}
	if (new_line)
		ft_putstr("\n", 1);
}
