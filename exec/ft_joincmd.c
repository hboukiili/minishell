/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joincmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukili <hboukili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:48:30 by iel-mach          #+#    #+#             */
/*   Updated: 2022/06/17 20:13:36 by hboukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_joincmd(t_parser *cmd)
{
	char	*join;
	char	**splt;
	int		i;

	i = 0;
	join = ft_strjoin_n(cmd->cmd, " ");
	join = ft_strjoin_s(join, cmd->opt);
	if (cmd->arg == NULL)
		return (ft_split(join, ' '));
	while (cmd->arg[i])
	{
		join = ft_strjoin(join, ' ');
		join = ft_strjoin_s(join, cmd->arg[i]);
		i++;
	}
	splt = ft_split(join, ' ');
	free (join);
	return (splt);
}

char	*get_home(char *str, char *s1)
{
	int	i;

	i = 0;
	while (g_f->old_env[i])
	{
		if (!ft_strncmp(g_f->old_env[i], str, 5))
			return (ft_substr(g_f->old_env[i], 5,
					ft_strlen(g_f->old_env[i]) - 5));
		i++;
	}
	printf("bash: %s: HOME not set\n", s1);
	return (NULL);
}

int	position_exit(t_parser *tmp)
{
	int	i;

	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->cmd, "exit", 4))
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (-1);
}

int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}
