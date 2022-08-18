
typedef struct s_pid_list	t_pid_list;


typedef union u_byte_bit
{
	char	byte;
	
	struct bitFields
	{
		bool bit0 : 1;
		bool bit1 : 1;
		bool bit2 : 1;
		bool bit3 : 1;
		bool bit4 : 1;
		bool bit5 : 1;
		bool bit6 : 1;
		bool bit7 : 1;
	} bits;
}	t_byte_bit;

_Bool	ft_byte_bit_get(t_byte_bit *byte_bit, int index)
{
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

_Bool	ft_byte_bit_set(t_byte_bit *byte_bit, int index, _Bool value)
{
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
	return (value);
}

typedef union u_int_bit
{
	unsigned int	int_type;
	t_byte_bit		byte[4];
}	t_int_bit;



typedef struct s_pid_list
{
	pid_t			pid;
	t_int_bit		len;
	size_t			index;
	size_t			bit_index;

	char			*data;
	t_byte_bit		*data_bit;
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
	pid_list->len.int_type = ft_strlen(data);
	pid_list->data = data;
	pid_list->data_bit = (t_byte_bit *)pid_list->data;
	return (pid_list);
}

t_pid_list	*ft_pid_list_data_set_len(t_pid_list *pid_list, size_t len)
{
	if (!len)
		return (NULL);
	pid_list->len.int_type = len;
	if (!ft_zeromalloc((void **)pid_list->data, sizeof(char) * len))
		return (NULL);
	pid_list->data_bit = (t_byte_bit *)pid_list->data;
	return (pid_list);
}

t_pid_list	*ft_pid_list_add(t_pid_list **pid_lst, t_pid_list *new_lst)
{
	if (!pid_lst)
		return (new_lst);
	new_lst->next = *pid_lst;
	*pid_lst = new_lst;
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
	t_pid_list	*pid_list;

	pid_list = *pid_list_ptr;
	if (pid_list->data && f)
		f(pid_list->data);
	free(pid_list);
	*pid_list_ptr = NULL;
	return (*pid_list_ptr);
}

t_pid_list	*ft_pid_list_del(t_pid_list **pid_list_ptr, pid_t pid, void (*f)(void *))
{
	t_pid_list	*pid_list;
	t_pid_list	*temp;

	pid_list = *pid_list_ptr;
	temp = pid_list;
	if (pid_list->pid == pid)
	{
		*pid_list_ptr = pid_list->next;
		ft_pid_list_free(&pid_list, f);
		return (*pid_list_ptr);
	}
	while (pid_list)
	{
		if (pid_list->pid == pid)
		{
			temp->next = pid_list->next;
			ft_pid_list_free(&pid_list, f);
			*pid_list_ptr = temp;
			return (temp->next);
		}
		temp = pid_list;
		pid_list = pid_list->next;
	}
	return (NULL);
}
