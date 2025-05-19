/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:53:14 by alejaro2          #+#    #+#             */
/*   Updated: 2025/05/19 19:30:02 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Mini.h"

volatile sig_atomic_t	g_status = 0;

void	sighandler(int signal)
{
	if (signal == SIGINT)
	{
		g_status = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	do_signal(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_handler(int signum)
{
	(void)signum;
	g_status = SIGINT;
	signal(SIGINT, SIG_DFL);
	exit(EXIT_FAILURE);
}
