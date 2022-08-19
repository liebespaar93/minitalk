/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_byte_bit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:21:08 by kyoulee           #+#    #+#             */
/*   Updated: 2022/08/19 15:43:40 by kyoulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_bit.h>

_Bool	ft_byte_bit_get(char *byte, int index)
{
	t_byte_bit	*byte_bit;

	byte_bit = (t_byte_bit *)byte;
	if (index == 0)
		return (byte_bit->bits.bit0);
	else if (index == 1)
		return (byte_bit->bits.bit1);
	else if (index == 2)
		return (byte_bit->bits.bit2);
	else if (index == 3)
		return (byte_bit->bits.bit3);
	else if (index == 4)
		return (byte_bit->bits.bit4);
	else if (index == 5)
		return (byte_bit->bits.bit5);
	else if (index == 6)
		return (byte_bit->bits.bit6);
	else if (index == 7)
		return (byte_bit->bits.bit7);
	return (0);
}

_Bool	ft_byte_bit_set(char *byte, int index, _Bool value)
{
	t_byte_bit	*byte_bit;

	byte_bit = (t_byte_bit *)byte;
	if (index == 0)
		byte_bit->bits.bit0 = value;
	else if (index == 1)
		byte_bit->bits.bit1 = value;
	else if (index == 2)
		byte_bit->bits.bit2 = value;
	else if (index == 3)
		byte_bit->bits.bit3 = value;
	else if (index == 4)
		byte_bit->bits.bit4 = value;
	else if (index == 5)
		byte_bit->bits.bit5 = value;
	else if (index == 6)
		byte_bit->bits.bit6 = value;
	else if (index == 7)
		byte_bit->bits.bit7 = value;
	*byte = byte_bit->byte;
	return (value);
}
