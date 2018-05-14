#include "irc.h"

void		irc_client_command_nick(t_irc_ui_client *ui, char **av)
{
	g_mutex_lock(&ui->mutex);
	ft_strncpy(ui->client->nickname, *av, 9);
	ui->client->nickname[9] = 0;
	ui_append_str(ui, ft_strdup("Nickname updated"), log_ok_str);
	update_log(ui);
	update_nickname(ui, *av);
	if (*(av + 1))
	{
		ui_append_str(ui, ft_strdup("Channel updated"), log_ok_str);
		update_channel(ui, *(av + 1));
	}
	g_mutex_unlock(&ui->mutex);
}
