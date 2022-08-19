/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:03:40 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 10:44:12 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_pid.h>
#include <libft.h>
#include <signal.h>

t_pid_list	*ft_pid_list_new(pid_t	pid)
{
	t_pid_list	*new;

	if (!ft_zeromalloc((void **)&new, sizeof(t_pid_list)))
		return (NULL);
	new->pid = pid;
	return (new);
}

t_pid_list	*ft_pid_list_add(t_pid_list *pid_lst, t_pid_list *new_lst)
{
	if (!pid_lst)
		return (new_lst);
	new_lst->next = pid_lst->next;
	pid_lst->next = new_lst;
	return (new_lst);
}

t_pid_list	*ft_pid_list_find(t_pid_list *pid_list, pid_t pid)
{
	while (pid_list)
	{
		if (pid_list->pid == pid)
			return (pid_list);
		pid_list = pid_list->next;
	}
	return (NULL);
}
