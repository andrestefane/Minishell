#include "../Mini.h"

char *extract_token_aux(char *input, int *index, t_token_type *type, t_token_type prev_type)
{
    int start;
    int len;
    char *token;

    start = *index;
    len = 0;
    *type = get_operator_type(input, *index, &len);
    if (*type != T_WORD)
    {
        *index = *index + len;
        token = ft_substr(input, start, len);
        return (token);
    }
    if (prev_type == T_RED_IN || prev_type == T_HEREDOC)
        *type = T_INFILE;
    if (prev_type == T_RED_OUT || prev_type == T_RED_APPEND)
        *type = T_OUTFILE;
    return (extract_word(input, index, start));
}

int fill_tokens(t_token **token_list, char *input)
{
    int index;
    t_token_type type;
    t_token_type prev_type;
    char *token;

    index = 0;
    prev_type = T_WORD;
    while (input[index])
    {
        token = extract_token(input, &index, &type, prev_type);
        if (!token)
            break;
        add_token(token_list, token, type);
        free(token);
        prev_type = type;
    }
    return (1);
}


t_token_type get_operator_type(char *input, int i, int *len)
{
    if (!input || input[i] == '\0')
    {
        *len = 0;
        return (T_WORD);
    }
    if (input[i] == '|')
    {
        *len = 1;
        return (T_PIPE);
    }
    if (input[i] == '<' && input[i + 1] == '<')
    {
        *len = 2;
        return (T_HEREDOC);
    }
    if (input[i] == '>' && input[i + 1] == '>')
    {
        *len = 2;
        return (T_RED_APPEND);
    }
    if (input[i] == '<')
    {
        *len = 1;
        return (T_RED_IN);
    }
    if (input[i] == '>')
    {
        *len = 1;
        return (T_RED_OUT);
    }
    *len = 0;
    return (T_WORD);
}
