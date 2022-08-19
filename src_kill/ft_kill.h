/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:08:18 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 15:43:05 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_KILL_H
# define FT_KILL_H

# include <ft_pid.h>

int		ft_kill_set(t_pid_list *pid_list, int sig);
void	ft_last_kill(t_pid_list *pid_list, int sig, void *context);

#endif