#ifndef IRC_H
# define IRC_H
# include "messages.h"
# include "libft.h"
# include "implemt.h"
# include <time.h>
# include <gtk/gtk.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <signal.h>
# include <unistd.h>
# include <netdb.h>
# define TRANSFERT_READ_MODE	0
# define TRANSFERT_WRITE_MODE	1
# define TRANSFERT_READY		0
# define TRANSFERT_CONTINUE		1
# define TRANSFERT_END			2
# define INVALID_SOCKET			-1
# define MAX_CLIENTS			20
# define DEFAULT_PORT			1234
# define MSG_LEN_MAX			512
# define MSG_END				"\x0d\x0a"
//# define MSG_END				"\n"

extern int				errno;

typedef char			t_msg[MSG_LEN_MAX];

typedef struct			s_blob
{
	int					fd;
	int					status;
	size_t				total_size;
	size_t				transfer_size;
	t_msg				buffer;
	char				*start;
	char				*pointer;
}						t_blob;

typedef struct			s_channel
{
	char				name[200];
	t_list				*clients;
	t_list				*operators;
}						t_channel;

typedef struct			s_client
{
	char				nickname[10];
	char				*hostname;
	struct sockaddr_in	sin;
	int					sock;
	int					port;
}						t_client;

typedef struct			s_srvclient
{
	char				nickname[10];
	char				*hostname;
	struct sockaddr_in	sin;
	int					sock;
	int					port;
	t_channel			*ch;
	t_msg				fullmsg;
	char				*reading_pointer;
	char				*start;
	char				*end;
	size_t				readed_size;
	int					transfert_status;
	t_list				*blob_list;
}						t_srvclient;

typedef struct			s_server
{
	fd_set				r_fds;
	fd_set				w_fds;
	int					sock;
	int					port;
	struct sockaddr_in	sin;
	char				*name;
	t_srvclient			*clients[MAX_CLIENTS];
	t_list				*channels;
}						t_server;

/*
**
**
**
*/

typedef enum			e_str_color
{
	def_str,
	err_str,
	server_def_str,
	server_err_str,
	log_ok_str,
	log_err_str
}						t_str_color;

typedef struct			s_ui_str
{
	t_str_color			color;
	char				time[16];
	char				*str;
}						t_ui_str;

typedef struct			s_irc_ui_server
{
	GThread				*thr;
	int					started;
	GtkBuilder			*builder;
	GtkTextView			*input;
	GtkTextView			*output;
	GtkButton			*sendbtn;
	GtkWindow			*window;
	GtkEntry			*hostname;
	GtkEntry			*port;
	GtkButton			*connectbtn;
	GMutex				mutex;
	t_server			*server;
}						t_irc_ui_server;

typedef struct			s_irc_ui_client
{
	GThread				*thr;
	GtkTextTag			*tags[6];
	int					started;
	int					should_stop;
	t_list				*lines_strs;
	size_t				n_lines;
	GtkBuilder			*builder;
	GtkTextView			*input;
	GtkTextView			*output;
	GtkButton			*sendbtn;
	GtkWindow			*window;
	GtkEntry			*hostname;
	GtkEntry			*port;
	GtkButton			*connectbtn;
	GtkEntry			*nick;
	GtkEntry			*channel;
	GtkButton			*modifybtn;
	GtkListBox			*users;
	GMutex				mutex;
	GCond				cond;
	t_client			*client;
}						t_irc_ui_client;

typedef struct			s_modif_ui
{
	char				*s;
	t_irc_ui_client		*ui;
}						t_modif_ui;

void					connect_button_handler(GtkButton *button, gpointer data);
void					send_button_handler(GtkButton *button, gpointer data);

void					update_connection(t_irc_ui_client *ui, char *host, char *port);
void					update_log(t_irc_ui_client *ui);
void					update_nickname(t_irc_ui_client *ui, char *s);
void					update_channel(t_irc_ui_client *ui, char *s);

void					start_client_thread(t_irc_ui_client *client);
void					*idle_client_output_refresh(gpointer *data);
void					*idle_client_nickname_refresh(gpointer *data);
void					*idle_client_channel_refresh(gpointer *data);
void					ui_init_str(t_ui_str *s, char *str, t_str_color color);
void					ui_append_str(t_irc_ui_client *ui, char *str, t_str_color color);

int						irc_server_init(t_server *s, int port);
void					irc_server_close(t_server *s);
void					irc_server_loop(t_server *s);
int						irc_server_send(t_server *s, t_srvclient *c, const char *msg);
int						irc_server_receive(t_server *s, t_srvclient *c, t_msg *msg);
int						irc_server_command(t_server *s, t_srvclient *c, t_msg msg);
void					irc_server_command_nick(t_server *s, t_srvclient *c, char **av);
void					irc_server_command_join(t_server *s, t_srvclient *c, char **av);
void					irc_server_command_msg(t_server *s, t_srvclient *c, char **av);
void					irc_server_command_list(t_server *s, t_srvclient *c, char **av);

int						irc_client_init(t_client *c);
void					irc_client_close(t_client *c);
int						irc_client_connect(t_client *c, const char *address, int port);
void					irc_client_loop(t_irc_ui_client *ui);
int						irc_client_receive(t_client *c, t_msg *msg);
int						irc_client_command(t_irc_ui_client *ui, t_msg msg);
void					irc_client_command_nick(t_irc_ui_client *ui, char **av);

#endif
