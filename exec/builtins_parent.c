/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukili <hboukili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 02:37:16 by hboukili          #+#    #+#             */
/*   Updated: 2022/06/17 03:49:03 by hboukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_cmd(t_parser *tmp)
{
	getcwd(g_f->oldpwd, sizeof(g_f->oldpwd));
	if (tmp->arg == NULL || (!ft_strncmp(tmp->arg[0], "#", 1) \
		&& ft_strlen(tmp->arg[0]) == 1) || (!ft_strncmp(tmp->arg[0], "~", 1) \
		&& ft_strlen(tmp->arg[0]) == 1))
	{
		getcwd(g_f->oldpwd, sizeof(g_f->oldpwd));
		if (chdir(get_home("HOME=", tmp->cmd)) == -1)
			g_f->p = 1;
		getcwd(g_f->pwd, sizeof(g_f->pwd));
		g_f->old_env = edit_ev(g_f->old_env, g_f->pwd, g_f->oldpwd);
	}
	else if (chdir(tmp->arg[0]) == -1)
	{
		perror (tmp->arg[0]);
		g_f->p = 1;
	}
	getcwd(g_f->pwd, sizeof(g_f->pwd));
	g_f->old_env = edit_ev(g_f->old_env, g_f->pwd, g_f->oldpwd);
}
