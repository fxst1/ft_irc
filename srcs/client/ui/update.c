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
