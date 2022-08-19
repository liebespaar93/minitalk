/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid_printf_client.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:58:35 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 15:41:41 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <signal.h>
#include <ft_color.h>
#include <ft_pid.h>

int	ft_pid_printf_client_step_null(pid_t standard, pid_t pass)
{
	return (
		ft_printf(
			FG_LRED"<< "
			FG_LYELLOW"CLIENT PID["
			FG_WHITE"%d"
			FG_LYELLOW"]"
			FG_LRED" -x- "
			FG_LYELLOW"SERVER PID["
			FG_WHITE"%d"
			FG_LYELLOW"]"
			FG_LRED" >>"
			NO_COLOR
			"\n", \
			standard, \
			pass
		)
	);
}

int	ft_pid_printf_client_step_0(pid_t standard, pid_t pass)
{
	return (
		ft_printf(
			"\n"\
			FG_LRED"<< "
			FG_LYELLOW"CLIENT PID["
			FG_WHITE"%d"
			FG_LYELLOW"]"
			FG_LRED" --> "
			FG_LYELLOW"SERVER PID["
			FG_WHITE"%d"
			FG_LYELLOW"]"
			FG_LRED" >>"
			NO_COLOR
			"\n", \
			standard, \
			pass
		)
	);
}

int	ft_pid_printf_client_step_1(pid_t standard, pid_t pass)
{
	return (
		ft_printf(
			FG_LGREEN"<< "
			FG_LYELLOW"CLIENT PID["
			FG_WHITE"%d"
			FG_LYELLOW"]"
			FG_LGREEN" --> "
			FG_LYELLOW"SERVER PID["
			FG_WHITE"%d"
			FG_LYELLOW"]"
			FG_GREEN" >>"
			NO_COLOR
			"\n", \
			standard, \
			pass
		)
	);
}

int	ft_pid_printf_client_step_2(pid_t standard, pid_t pass)
{
	return (
		ft_printf(
			FG_LGREEN"<< "
			FG_LYELLOW"CLIENT PID["
			FG_WHITE"%d"
			FG_LYELLOW"]"
			FG_LGREEN" <-> "
			FG_LYELLOW"SERVER PID["
			FG_WHITE"%d"
			FG_LYELLOW"]"
			FG_GREEN" >>"
			NO_COLOR
			"\n", \
			standard, \
			pass
		)
	);
}

int	ft_pid_printf_client(pid_t	standard, pid_t pass, t_pid_list *pid_list)
{
	if (!pid_list)
		return (ft_pid_printf_client_step_null(standard, pass));
	else if (pid_list->step == 0)
		return (ft_pid_printf_client_step_0(standard, pass));
	else if (pid_list->step == 1)
		return (ft_pid_printf_client_step_1(standard, pass));
	else if (pid_list->step == 2)
		return (ft_pid_printf_client_step_2(standard, pass));
	return (0);
}
