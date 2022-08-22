/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 09:59:38 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/23 01:08:03 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PID_H
# define FT_PID_H

# include <ft_bit.h>
# include <stdlib.h>

typedef struct s_pid_list	t_pid_list;

typedef struct s_pid_list
{
	pid_t			pid;
	int				step;
	t_index_bit		index;

	char			*data;
	int				len;
	pid_t			last_kill_pid;
	int				last_kill_sig;

	t_pid_list		*next;
}	t_pid_list;

t_pid_list*g_pid_list;

/** ft_pid.c **/

t_pid_list	*ft_pid_list_new(pid_t	pid);
t_pid_list	*ft_pid_list_add(t_pid_list *pid_lst, t_pid_list *new_lst);
t_pid_list	*ft_pid_list_find(t_pid_list *pid_list, pid_t pid);

/** ft_pid_data.c **/

t_pid_list	*ft_pid_list_data_set(t_pid_list *pid_list, char *data);
t_pid_list	*ft_pid_list_data_set_len(t_pid_list *pid_list, size_t len);

/** ft_pid_free.c **/

t_pid_list	*ft_pid_list_free(t_pid_list **pid_list_ptr, void (*f)(void *));
t_pid_list	*ft_pid_list_del(t_pid_list **pid_list_ptr, pid_t pid, \
	void (*f)(void *));
t_pid_list	*ft_pid_list_clear(t_pid_list **pid_list_ptr, void (*f)(void *));

/** ft_pid_printf_server.c **/

int			ft_pid_printf_server(pid_t standard, pid_t pass, \
	t_pid_list *pid_list);

/** ft_pid_printf_clinet.c **/

int			ft_pid_printf_client(pid_t	standard, pid_t pass, \
	t_pid_list *pid_list);

#endif