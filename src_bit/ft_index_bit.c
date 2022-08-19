/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_bit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:23:19 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 15:46:04 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_bit.h>

_Bool	ft_index_bit_get(char *data, t_index_bit index_bit)
{
	return (
		ft_byte_bit_get(
			data + index_bit.bits.index, \
			index_bit.bits.bit
		)
	);
}

_Bool	ft_index_bit_set(char *data, t_index_bit index_bit, _Bool value)
{
	return (
		ft_byte_bit_set(
			data + index_bit.bits.index, \
			index_bit.bits.bit, \
			value
		)
	);
}
