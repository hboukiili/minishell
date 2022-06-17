/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukili <hboukili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:44:13 by hboukili          #+#    #+#             */
/*   Updated: 2022/06/17 23:49:10 by hboukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_env(char *ev, t_p *s)
{
	while (s->string[s->i] != '"' && s->string[s->i] != '\''
		&& s->string[s->i] != '$')
	{
		if ((s->string[s->i] >= 'a' && s->string[s->i] <= 'z')
			|| (s->string[s->i] >= 'A' && s->string[s->i] <= 'Z')
			|| (s->string[s->i] >= '0' && s->string[s->i] <= '9')
			|| s->string[s->i] == '_')
			ev = ft_strjoin(ev, s->string[s->i++]);
		else
			break ;
	}
	ev = ft_strjoin(ev, '=');
	return (ev);
}

int	count_pipes(char *s)
{
	int	i;
	int	x;

	x = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '"'
				&& s[i] != '\'')
				i++;
			if (s[i] != '\0')
				i++;
		}
		if (s[i] == '|')
			x++;
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (x);
}

char	*dollar_check(t_p *s, char *str, int x)
{
	char	*tmp1;

	if (s->string[++s->i] == '?')
	{
		tmp1 = ft_itoa(g_f->p);
		str = ft_strjoin_s(str, tmp1);
		free(tmp1);
		s->i++;
	}
	else if (ft_isdigit(s->string[s->i]))
	{
		s->i++;
		str = ft_strjoin(str, '\0');
	}
	else if (s->string[s->i] == '$')
	{
		s->i++;
		str = ft_strjoin(str, '\0');
	}
	else if (ft_isalpha(s->string[s->i])
		|| s->string[s->i] == '_')
		str = get_env(s, str, x);
	else
		str = ft_strjoin(str, '$');
	return (str);
}

void	free_env(void)
{
	int	i;

	i = 0;
	while (g_f->old_env[i])
	{
		free(g_f->old_env[i]);
		i++;
	}
	free(g_f->old_env);
}
