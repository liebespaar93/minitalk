/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:23:04 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/22 22:55:22 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <ft_color.h>
#include <libft.h>
#include <signal.h>
#include <ft_pid.h>
#include <ft_kill.h>

void	ft_handle_conn_client(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;

	usleep(100);
	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (siginfo->si_pid && !pid_list)
	{
		pid_list = \
			ft_pid_list_add(g_pid_list, ft_pid_list_new(siginfo->si_pid));
		ft_pid_list_data_set(pid_list, g_pid_list->data);
		ft_kill_set(pid_list, SIGINFO);
		pid_list->step++;
	}
	else if (pid_list && pid_list->step == 1 && pid_list->step++)
		ft_kill_set(pid_list, SIGINFO);
	else if (pid_list && pid_list->step >= 2 && ft_kill_set(pid_list, SIGINFO))
		pid_list->step = 0;
	else if (pid_list && !pid_list->step)
	{
		ft_pid_list_clear(&g_pid_list, NULL);
		ft_pid_printf_client(getpid(), siginfo->si_pid, NULL);
		exit(1);
	}
	ft_pid_printf_client(getpid(), siginfo->si_pid, pid_list);
	ft_last_kill(pid_list, sig, context);
}

void	ft_handle_send_bit(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;
	_Bool		bit;

	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (!usleep(100) && pid_list && pid_list->step == 2)
	{
		bit = ft_index_bit_get((char *)&pid_list->len, pid_list->index);
		if (ft_printf(FG_LCYAN"%d", bit) && ++pid_list->index.data)
			ft_kill_set(pid_list, SIGUSR1 + bit);
		if (pid_list->index.bits.index == 4 && pid_list->step++)
			if (ft_printf("\n"))
				pid_list->index.data = 0;
	}
	else if (pid_list && pid_list->step == 3)
	{
		if (pid_list->index.bits.index == pid_list->len && pid_list->step--)
			ft_kill_set(pid_list, SIGINFO);
		else
		{
			bit = ft_index_bit_get(pid_list->data, pid_list->index);
			if (ft_printf(FG"208m%d", bit) && ++pid_list->index.data)
				ft_kill_set(pid_list, SIGUSR1 + bit);
		}
	}
	ft_last_kill(pid_list, sig, context);
}

int	main(int ar, char *av[])
{
	struct sigaction	sa_siginfo;
	struct sigaction	sa_siguser1;
	siginfo_t			siginfo_server;

	ft_printf(FG_LYELLOW"[CLIENT PID : "FG_WHITE"%d"FG_LYELLOW" ]\n", getpid());
	if (ar < 3 && ft_error_m("CEHCK argv need more then 3"))
		return (-1);
	if (!ft_atoi(av[1]) && ft_error_m("CEHCK PID number"))
		return (-1);
	g_pid_list = ft_pid_list_new(getpid());
	ft_pid_list_data_set(g_pid_list, av[2]);
	siginfo_server.si_pid = (pid_t)ft_atoi(av[1]);
	sa_siginfo.__sigaction_u.__sa_sigaction = &ft_handle_conn_client;
	sa_siginfo.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_siginfo.sa_mask);
	sigaction(SIGINFO, &sa_siginfo, NULL);
	sa_siguser1.__sigaction_u.__sa_sigaction = &ft_handle_send_bit;
	sa_siguser1.sa_flags = 0;
	sigemptyset(&sa_siguser1.sa_mask);
	sigaction(SIGUSR1, &sa_siguser1, NULL);
	ft_handle_conn_client(SIGINFO, &siginfo_server, NULL);
	while (1)
		pause();
	return (0);
}
