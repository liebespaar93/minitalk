#include <signal.h>

#include <stdio.h>
#include <unistd.h>
#include <ft_printf.h>
#include <libft.h>
#include <ft_color.h>
#include "../src_pid/ft_pid.c"



t_pid_list	*g_pid_list;

int	ft_last_kill_set(t_pid_list *pid_list, pid_t pid, int sig)
{
	if (!pid_list)
		return (0);
	pid_list->last_kill_pid = pid;
	pid_list->last_kill_sig = sig;
	g_pid_list->last_kill_pid = pid;
	g_pid_list->last_kill_sig = sig;
	return (1);
}

void	ft_handle_conn_client(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;

	usleep(100);
	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (!pid_list)
	{
		pid_list = ft_pid_list_add(g_pid_list, ft_pid_list_new(siginfo->si_pid));
		ft_printf(FG_LGREEN"<<"FG_LYELLOW" CLIENT PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LGREEN" --> "FG_LYELLOW"SERVER PID["FG_WHITE"%d"FG_LYELLOW"]"FG_GREEN" >> "NO_COLOR"\n", getpid(), siginfo->si_pid);
		pid_list->step++;
		ft_last_kill_set(pid_list, pid_list->pid, SIGINFO);
	}
	else if (pid_list && pid_list->step == 1)
	{
		ft_printf(FG_LGREEN"<<"FG_LYELLOW" CLIENT PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LGREEN" <-> "FG_LYELLOW"SERVER PID["FG_WHITE"%d"FG_LYELLOW"]"FG_GREEN" >> "NO_COLOR"\n", getpid(), siginfo->si_pid);
		pid_list->step++;
		ft_pid_list_data_set(pid_list, g_pid_list->data);
		ft_last_kill_set(pid_list, pid_list->pid, SIGINFO);
	}
	else if (pid_list && pid_list->step >= 2)
	{
		ft_printf(FG_LRED"<<"FG_LYELLOW" CLIENT PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LRED" --> "FG_LYELLOW"SERVER PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LRED" >> "NO_COLOR"\n", siginfo->si_pid, getpid());
		pid_list->step = 0;
		ft_last_kill_set(pid_list, pid_list->pid, SIGINFO);
	}
	else if (pid_list && !pid_list->step)
	{
		ft_pid_list_del(&g_pid_list, pid_list->pid, NULL);
		ft_printf(FG_LRED"<<"FG_LYELLOW" CLIENT PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LRED" -x- "FG_LYELLOW"SERVER PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LRED" >> "NO_COLOR"\n", siginfo->si_pid, getpid());
		exit(1);
	}
	if (!pid_list)
		kill(g_pid_list->last_kill_pid, g_pid_list->last_kill_sig);
	else 
		kill(pid_list->last_kill_pid, pid_list->last_kill_sig);
}


void	ft_handle_send_bit(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;

	usleep(100);
	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (pid_list)
	{
		if (pid_list->step == 2)
		{
			if (pid_list->index.bits.index == 4 && pid_list->step++ && ft_printf("\n"))
				pid_list->index.data = -1;
			else if (ft_index_bit_get((char *)&pid_list->len, pid_list->index) && ft_printf("1"))
				ft_last_kill_set(pid_list, pid_list->pid, SIGUSR1);
			else if (ft_printf("0"))
				ft_last_kill_set(pid_list, pid_list->pid, SIGUSR2);
			pid_list->index.data++;
		}
		if (pid_list->step == 3)
		{
			if (pid_list->index.bits.index == pid_list->len && pid_list->step-- && ft_printf("\n"))
			{
				pid_list->index.data = -1;
				ft_last_kill_set(pid_list, pid_list->pid, SIGINFO);
			}
			else if (ft_index_bit_get(pid_list->data, pid_list->index) && ft_printf("1"))
				ft_last_kill_set(pid_list, pid_list->pid, SIGUSR1);
			else if (ft_printf("0"))
				ft_last_kill_set(pid_list, pid_list->pid, SIGUSR2);
			pid_list->index.data++;
		}
	}
	if (!pid_list)
		kill(g_pid_list->last_kill_pid, g_pid_list->last_kill_sig);
	else 
		kill(pid_list->last_kill_pid, pid_list->last_kill_sig);
}

int main(int ar, char *av[])
{
	struct sigaction	sa_siginfo;
	struct sigaction	sa_sighup;
	struct sigaction	sa_siguser1;
	struct sigaction	sa_siguser2;
	siginfo_t	siginfo_server;
	

	ft_printf(FG_LYELLOW"[CLIENT PID : "FG_WHITE"%d"FG_LYELLOW" ]"NO_COLOR"\n", getpid());
	g_pid_list = ft_pid_list_new(getpid());
	ft_pid_list_data_set(g_pid_list, av[2]);
	siginfo_server.si_pid = (pid_t)ft_atoi(av[1]);

	sa_siginfo.__sigaction_u.__sa_sigaction = &ft_handle_conn_client;
	sa_siginfo.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_siginfo.sa_mask);
	sigaction(SIGINFO, &sa_siginfo, NULL);

	sa_sighup.__sigaction_u.__sa_sigaction = &ft_handle_conn_client;
	sa_sighup.sa_flags = 0;
	sigemptyset(&sa_sighup.sa_mask);
	sigaction(SIGHUP, &sa_sighup, NULL);

	sa_siguser1.__sigaction_u.__sa_sigaction = &ft_handle_send_bit;
	sa_siguser1.sa_flags = 0;
	sigemptyset(&sa_siguser1.sa_mask);
	sigaction(SIGUSR1, &sa_siguser1, NULL);

	ft_handle_conn_client(SIGINFO, &siginfo_server, NULL);

	while (1)
		pause();
	return (0);
}