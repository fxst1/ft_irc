#include "irc.h"

static int			connection(t_irc_ui_client *ui)
{
	char			*hostname;
	char			*port;
	int				ret;

	ret = 1;
	if (ui->client->sock <= 0)
	{
		if (irc_client_init(ui->client) != 0)
		{
			ui_append_str(ui, ft_strjoin("Cannot create socket : ", strerror(errno)), log_err_str);
			return (-1);
		}
	}
	hostname = (char*)gtk_entry_get_text(ui->hostname);
	port = (char*)gtk_entry_get_text(ui->port);
	if (irc_client_connect(ui->client, hostname, ft_atoi(port)) == 0)
		ui_append_str(ui, ft_strdup("Connection successfull"), log_ok_str);
	else
	{
		ret = 0;
		ui_append_str(ui, ft_strjoin("Connection error : ", strerror(errno)), log_err_str);
	}
	return (ret);
}

static int			should_stop(t_irc_ui_client *ui)
{
	int				ret;

	ret = 0;
	g_mutex_lock(&ui->mutex);
	if (ui->should_stop)
	{
		ret = 1;
		ui->started = 0;
		ui->should_stop = 0;
		irc_client_close(ui->client);
		g_cond_signal(&ui->cond);
	}
	g_mutex_unlock(&ui->mutex);
	return (ret);
}

static t_client		*start_loop(t_irc_ui_client *ui)
{
	t_client		*c;

	g_mutex_lock(&ui->mutex);
	ui->should_stop = 0;
	ui->started = connection(ui);
	c = ui->client;
	update_log(ui);
	g_mutex_unlock(&ui->mutex);
	return (c);
}

void				irc_client_loop(t_irc_ui_client *ui)
{
	t_client		*c;
	fd_set			readfds;
	t_msg			msgs[2];
	int				n;
	struct timeval	tv;

	c = start_loop(ui);
	while (ui->started)
	{
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		FD_ZERO(&readfds);
		FD_SET(c->sock, &readfds);
		if (select(c->sock + 1, &readfds, NULL, NULL, &tv) == -1)
		{
			fprintf(stderr, "Select error\n");
			exit(EXIT_FAILURE);
		}
		if (FD_ISSET(c->sock, &readfds))
		{
			n = irc_client_receive(c, &msgs[1]);
			printf("info receive: %s\n", msgs[1]);
			if ((n > 0 && irc_client_command(ui, msgs[1])) || n == 0)
				break;
		}
		if (should_stop(ui))
			break ;
	}
}
