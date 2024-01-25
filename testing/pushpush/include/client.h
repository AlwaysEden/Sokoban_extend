#include <gtk/gtk.h>

#define NAME_SIZE 16
typedef struct location{
    int x;
    int y;
} location_t;

typedef struct user{
    char name[NAME_SIZE];
    int score;
    location_t base_loc;
    location_t user_loc;
}user_t;

typedef struct object_data{
    int map_width;
        int map_height;
    int timeout;
    int max_user;
    struct user * users;
    location_t * item_locations;
    location_t * block_locations;
}object_data_t;

GdkPixbuf *create_pixbuf(const gchar * filename);
GtkWidget* create_entity(int id);
int load_icons();
int check_map_valid();
void set_window();
static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void display_screen();
void add_mat_board();
void exit_game(GtkWidget* widget);
void gameover();

//for move handling
int check_validation(int cmd);
int move(int cmd, int movement);
void update_model(int id, int x, int y);
void update_cell();
int item_idxToId(int idx);
int item_idToIdx(int id);
void score_up(int user_idx);
gboolean handle_cmd(gpointer user_data) ;

//for networking
int recv_bytes(int sock_fd, void * buf, size_t len);
int send_bytes(int sock_fd, void * buf, size_t len);
void handle_timeout(int signum);
int parseJson(char * jsonfile);
void *recv_msg(void * arg);
void cannot_enter();
int connection(char *arg[]);
int start_game(int fd);
