#include "irc.h"

void		update_connection(t_irc_ui_client *ui, char *host, char *port)
{
	gtk_entry_set_text(ui->hostname, host);
	gtk_entry_set_text(ui->port, port);
}

void			update_log(t_irc_ui_client *ui)
{
	g_idle_add((GSourceFunc)idle_client_output_refresh, ui);
}

void			update_nickname(t_irc_ui_client *ui, char *s)
{
	t_modif_ui	*mui;

	mui = (t_modif_ui*)ft_memalloc(sizeof(t_modif_ui));
	mui->s = ft_strdup(s);
	mui->ui = ui;
	g_idle_add((GSourceFunc)idle_client_nickname_refresh, mui);
}

void			update_channel(t_irc_ui_client *ui, char *s)
{
	t_modif_ui	*mui;

	mui = (t_modif_ui*)ft_memalloc(sizeof(t_modif_ui));
	mui->s = ft_strdup(s);
	mui->ui = ui;
	g_idle_add((GSourceFunc)idle_client_channel_refresh, mui);
}
