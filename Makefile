# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyoulee <kyoulee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/31 10:01:30 by kyoulee           #+#    #+#              #
#    Updated: 2022/08/23 09:52:41 by kyoulee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = minitalk

CC = cc
CXXFLAGS = $(NULL)
CFLAGS = -Wall -Werror -Wextra
DFLAGS = $(NULL)
IFLAGS =						\
	-I $(INCLUDE_DIR)			\
	-I $(INCLUDE_LIBFT_DIR)		\
	-I $(INCLUDE_FT_PRINTF_DIR)

LDFLAGS =						\
	-L $(LIBFT_DIR)				\
	-L $(FT_PRINTF_DIR)
	
LDLIBS =						\
	-lftprintf -lft 
	

#####***** COLOR *****#####
BG_RED     = \033[41m
BG_GREEN   = \033[42m
BG_YELLOW  = \033[43m
BG_BLUE    = \033[44m
BG_MAGENTA = \033[45m
BG_CYAN    = \033[46m
BG_LGREY   = \033[47m
BG_DGREY   = \033[100m
BG_LRED    = \033[101m
BG_LGREEN  = \033[102m
BG_LYELLOW = \033[103m
BG_LBLUE   = \033[104m
BG_LMAGENTA= \033[105m
BG_LCYAN   = \033[106m
BG_WHITE   = \033[107m
BG_MAKE1   = \033[48;5;236m
BG_MAKE2   = \033[48;5;238m
BG_MAKE3   = \033[48;5;240m

FG_BLACK   = \033[30m
FG_RED     = \033[31m
FG_GREEN   = \033[32m
FG_YELLOW  = \033[33m
FG_BLUE    = \033[34m
FG_MAGENTA = \033[35m
FG_CYAN    = \033[36m
FG_LGREY   = \033[37m
FG_DGREY   = \033[90m
FG_LRED    = \033[91m
FG_LGREEN  = \033[92m
FG_LYELLOW = \033[93m
FG_LBLUE   = \033[94m
FG_LMAGENTA= \033[95m
FG_LCYAN   = \033[96m
FG_WHITE   = \033[97m
 
CL_BOLD   = \033[1m
CL_DIM    = \033[2m
CL_UDLINE = \033[4m
CL_BLINK  = \033[5m
CL_INVERT = \033[7m
CL_HIDDEN = \033[8m
 
NO_COLOR = \033[0m

#####***** DIR *****#####

ROOTDIR = $(abspath $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))
SRC_DIR = $(ROOTDIR)/src
SRC_BIT_DIR = $(ROOTDIR)/src_bit
SRC_KILL_DIR = $(ROOTDIR)/src_kill
SRC_PID_DIR = $(ROOTDIR)/src_pid
SRC_SERVER_DIR = $(ROOTDIR)/src_server
SRC_CLINET_DIR = $(ROOTDIR)/src_client

OBJ_DIR = $(ROOTDIR)/obj
INCLUDE_DIR = $(ROOTDIR)/include

MINITALK_DIR = $(ROOTDIR)/minitalk
## MODULES ##
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = $(ROOTDIR)/modules/Libft
INCLUDE_LIBFT_DIR = $(LIBFT_DIR)/include

FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_DIR = $(ROOTDIR)/modules/ft_printf
INCLUDE_FT_PRINTF_DIR = $(FT_PRINTF_DIR)/include

#####***** SRC *****#####
SRC_C_SRC =	$(NULL)

SRC_C = $(addprefix $(SRC_DIR)/, $(SRC_C_SRC))

SRC_BIT_C_SRC =	\
						ft_byte_bit.c		\
						ft_index_bit.c
						
SRC_BIT_C = $(addprefix $(SRC_BIT_DIR)/, $(SRC_BIT_C_SRC))

SRC_KILL_C_SRC =	ft_kill.c

SRC_KILL_C = $(addprefix $(SRC_KILL_DIR)/, $(SRC_KILL_C_SRC))

SRC_PID_C_SRC =	\
						ft_pid_data.c	\
						ft_pid_free.c	\
						ft_pid_printf_client.c	\
						ft_pid_printf_server.c	\
						ft_pid.c

SRC_PID_C = $(addprefix $(SRC_PID_DIR)/, $(SRC_PID_C_SRC))

SRC_SERVER_C_SRC =	server.c

SRC_SERVER_C = $(addprefix $(SRC_SERVER_DIR)/, $(SRC_SERVER_C_SRC))

SRC_CLIENT_C_SRC =	client.c

SRC_CLIENT_C = $(addprefix $(SRC_CLINET_DIR)/, $(SRC_CLIENT_C_SRC))

OBJS =	$(SRC_C:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)						\
		$(SRC_BIT_C:$(SRC_BIT_DIR)/%.c=$(OBJ_DIR)/%.o)				\
		$(SRC_KILL_C:$(SRC_KILL_DIR)/%.c=$(OBJ_DIR)/%.o)			\
		$(SRC_PID_C:$(SRC_PID_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS_SERVER =	$(SRC_SERVER_C:$(SRC_SERVER_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_CLIENT	=	$(SRC_CLIENT_C:$(SRC_CLINET_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS_CLEAN = $(OBJS)

#####***** working *****#####

all : $(OBJ_DIR) $(TARGET)

bonus : $(OBJ_DIR) $(TARGET)

test : 
	@echo "$(OBJS) -o $(TARGET)"

$(TARGET) : $(MINITALK_DIR) $(OBJS) $(OBJS_SERVER) $(OBJS_CLIENT) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(IFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJS) $(OBJS_SERVER) -o $(TARGET)/server
	$(CC) $(CFLAGS) $(IFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJS) $(OBJS_CLIENT) -o $(TARGET)/client
	@echo "$(FG_LMAGENTA)$(CC) $(FG_BLUE) $(CFLAGS)"
	@(for i in $(IFLAGS) $(LDFLAGS); do echo $$i; done)
	@echo "$(LDLIBS) $(FG_LCYAN)"
	@(for i in $(OBJS); do echo $$i; done)
	@echo "$(FG_BLUE)-o $(FG_LYELLOW)$(TARGET)"

$(OBJ_DIR) : 
	mkdir $@

$(MINITALK_DIR) : 
	mkdir $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_BIT_DIR)/%.c
	$(CC) $(CPPFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_KILL_DIR)/%.c
	$(CC) $(CPPFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_PID_DIR)/%.c
	$(CC) $(CPPFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_SERVER_DIR)/%.c
	$(CC) $(CPPFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_CLINET_DIR)/%.c
	$(CC) $(CPPFLAGS) $(IFLAGS) -c $< -o $@

## MODULES ##
$(LIBFT):
	echo "$(FG_MAGENTA)module $(FG_LYELLOW)Libft$(NO_COLOR) -> $(FG_LCYAN)$(LIBFT)$(NO_COLOR)$(BG_MAKE1)"
	$(MAKE) -C $(LIBFT_DIR) bonus
	@echo "$(NO_COLOR)"

$(FT_PRINTF):
	echo "$(FG_MAGENTA)module $(FG_LYELLOW)ft_printf$(NO_COLOR) -> $(FG_LCYAN)$(FT_PRINTF)$(NO_COLOR)$(BG_MAKE1)"
	$(MAKE) -C $(FT_PRINTF_DIR) bonus
	@echo "$(NO_COLOR)"
#####***** clean *****#####

## MODULES ##
clean_libft :
	@echo "clean $(FG_MAGENTA)module $(FG_LYELLOW)$(notdir $(LIBFT))$(NO_COLOR)$(BG_MAKE1)"
	$(MAKE) -C $(LIBFT_DIR) $(MAKECMDGOALS) 
	@echo "$(NO_COLOR)"

clean_ft_printf :
	@echo "clean $(FG_MAGENTA)module $(FG_LYELLOW)$(notdir $(FT_PRINTF))$(NO_COLOR)$(BG_MAKE1)"
	$(MAKE) -C $(FT_PRINTF_DIR) $(MAKECMDGOALS)
	@echo "$(NO_COLOR)"

clean : clean_libft clean_ft_printf
	rm -f $(OBJS_CLEAN) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean : OBJS_CLEAN+=$(TARGET)/SERVER $(TARGET)/CLIENT
fclean : clean
	rm -r $(TARGET)

re : fclean all

.PHONY: all re  clean fclean clean_libft clean_ft_printf
