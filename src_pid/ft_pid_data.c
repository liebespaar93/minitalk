/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:04:59 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 15:38:29 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_pid.h>
#include <libft.h>

t_pid_list	*ft_pid_list_data_set(t_pid_list *pid_list, char *data)
{
	if (!data)
		return (NULL);
	pid_list->len = ft_strlen(data);
	pid_list->data = data;
	return (pid_list);
}

t_pid_list	*ft_pid_list_data_set_len(t_pid_list *pid_list, size_t len)
{
	if (!len)
		return (NULL);
	pid_list->len = len;
	if (!ft_zeromalloc((void **)&pid_list->data, sizeof(char) * len))
		return (NULL);
	return (pid_list);
}
