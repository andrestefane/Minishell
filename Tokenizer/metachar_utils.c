#include "../Mini.h"

static int  extract_double_metachar(t_tokenizer *tok,
                                    t_token_type *type)
{
    char c;

    c = tok->input[tok->pos];
    if ((c == '>' && tok->input[tok->pos + 1] == '>')
     || (c == '<' && tok->input[tok->pos + 1] == '<'))
    {
        if (c == '>')
            *type = T_RED_APPEND;
        else
            *type = T_HEREDOC;
        tok->pos += 2;
        return (1);
    }
    return (0);
}

static int  extract_single_metachar(t_tokenizer *tok,
                                    t_token_type *type)
{
    char c;

    c = tok->input[tok->pos];
    if (c == '|')
        *type = T_PIPE;
    else if (c == '>')
        *type = T_RED_OUT;
    else if (c == '<')
        *type = T_RED_IN;
     else if (c == '$')
        *type = T_DOLLAR;
    else if (c == '?')
        *type = T_QUESTION;
    else
        return (0);
    tok->pos++;
    return (1);
}

int  extract_metachar(t_tokenizer *tok,
                      t_token_type *type,
                      t_token_quote *quote)
{
    *quote = Q_NONE;
    if (extract_double_metachar(tok, type))
        return (1);
    if (extract_single_metachar(tok, type))
        return (1);
    return (0);
}

