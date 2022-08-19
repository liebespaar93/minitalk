/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:08:18 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 14:54:59 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_kill.h>
#include <signal.h>

int	ft_kill_set(t_pid_list *pid_list, int sig)
{
	if (!pid_list)
		return (0);
	pid_list->last_kill_pid = pid_list->pid;
	pid_list->last_kill_sig = sig;
	g_pid_list->last_kill_pid = pid_list->pid;
	g_pid_list->last_kill_sig = sig;
	return (1);
}

void	ft_last_kill(t_pid_list *pid_list, int sig, void *context)
{
	(void)sig;
	(void)context;
	if (!pid_list)
		kill(g_pid_list->last_kill_pid, g_pid_list->last_kill_sig);
	else
		kill(pid_list->last_kill_pid, pid_list->last_kill_sig);
}
