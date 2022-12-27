#ifndef __SHOW_H
#define __SHOW_H

//gcc `pkg-config --cflags gtk+-3.0` -o main main.c `pkg-config --libs gtk+-3.0`

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "type.h"

struct data
{
    int h, w, nl, nc;
    int matrix[n_max][n_max];
    position st, ed;
    char *name;
    position *path;
    int lg;
};

struct update_data
{
    int h, w;
    position *path;
    int lg;
    int poz;
    GtkWidget *grid;
}; 

struct process_data
{
    int matrix[n_max][n_max];
    position st, ed;
    int h, w, nl, nc;
    int poz;
    GtkWidget *grid;
};

static void activate_initial(GtkApplication*, gpointer);
static void activate_way(GtkApplication*, gpointer);
static void activate_process(GtkApplication*, gpointer);

void myCSS();

GtkWidget* create_window(char*, int, int, GtkApplication*);
GtkWidget* create_grid(int[][n_max], position, position, int, int, int, int);
GtkWidget* create_cheese_button(gint, gint);
GtkWidget* create_mouse_button(gint, gint);
GtkWidget* create_wall_button(gint, gint);
GtkWidget* create_floor_button();

void update_run_button(GtkWidget*, gint, gint);
void update_find_button(GtkWidget*, gint, gint);
void update_pass_button(GtkWidget*);
void update_process_button(GtkWidget*, int);
void update_pass_process_button(GtkWidget*);

static gboolean update_grid_way(gpointer);
static gboolean update_grid_process(gpointer);

int run(int[][n_max], int, int, position, position, int, int, char*, int, ...);
void atribute(struct data*, int[][n_max], int, int, int, int, position, position, char*);

GtkWidget* create_cheese_button(gint h, gint w)
{
    GtkWidget *button, *image;
    button = gtk_button_new();
    GdkPixbuf *pin, *pout;
    const gchar *filename = "cheese.png";
    pin = gdk_pixbuf_new_from_file(filename, NULL);
    pout = gdk_pixbuf_scale_simple(GDK_PIXBUF(pin), h, w, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(GDK_PIXBUF(pout));
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "Cheese");
    return button;
}

GtkWidget* create_mouse_button(gint h, gint w)
{
    GtkWidget *button, *image;
    GdkPixbuf *pin, *pout;
    const gchar *filename = "mouse.png";
    pin = gdk_pixbuf_new_from_file(filename, NULL);
    pout = gdk_pixbuf_scale_simple(GDK_PIXBUF(pin), h, w, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(GDK_PIXBUF(pout));
    button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "Mouse");
    return button;
}

GtkWidget* create_wall_button(gint h, gint w)
{
    GtkWidget *button, *image;
    GdkPixbuf *pin, *pout;
    const gchar *filename = "wall.png";
    pin = gdk_pixbuf_new_from_file(filename, NULL);
    pout = gdk_pixbuf_scale_simple(GDK_PIXBUF(pin), h, w, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(GDK_PIXBUF(pout));
    button = gtk_button_new();
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "Wall");
    return button;
}

GtkWidget* create_floor_button()
{
    GtkWidget *button;
    button = gtk_button_new();
    gtk_widget_set_name(button, "Floor");
    return button;
}

void update_run_button(GtkWidget* button, gint h, gint w)
{
    GtkWidget *image;
    GdkPixbuf *pin, *pout;
    const gchar *filename = "run.png";

    pin = gdk_pixbuf_new_from_file(filename, NULL);
    pout = gdk_pixbuf_scale_simple(GDK_PIXBUF(pin), h, w, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(GDK_PIXBUF(pout));
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "Run"); 
}

void update_find_button(GtkWidget* button, gint h, gint w)
{
    GtkWidget *image;
    GdkPixbuf *pin, *pout;
    const gchar *filename = "find.png";

    pin = gdk_pixbuf_new_from_file(filename, NULL);
    pout = gdk_pixbuf_scale_simple(GDK_PIXBUF(pin), h, w, GDK_INTERP_BILINEAR);
    image = gtk_image_new_from_pixbuf(GDK_PIXBUF(pout));
    gtk_button_set_image(GTK_BUTTON(button), image);
    gtk_widget_set_name(button, "Find");
}

void update_pass_button(GtkWidget* button)
{
    GtkWidget *image = gtk_button_get_image(GTK_BUTTON(button));
    gtk_widget_hide(image);
    gtk_widget_set_name(button, "Pass");
}

void update_process_button(GtkWidget* button, int number)
{
    gtk_widget_set_name(button, "Process");
    gchar *text;
    
    text = g_strdup_printf("%d", number);

    gtk_button_set_label(GTK_BUTTON(button), text); 

    g_free(text);
}

void update_pass_process_button(GtkWidget* button)
{
    gtk_widget_set_name(button, "Pass_process");
}

GtkWidget* create_grid(int matrix[][n_max], position st, position ed, int nl, int nc, int h, int w)
{
    gint h_cell = h/nl;
    gint w_cell = w/nc;

    GtkWidget* grid, *button;
    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 1);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 1);

    int i, j; 
    for (i = 0; i < nl; ++i) gtk_grid_insert_row(GTK_GRID(grid), i);
    for (j = 0; j < nc; ++j) gtk_grid_insert_column(GTK_GRID(grid), j);
    for (i = 0; i < nl; ++i)
        for (j = 0; j < nc; ++j)
        {
            if (i+1 == st.l && j+1 == st. c)
                button = create_mouse_button(h_cell, w_cell);
            else if (i+1 == ed.l && j+1 == ed.c)
                    button = create_cheese_button(h_cell, w_cell);
                else if (matrix[i+1][j+1] == -1)
                        button = create_wall_button(h_cell, w_cell);
                    else button = create_floor_button();
            gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);    
        }
    return grid;
}

GtkWidget* create_window(char* name, int h, int w, GtkApplication *app)
{
    GtkWidget *window;
    gchar *nume = name; gint hl = h, wl = w;
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), nume);
    gtk_window_set_default_size(GTK_WINDOW(window), hl, wl);
    return window;
}

void myCSS()
{
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

void atribute(struct data* mydata, int matrix[][n_max], int nl, int nc, int h, int w, position st, position ed, char *name)
{
    mydata->nl = nl;
    mydata->nc = nc;
    mydata->h = h;
    mydata->w = w;
    mydata->st = st;
    mydata->ed = ed;
    int n = strlen(name);
    mydata->name = (char*)malloc((n+1)*sizeof(char));
    strcpy(mydata->name, name);
    int i, j;
    for (i = 0; i <= nl + 1; ++i)
        for (j = 0; j <= nc + 1; ++j)
            mydata->matrix[i][j] = matrix[i][j];

}

static void activate_inital(GtkApplication *app, gpointer user_data)
{
    myCSS();
    struct data *mydata = user_data;
    GtkWidget *window, *grid;
    window = create_window(mydata->name, mydata->h, mydata->w, app);
    grid = create_grid(mydata->matrix, mydata->st, mydata->ed, mydata->nl, mydata->nc, mydata->h, mydata->w);

    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
}

static gboolean update_grid_way(gpointer user_data)
{
    struct update_data *mydata = (struct update_data*)user_data;

    position *path = mydata->path;
    int poz = mydata->poz;
    if (poz == 0)
    {
        GtkWidget *button = gtk_grid_get_child_at(GTK_GRID(mydata->grid), path[poz].c-1, path[poz].l-1);
        update_run_button(button, mydata->h, mydata->w);

        mydata->poz ++;
        return TRUE;
    }
    if (poz == mydata->lg - 1)
    {
        //end position
        GtkWidget *button = gtk_grid_get_child_at(GTK_GRID(mydata->grid), path[poz].c-1, path[poz].l-1);
        update_find_button(button, mydata->h, mydata->w);

        // the passed position
        button = gtk_grid_get_child_at(GTK_GRID(mydata->grid), path[poz-1].c-1, path[poz-1].l-1);
        update_pass_button(button);

        return FALSE;
    }

    {
        //the passed position
        GtkWidget *button = gtk_grid_get_child_at(GTK_GRID(mydata->grid), path[poz-1].c-1, path[poz-1].l-1);
        update_pass_button(button);

        // the now position
        button = gtk_grid_get_child_at(GTK_GRID(mydata->grid), path[poz].c-1, path[poz].l-1);
        update_run_button(button, mydata->h, mydata->w);

        mydata->poz ++;
        return TRUE;
    }

}

static void activate_way(GtkApplication *app, gpointer user_data)
{
    myCSS();
    struct data *mydata = (struct data*)user_data;
    GtkWidget *window, *grid;
    window = create_window(mydata->name, mydata->h, mydata->w, app);
    grid = create_grid(mydata->matrix, mydata->st, mydata->ed, mydata->nl, mydata->nc, mydata->h, mydata->w);

    struct update_data *updata = (struct update_data*)malloc(1*sizeof(struct update_data));
    updata->grid = grid;
    updata->h = mydata->h/mydata->nl;
    updata->w = mydata->w/mydata->nc;
    updata->path = mydata->path;
    updata->lg = mydata->lg;
    updata->poz = 0;



    g_timeout_add(1000, G_SOURCE_FUNC(update_grid_way), updata);


    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
}

static gboolean update_grid_process(gpointer user_data)
{
    struct process_data *mydata = (struct process_data*)user_data;

    int poz = mydata->poz;


    int i, j;
    int n = mydata->nl, m = mydata->nc;
    if (poz != 1)
    {
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= m; ++j)
                if (mydata->matrix[i][j] == poz)
                {
                    GtkWidget *button = gtk_grid_get_child_at(GTK_GRID(mydata->grid), j-1, i-1);
                    update_pass_process_button(button);
                }
    }

    if (poz == mydata->matrix[mydata->ed.l][mydata->ed.c] - 1) ///suntem pe final
        return FALSE;

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            if (mydata->matrix[i][j] == poz + 1)
            {
                GtkWidget *button = gtk_grid_get_child_at(GTK_GRID(mydata->grid), j-1, i-1);
                update_process_button(button, poz);
            }
    
    mydata->poz = mydata->poz + 1;
    return TRUE;
}

static void activate_process(GtkApplication *app, gpointer user_data)
{
    myCSS();
    struct data *mydata = (struct data*)user_data;
    GtkWidget *window, *grid;
    window = create_window(mydata->name, mydata->h, mydata->w, app);
    grid = create_grid(mydata->matrix, mydata->st, mydata->ed, mydata->nl, mydata->nc, mydata->h, mydata->w);

    struct process_data *updata = (struct process_data*)malloc(1*sizeof(struct process_data));
    updata->st = mydata->st;
    updata->ed = mydata->ed;
    updata->poz = 1;
    updata->grid = grid;
    updata->nl = mydata->nl;
    updata->nc = mydata->nc;
    int i, j;
    for (i = 0; i <= mydata->nl + 1; ++i)
        for (j = 0; j <= mydata->nc +1; ++j)
            updata->matrix[i][j] = mydata->matrix[i][j];

    g_timeout_add(1000, G_SOURCE_FUNC(update_grid_process), updata);


    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
    
}

int run(int matrix[][n_max], int nl, int nc, position st, position ed, int h, int w, char* name, int task, ...)
{
    struct data local;
    atribute(&local, matrix, nl, nc, h, w, st, ed, name);
    
    GtkApplication *app; 
    int status;

    app = gtk_application_new("org.gtk.exemple", G_APPLICATION_FLAGS_NONE);
    switch(task)    
    {
        case initial: g_signal_connect(app, "activate", G_CALLBACK(activate_inital), &local); break;
        case way:
            va_list ptr;
            va_start(ptr, task);
            local.path = va_arg(ptr, position*);
            local.lg = va_arg(ptr, int);
            g_signal_connect(app, "activate", G_CALLBACK(activate_way), &local);
            break;
        case process: g_signal_connect(app, "activate", G_CALLBACK(activate_process), &local); break;
        default: break;
    }
    status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);

    return status;
    
}

#endif