#include "irc.h"

static void			init_ui(t_irc_ui_client *ui, t_client *c, char *host, char* port)
{
	g_mutex_init(&ui->mutex);
	ui->client = c;
	ui->builder = gtk_builder_new_from_file("./xml/client.glade");
	ui->window = (GtkWindow*)gtk_builder_get_object(ui->builder, "client-window");
	ui->sendbtn = (GtkButton*)gtk_builder_get_object(ui->builder, "client-send");
	ui->output = (GtkTextView*)gtk_builder_get_object(ui->builder, "client-output");
	ui->input = (GtkTextView*)gtk_builder_get_object(ui->builder, "client-input");
	ui->hostname = (GtkEntry*)gtk_builder_get_object(ui->builder, "client-connect-host");
	ui->port = (GtkEntry*)gtk_builder_get_object(ui->builder, "client-connect-port");
	ui->connectbtn = (GtkButton*)gtk_builder_get_object(ui->builder, "client-connect-btn");
	ui->nick = (GtkEntry*)gtk_builder_get_object(ui->builder, "client-nick");
	ui->channel = (GtkEntry*)gtk_builder_get_object(ui->builder, "client-channel");
	ui->modifybtn = (GtkButton*)gtk_builder_get_object(ui->builder, "client-modify-btn");
	ui->users = (GtkListBox*)gtk_builder_get_object(ui->builder, "client-users");
	ui->tags[0] = (GtkTextTag*)gtk_builder_get_object(ui->builder, "tag-client-def");
	ui->tags[1] = (GtkTextTag*)gtk_builder_get_object(ui->builder, "tag-client-err");
	ui->tags[2] = (GtkTextTag*)gtk_builder_get_object(ui->builder, "tag-server-def");
	ui->tags[3] = (GtkTextTag*)gtk_builder_get_object(ui->builder, "tag-server-err");
	ui->tags[4] = (GtkTextTag*)gtk_builder_get_object(ui->builder, "tag-log-ok");
	ui->tags[5] = (GtkTextTag*)gtk_builder_get_object(ui->builder, "tag-log-err");
	update_connection(ui, host, port);

	g_signal_connect(
		G_OBJECT(ui->window),
		"delete-event",
		G_CALLBACK(gtk_main_quit),
		NULL
	);

	g_signal_connect(
		G_OBJECT(ui->connectbtn),
		"clicked",
		G_CALLBACK(connect_button_handler),
		ui
	);

	g_signal_connect(
		G_OBJECT(ui->sendbtn),
		"clicked",
		G_CALLBACK(send_button_handler),
		ui
	);

}


static void			clear_output(t_list *out)
{
	t_list		*tmp;
	t_ui_str	*s;

	while (out)
	{
		tmp = out->next;
		s = (t_ui_str*)out->content;
		free(s->str);
		free(s);
		free(out);
		out = tmp;
	}
}

int					main(int ac, char **av)
{
	t_irc_ui_client	*ui;
	t_client		c;

	if (ac > 3)
		return (1);
	gtk_init(&ac, &av);
	ft_bzero(&c, sizeof(t_client));
	ui = ft_memalloc(sizeof(t_irc_ui_client));
	if (ac == 1)
		init_ui(ui, &c, "", "");
	else if (ac == 2)
		init_ui(ui, &c, av[1], "1234");
	else
		init_ui(ui, &c, av[1], av[2]);
	gtk_widget_show((GtkWidget*)ui->window);
	gtk_main();
	gtk_widget_destroy((GtkWidget*)ui->window);
	gtk_widget_destroy((GtkWidget*)ui->input);
	gtk_widget_destroy((GtkWidget*)ui->output);
	gtk_widget_destroy((GtkWidget*)ui->sendbtn);
	gtk_widget_destroy((GtkWidget*)ui->window);
	gtk_widget_destroy((GtkWidget*)ui->hostname);
	gtk_widget_destroy((GtkWidget*)ui->port);
	gtk_widget_destroy((GtkWidget*)ui->connectbtn);
	gtk_widget_destroy((GtkWidget*)ui->nick);
	gtk_widget_destroy((GtkWidget*)ui->channel);
	gtk_widget_destroy((GtkWidget*)ui->modifybtn);
	gtk_widget_destroy((GtkWidget*)ui->users);
	clear_output(ui->lines_strs);
	free(ui);
	return (0);
}
