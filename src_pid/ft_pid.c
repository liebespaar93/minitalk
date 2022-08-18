#include <stdlib.h>

typedef struct s_pid_list	t_pid_list;


typedef union u_byte_bit
{
	char	byte;
	
	struct bitFields
	{
		_Bool bit0 : 1;
		_Bool bit1 : 1;
		_Bool bit2 : 1;
		_Bool bit3 : 1;
		_Bool bit4 : 1;
		_Bool bit5 : 1;
		_Bool bit6 : 1;
		_Bool bit7 : 1;
	} bits;
}	t_byte_bit;

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

typedef union u_int_bit
{
	unsigned int	int_type;
	unsigned char	byte[4];
}	t_int_bit;

typedef union u_index_bit
{
	int		data;
	struct index_bit
	{
		unsigned char	bit:3;
		int				index:29;
	} bits;
}	t_index_bit;

_Bool	ft_index_bit_get(char *data, t_index_bit index_bit)
{
	return (ft_byte_bit_get(data + index_bit.bits.index, index_bit.bits.bit));
}

_Bool	ft_index_bit_set(char *data, t_index_bit index_bit, _Bool value)
{
	return (ft_byte_bit_set(data + index_bit.bits.index, index_bit.bits.bit, value));
}

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

t_pid_list	*ft_pid_list_new(pid_t	pid)
{
	t_pid_list	*new;

	if (!ft_zeromalloc((void **)&new, sizeof(t_pid_list)))
		return (NULL);
	new->pid = pid;
	return (new);
}


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

t_pid_list	*ft_pid_list_del(t_pid_list **pid_list_ptr, pid_t pid, void (*f)(void *))
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
