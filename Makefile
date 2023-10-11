# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jehubert <jehubert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 22:27:42 by amonier           #+#    #+#              #
#    Updated: 2023/09/16 22:33:41 by jehubert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

DIR_SRCS	= srcs

DIR_OBJS	= objs

SRCS_NAMES		= 	main/main.c		\
					main/ctrlc.c	\
					parsing/env.c		\
					exec/clear_double_tab_int.c		\
					exec/exec.c										\
					exec/child.c									\
					exec/pipex/pipex.c									\
					exec/pipex/pipex_error.c							\
					exec/builtin/check_builtin.c								\
					exec/cmds/cmds.c												\
					exec/cmds/cmds_two.c										\
					exec/cmds/cmds_three.c										\
					exec/builtin/size_double_tab.c								\
					exec/builtin/cd/cd.c											\
					exec/builtin/cd/cd_two.c									\
					exec/builtin/cd/cd_three.c										\
					exec/builtin/pwd.c											\
					exec/builtin/echo.c											\
					exec/builtin/export/b_export.c										\
					exec/builtin/export/alpha_export.c							\
					exec/builtin/export/alpha_export_two.c						\
					exec/builtin/export/b_export_two.c							\
					exec/builtin/export/b_export_three.c						\
					exec/builtin/export/b_export_four.c							\
					exec/builtin/b_env.c										\
					exec/builtin/free_double_tab_char.c							\
					exec/builtin/b_unset.c										\
					exec/free_t_mini.c											\
					exec/no_fork/no_fork.c								\
					exec/no_fork/no_fork_two.c							\
					exec/files/files.c								\
					exec/files/files_two.c							\
					exec/files/files_three.c						\
					exec/print_error.c									\
					exec/ft_strjoin_triple.c							\
					exec/builtin/secure_printf.c						\
					parsing/split_utils.c \
					parsing/check_tokens_utils.c \
					parsing/check_tokens_main.c \
					parsing/cmd_split.c \
					parsing/search_redir.c \
					parsing/check_quotes.c \
					parsing/utils_redir.c \
					parsing/quotes_state.c \
					parsing/quotes_state_utils.c \
					parsing/dollar.c \
					parsing/env_var_update.c \
					parsing/checking.c \
					parsing/free.c \
					parsing/remove_quotes.c \
					parsing/check_prompt.c \
					parsing/get.c \
					parsing/line.c		\
					parsing/to_expand.c \
					patch/here_doc.c									\
					patch/create_temp_files.c							\
					patch/unlink_tmp_files.c							\
					patch/dollar_bis.c	\
					parsing/check_bis.c \
					patch/random_names.c \
					patch/rnl.c	\
					patch/ctrl_here_doc.c	\
					patch/file_dad.c		\
					exec/builtin/export/export_patch.c			\
					exec/no_fork/no_fork_three.c \
					exec/builtin/export/alpha_export_five.c \
					exec/builtin/export/alpha_export_six.c \
					main/main_bis.c

OBJS_NAMES	= ${SRCS_NAMES:.c=.o}

SRCS		= $(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS		= $(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -g2 -g3
HEAD		= -IIncludes

RM			= rm -f
DIR_DUP		= mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft --no-print-directory
	$(CC) $(CFLAGS) $(OBJS) -lreadline libft/libft.a -o $(NAME)
	$(info CREATED $(NAME))
	@echo "DONE !"

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(HEAD) -c $< -o $@
	$(info CREATED $@)

clean:
	make -C libft clean --no-print-directory
	$(RM) $(OBJS)

fclean: clean
	make -C libft fclean --no-print-directory
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
