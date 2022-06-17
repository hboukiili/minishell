/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mycmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboukili <hboukili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:53:02 by iel-mach          #+#    #+#             */
/*   Updated: 2022/06/17 20:02:45 by hboukili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	herdoc_n(t_parser *cmd, int *fd)
{
	int	fd0;

	g_f->flg = 1;
	ft_herdoc(cmd, cmd->rdr->fd);
	if (g_f->flg == -1)
	{
		dup(g_f->fdex);
		return (0);
	}
	g_f->flg = 0;
	dup(g_f->fdex);
	fd0 = open("/tmp/herdoc", O_RDONLY, 0644);
	fd[0] = fd0;
	return (1);
}

void	open_der(t_parser *cmd, int *fd)
{
	t_rdr	*tmp;

	while (cmd->rdr)
	{
		if (cmd->rdr->type == 2)
		{
			fd[0] = cmd->rdr->fd;
			if (fd[0] == -1)
				printf("my minishell: %s: No such file or directory\n",
					cmd->rdr->rdr_value);
		}
		if (cmd->rdr->type == 0 || cmd->rdr->type == 1)
			fd[1] = cmd->rdr->fd;
		if (cmd->rdr->type == 3)
			if (!herdoc_n(cmd, fd))
				break ;
		tmp = cmd->rdr;
		free(cmd->rdr->rdr_value);
		cmd->rdr = cmd->rdr->next;
		free(tmp);
	}
}

void	wait_function(t_parser *cmd)
{
	t_parser	*tmp;

	tmp = cmd;
	while (tmp)
	{
		wait(&g_f->exit_code);
		if (WIFEXITED(g_f->exit_code))
			g_f->p = WEXITSTATUS (g_f->exit_code);
		if (g_f->exit_code > 255)
			g_f->exit_code /= 255;
		if (g_f->exit_code == 256)
			g_f->exit_code = 255;
		else if (g_f->exit_code == 2)
			g_f->p = 130;
		else if (g_f->exit_code == 3)
			g_f->p = 131;
		if (g_f->flg == -1)
			g_f->p = 1;
		tmp = tmp ->next;
	}
}

int	ft_mycmd_2(t_child *t, t_parser *tmp, t_parser *cmd)
{
	if ((!ft_strncmp(tmp->cmd, "cd", 2) && ft_strlen(tmp->cmd) == 2)
		&& tmp->next == NULL)
		cd_cmd(tmp);
	else if ((!ft_strncmp(tmp->cmd, "export", 6) && ft_strlen(tmp->cmd) == 6)
		&& cmd->next == NULL)
	{
		if (tmp->opt != NULL || tmp->arg != NULL)
			export1(tmp);
		else if (tmp->opt == NULL && tmp->arg == NULL)
			export3();
	}
	else if ((!ft_strncmp(tmp->cmd, "unset", 4) && ft_strlen(tmp->cmd) == 5)
		&& cmd->next == NULL)
		unset1(tmp);
	else if ((!ft_strncmp(tmp->cmd, "exit", 4) && ft_strlen(tmp->cmd) == 4
			&& !position_exit(cmd)))
	{
		if (exit_0(tmp) == 1)
			return (1);
	}
	else
		ft_child(t, tmp);
	return (0);
}

int	ft_mycmd(t_parser *cmd)
{
	t_parser	*tmp;
	t_child		*t;

	t = malloc(sizeof(t_child));
	t->in = 0;
	t->out = 1;
	cmd->env = g_f->old_env;
	tmp = cmd;
	while (tmp)
	{
		if (ft_mycmd_2(t, tmp, cmd) == 1)
			return (1);
		tmp = tmp->next;
	}
	if (cmd->next)
		close(t->fd[0]);
	wait_function(cmd);
	free(t);
	return (0);
}
