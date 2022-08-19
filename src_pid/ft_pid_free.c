/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:28:09 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 15:30:47 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_pid.h>

t_pid_list	*ft_pid_list_free(t_pid_list **pid_list_ptr, void (*f)(void *))
{
	t_pid_list	*pid_list_next;

	pid_list_next = (*pid_list_ptr)->next;
	if ((*pid_list_ptr)->data && f)
		f((*pid_list_ptr)->data);
	free((*pid_list_ptr));
	*pid_list_ptr = NULL;
	return (pid_list_next);
}

t_pid_list	*ft_pid_list_del(t_pid_list **pid_list_ptr, pid_t pid, \
	void (*f)(void *))
{
	t_pid_list	*pid_list;
	t_pid_list	*pid_list_next;

	if (!pid_list_ptr && !*pid_list_ptr)
		return (NULL);
	pid_list = *pid_list_ptr;
	pid_list_next = pid_list->next;
	while (pid_list_next)
	{
		if (pid_list_next->pid == pid)
		{
			pid_list->next = pid_list_next->next;
			ft_pid_list_free(&pid_list_next, f);
			return (pid_list);
		}
		pid_list = pid_list_next;
		pid_list_next = pid_list_next->next;
	}
	return (NULL);
}

t_pid_list	*ft_pid_list_clear(t_pid_list **pid_list_ptr, void (*f)(void *))
{
	t_pid_list	*pid_list;
	t_pid_list	*pid_list_next;

	if (!pid_list_ptr && !*pid_list_ptr)
		return (NULL);
	pid_list = *pid_list_ptr;
	pid_list_next = pid_list->next;
	while (pid_list)
	{
		pid_list_next = pid_list->next;
		ft_pid_list_free(&pid_list, f);
		pid_list = pid_list_next;
	}
	return (NULL);
}
