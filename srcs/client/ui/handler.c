#include "irc.h"

void		connect_button_handler(GtkButton *button, gpointer data)
{
	t_irc_ui_client	*ui;

	ui = (t_irc_ui_client*)data;
	g_mutex_lock(&ui->mutex);
	ui->should_stop = 1;
	g_mutex_unlock(&ui->mutex);
	while (ui->started)
	{
//		g_mutex_lock(&ui->mutex);
//		g_cond_wait(&ui->cond, &ui->mutex);
//		g_mutex_unlock(&ui->mutex);
	}
	start_client_thread(ui);
	(void)button;
}

static void	send_a_msg(t_irc_ui_client *ui, t_client *c, char *msg)
{
	t_msg		sendmsg;

	ft_bzero(sendmsg, MSG_LEN_MAX);
	if (ft_strlen(c->nickname) > 0)
	{
		ft_strcat(sendmsg, ":");
		ft_strcat(sendmsg, c->nickname);
	}
	else
		ft_strcat(sendmsg, ":");
	ft_strcat(sendmsg, " ");
	ft_strncat(sendmsg, msg, MSG_LEN_MAX - ft_strlen(msg));
	ft_strcat(sendmsg, MSG_END);
	if (send(c->sock, sendmsg, ft_strlen(sendmsg), 0) < 0)
	{
		ui_append_str(ui, ft_strjoin("Cannot send message : ", strerror(errno)), log_err_str);
		update_log(ui);
	}
	printf("SEND: %s\n", sendmsg);
}

void		send_button_handler(GtkButton *button, gpointer data)
{
	GtkTextIter		start;
	GtkTextIter		end;
	GtkTextBuffer	*tbuf;
	t_irc_ui_client	*ui;
	char			*buf;

	ui = (t_irc_ui_client*)data;
	g_mutex_lock(&ui->mutex);
	tbuf = gtk_text_view_get_buffer(ui->input);
	gtk_text_buffer_get_start_iter(tbuf, &start);
	gtk_text_buffer_get_end_iter(tbuf, &end);
	buf = (char*)gtk_text_buffer_get_text(tbuf, &start, &end, 0);
	buf = ft_strtrim(buf);
	send_a_msg(ui, ui->client, *buf == '/' ? buf + 1 : buf);
	free(buf);
	g_mutex_unlock(&ui->mutex);
	(void)button;
}
