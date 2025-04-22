/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:37:01 by astefane          #+#    #+#             */
/*   Updated: 2025/04/22 16:23:52 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mini.h"

int main(int argc, char **env)
{
    char *input;
    int index;
    t_token_type type;
    char *token;

    (void)env;
    if (argc != 1)
        exit_with_error("Alot of arguments\n", 1);
    while (1)
    {
        input = readline("Minishell> ");
        if (!input)
        {
            ft_putstr("\nLeaving...\n");
            break;
        }
        if (*input)
        {
            add_history(input);
            index = 0;
            while (input[index])
            {
                token = extract_token(input, &index, &type);
                if (!token)
                    break;
                printf("Token: %s, Type: %d, Index: %d\n", token, type, index);
                free(token);
            }
        }
        free(input);
    }
    return (0);
}
