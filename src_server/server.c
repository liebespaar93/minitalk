/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:11:53 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 15:20:54 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <ft_color.h>
#include <libft.h>
#include <signal.h>
#include <ft_pid.h>
#include <ft_kill.h>

t_pid_list	*g_pid_list;

void	ft_handle_conn_server(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;

	usleep(100);
	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (siginfo->si_pid && !pid_list)
	{
		pid_list = \
			ft_pid_list_add(g_pid_list, ft_pid_list_new(siginfo->si_pid));
		ft_kill_set(pid_list, SIGINFO);
		pid_list->step++;
	}
	else if (pid_list && pid_list->step == 1 && ft_kill_set(pid_list, SIGUSR1))
		pid_list->step++;
	else if (pid_list && pid_list->step >= 2 && ft_kill_set(pid_list, SIGINFO))
		pid_list->step = 0;
	else if (pid_list && !pid_list->step && ft_kill_set(pid_list, SIGINFO))
	{
		ft_pid_list_del(&g_pid_list, siginfo->si_pid, free);
		pid_list = NULL;
	}
	ft_pid_printf_server(getpid(), siginfo->si_pid, pid_list);
	ft_last_kill(pid_list, sig, context);
}

void	ft_handle_receive_bit_0(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;

	usleep(100);
	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (pid_list && ft_kill_set(pid_list, SIGUSR1) && pid_list->step == 2)
	{
		ft_printf(FG_LCYAN"0");
		ft_index_bit_set((char *)&pid_list->len, pid_list->index, 0);
		pid_list->index.data++;
		if (pid_list->index.bits.index == 4 && pid_list->step++)
			if (ft_pid_list_data_set_len(pid_list, pid_list->len))
				if (ft_printf("\n"))
					pid_list->index.data = 0;
	}
	else if (pid_list && pid_list->step == 3)
	{
		ft_printf(FG"208m0"NO_COLOR);
		ft_index_bit_set(pid_list->data, pid_list->index, 0);
		pid_list->index.data++;
		if (pid_list->index.bits.index == pid_list->len)
			if (ft_printf("\n%.*2$s", pid_list->data, pid_list->len))
				pid_list->index.data = 0;
	}
	ft_last_kill(pid_list, sig, context);
}

void	ft_handle_receive_bit_1(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;

	usleep(100);
	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (pid_list && ft_kill_set(pid_list, SIGUSR1) && pid_list->step == 2)
	{
		ft_printf(FG_LCYAN"1");
		ft_index_bit_set((char *)&pid_list->len, pid_list->index, 1);
		pid_list->index.data++;
		if (pid_list->index.bits.index == 4 && pid_list->step++)
			if (ft_pid_list_data_set_len(pid_list, pid_list->len))
				if (ft_printf("\n"))
					pid_list->index.data = 0;
	}
	else if (pid_list && pid_list->step == 3)
	{
		ft_printf(FG"208m1"NO_COLOR);
		ft_index_bit_set(pid_list->data, pid_list->index, 1);
		pid_list->index.data++;
		if (pid_list->index.bits.index == pid_list->len)
			if (ft_printf("\n%.*2$s", pid_list->data, pid_list->len))
				pid_list->index.data = 0;
	}
	ft_last_kill(pid_list, sig, context);
}

int	main(void)
{
	struct sigaction	siguser1;
	struct sigaction	siguser2;
	struct sigaction	siginfo;

	ft_printf(FG_LYELLOW"[SERVER PID : "FG_WHITE"%d"FG_LYELLOW" ]\n", getpid());
	g_pid_list = ft_pid_list_new(getpid());
	siginfo.__sigaction_u.__sa_sigaction = &ft_handle_conn_server;
	siginfo.sa_flags = SA_SIGINFO;
	sigemptyset(&siginfo.sa_mask);
	sigaction(SIGINFO, &siginfo, NULL);
	siguser1.__sigaction_u.__sa_sigaction = &ft_handle_receive_bit_0;
	siguser1.sa_flags = 0;
	sigemptyset(&siguser1.sa_mask);
	sigaction(SIGUSR1, &siguser1, NULL);
	siguser2.__sigaction_u.__sa_sigaction = &ft_handle_receive_bit_1;
	siguser2.sa_flags = 0;
	sigemptyset(&siguser2.sa_mask);
	sigaction(SIGUSR2, &siguser2, NULL);
	while (1)
		pause();
	return (0);
}
