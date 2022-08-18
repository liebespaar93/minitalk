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

void	ft_handle_conn_server(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;

	usleep(100);
	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (!pid_list)
	{
		pid_list = ft_pid_list_add(g_pid_list, ft_pid_list_new(siginfo->si_pid));
		ft_printf(FG_LGREEN"<<"FG_LYELLOW" SERVER PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LGREEN" --> "FG_LYELLOW"CLIENT PID["FG_WHITE"%d"FG_LYELLOW"]"FG_GREEN" >> "NO_COLOR"\n", getpid(),siginfo->si_pid);
		pid_list->step++;
		ft_last_kill_set(pid_list, pid_list->pid, SIGINFO);
	}
	else if(pid_list && pid_list->step == 1)
	{
		pid_list->step++;
		ft_printf(FG_LGREEN"<<"FG_LYELLOW" SERVER PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LGREEN" <-> "FG_LYELLOW"CLIENT PID["FG_WHITE"%d"FG_LYELLOW"]"FG_GREEN" >> "NO_COLOR"\n", getpid(),siginfo->si_pid);
		ft_last_kill_set(pid_list, pid_list->pid, SIGUSR1);
	}
	else if(pid_list && pid_list->step >= 2)
	{
		pid_list->step = 0;
		ft_printf(FG_LRED"<<"FG_LYELLOW" SERVER PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LRED" --> "FG_LYELLOW"CLIENT PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LRED" >> "NO_COLOR"\n", getpid(),siginfo->si_pid);
		ft_last_kill_set(pid_list, pid_list->pid, SIGINFO);
	}
	else if(pid_list && !pid_list->step)
	{
		ft_pid_list_del(&g_pid_list, siginfo->si_pid, &free);
		ft_printf(FG_LRED"<<"FG_LYELLOW" SERVER PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LRED" -x- "FG_LYELLOW"CLIENT PID["FG_WHITE"%d"FG_LYELLOW"]"FG_LRED" >> "NO_COLOR"\n", getpid(),siginfo->si_pid);
		ft_last_kill_set(pid_list, pid_list->pid, SIGINFO);
	}
	if (!pid_list)
		kill(g_pid_list->last_kill_pid, g_pid_list->last_kill_sig);
	else
		kill(pid_list->last_kill_pid, pid_list->last_kill_sig);
}

void	ft_handle_receive_bit_0(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;

	usleep(100);
	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (pid_list)
	{
		if (pid_list->step == 2)
		{
			if (pid_list->index.bits.index == 4 && pid_list->step++ && ft_printf("\n"))
			{
				ft_pid_list_data_set_len(pid_list, pid_list->len);
				pid_list->index.data = -1;
			}
			else if (ft_printf("0"))
			{
				ft_index_bit_set((char *)&pid_list->len, pid_list->index, 0);
				ft_last_kill_set(pid_list, pid_list->pid, SIGUSR1);
			}
			pid_list->index.data++;
		}
		if (pid_list->step == 3)
		{
			if (ft_printf("0"))
			{
				ft_index_bit_set(pid_list->data, pid_list->index, 0);
				ft_last_kill_set(pid_list, pid_list->pid, SIGUSR1);
			}
			pid_list->index.data++;
			if (pid_list->index.bits.index == pid_list->len && pid_list->step-- && ft_printf("\n"))
			{
				pid_list->index.data = -1;
				ft_printf(FG_LCYAN"");
				write(1, pid_list->data, pid_list->len);
				ft_printf(NO_COLOR"\n");
			}
			ft_last_kill_set(pid_list, pid_list->pid, SIGUSR1);
		}
	}
	if (!pid_list)
		kill(g_pid_list->last_kill_pid, g_pid_list->last_kill_sig);
	else 
		kill(pid_list->last_kill_pid, pid_list->last_kill_sig);
}

void	ft_handle_receive_bit_1(int sig, siginfo_t *siginfo, void *context)
{
	t_pid_list	*pid_list;

	usleep(100);
	pid_list = ft_pid_list_find(g_pid_list, siginfo->si_pid);
	if (pid_list)
	{
		if (pid_list->step == 2)
		{
			if (pid_list->index.bits.index == 4 && pid_list->step++ && ft_printf("\n"))
			{
				ft_pid_list_data_set_len(pid_list, pid_list->len);
				pid_list->index.data = -1;
			}
			else if (ft_printf("1"))
				ft_index_bit_set((char *)&pid_list->len, pid_list->index, 1);
			pid_list->index.data++;
		}
		if (pid_list->step == 3)
		{
			if (ft_printf("1"))
				ft_index_bit_set(pid_list->data, pid_list->index, 1);
			pid_list->index.data++;
			if (pid_list->index.bits.index == pid_list->len && pid_list->step-- && ft_printf("\n"))
			{
				pid_list->index.data = 0;
				ft_printf(FG_LCYAN"");
				write(1, pid_list->data, pid_list->len);
				ft_printf(NO_COLOR"\n");
			}
		}
		ft_last_kill_set(pid_list, pid_list->pid, SIGUSR1);
	}
	
	if (!pid_list)
		kill(g_pid_list->last_kill_pid, g_pid_list->last_kill_sig);
	else 
		kill(pid_list->last_kill_pid, pid_list->last_kill_sig);
}



int main(int ar, char *av[])
{
	struct sigaction	siguser1;
	struct sigaction	siguser2;
	struct sigaction	siginfo;

	ft_printf(FG_LYELLOW"[SERVER PID : "FG_WHITE"%d"FG_LYELLOW" ]"NO_COLOR"\n", getpid());
	g_pid_list = ft_pid_list_new(getpid());

	siginfo.__sigaction_u.__sa_sigaction = &ft_handle_conn_server;
	siginfo.sa_flags = SA_SIGINFO;
	sigemptyset(&siginfo.sa_mask);
	sigaction(SIGINFO, &siginfo, NULL);

	siguser1.__sigaction_u.__sa_sigaction = &ft_handle_receive_bit_1;
	siguser1.sa_flags = 0;
	sigemptyset(&siguser1.sa_mask);
	sigaction(SIGUSR1, &siguser1, NULL);

	siguser2.__sigaction_u.__sa_sigaction = &ft_handle_receive_bit_0;
	siguser2.sa_flags = 0;
	sigemptyset(&siguser2.sa_mask);
	sigaction(SIGUSR2, &siguser2, NULL);

	while (1)
		pause();
}