#include "../incl/minishell.h"

void	type_token(t_token_chain *token_node, char *type)
{
	int	i;

	i = 0;
	while (i != 3)
	{
		token_node->type[i] = type[i];
		i++;
	}
}

int	is_builtin(char *token, t_data *data)
{
	int	i;

	i = 0;
	while (i != 7)
	{
		if (str_comp(token, data->builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_env_var(char *token)
{
	if (token[0] == '$' && token[1] != '?')
		return (1);
	return (0);
}

int	is_last_pipe_exit(char *token)
{
	if (token[0] == '$' && token[1] == '?' && !token[2])
		return (1);
	return (0);
}

void	prog_arg_fix(t_data *data)
{
	t_token_chain	*current;
	char			pr_ar;

	current = data->token_chain->next;
	pr_ar = 0;
	while (current)
	{
		if ((str_comp(current->type, "pr") || str_comp(current->type, "bu")) && !pr_ar)
		{
			pr_ar = 1;
			current = current->next;
		}
		while (current && pr_ar && (str_comp(current->type, "pr") || str_comp(current->type, "bu")))
		{
			type_token(current, "ar");
			current = current->next;
		}
		if (current && pr_ar && !(str_comp(current->type, "pr") || str_comp(current->type, "bu")))
			pr_ar = 0;
		if (current)
			current = current->next;
	}
}

void	type_token_chain(t_data *data)
{
	t_token_chain	*current;

	current = data->token_chain->next;
	while (current)
	{
		if (is_builtin(current->token, data))
			type_token(current, "bu");
		else if (get_cmd_path(current->token, data))
			type_token(current, "pr");
		else if (str_comp(current->token, "|"))
			type_token(current, "pi");
		else if (str_comp(current->token, "<"))
			type_token(current, "ri");
		else if (str_comp(current->token, ">"))
			type_token(current, "ro");
		else if (str_comp(current->token, "<<"))
			type_token(current, "rd");
		else if (str_comp(current->token, ">>"))
			type_token(current, "ra");
		else if (is_last_pipe_exit(current->token))
			type_token(current, "es");
		else if (is_env_var(current->token))
			type_token(current, "ev");
		else if (str_comp(current->token, "\""))
			type_token(current, "dq");
		else if (str_comp(current->token, "\'"))
			type_token(current, "sq");
		else
			type_token(current, "ar");
		current = current->next;
	}
	prog_arg_fix(data);
}
