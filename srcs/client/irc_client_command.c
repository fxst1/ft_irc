#include "irc.h"

static void		myecho2(char **av, size_t n, t_irc_ui_client *ui, t_str_color c)
{
	char		*str;
	size_t		i;

	i = 0;
	str = (char*)malloc(sizeof(char) * (n + 3));
	ft_bzero(str, n + 3);
	while (av[i])
	{
		if (i == 0)
			ft_strcat(str, av[i]);
		else
		{
			ft_strcat(str, " ");
			ft_strcat(str, av[i]);
		}
		i++;
	}
	g_mutex_lock(&ui->mutex);
	ui_append_str(ui, str, c);
	update_log(ui);
	g_mutex_unlock(&ui->mutex);
}

static void		myecho(char **av, t_irc_ui_client *ui, t_str_color c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (av[i])
	{
		if (i == 0)
			n += ft_strlen(av[i]);
		else
			n += ft_strlen(av[i]) + 1;
		i++;
	}
	if (n > 0)
		myecho2(av, n, ui, c);
}

static void		undef_command(t_irc_ui_client *ui, t_msg msg)
{
	char		*s;

	g_mutex_lock(&ui->mutex);
	s = ft_strjoin("Undefined command : ", msg);
	ui_append_str(ui, s, log_err_str);
	update_log(ui);
	g_mutex_unlock(&ui->mutex);
}

int				irc_client_command(t_irc_ui_client *ui, t_msg msg)
{
	char	**split;
	size_t	i;

	i = 0;
	split = ft_strsplit(msg, ' ');
	if (!ft_strccmp(split[1], "NOTICE"))
		myecho(split + 2, ui, server_def_str);
	else if (!ft_strccmp(split[1], "ERROR"))
		myecho(split + 2, ui, server_err_str);
	else if (!ft_strccmp(split[1], "QUIT"))
		irc_client_close(ui->client);
	else if (!ft_strccmp(split[1], "INFO"))
		irc_client_command_nick(ui, split + 2);
	else if (!ft_strccmp(split[1], "MSG"))
		myecho(split + 2, ui, def_str);
	else if (!ft_strccmp(split[1], "LIST"))
		;
	else
		undef_command(ui, msg);
	while (split[i])
		free(split[i++]);
	free(split);
	return (0);
}
