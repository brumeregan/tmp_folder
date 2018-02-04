#include <ncurses.h>
#include <menu.h>

#include <cstring>
#include <cstdlib>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char choices[][10] = {
        "lab1",
        "lab2",
        "lab3",
        "lab4",
        "lab5"
};

int main(int argc, char *argv[])
{
    ITEM **items;
    int c;
    MENU *menu;
    int n_choices, i;
    ITEM *current;

    /* Initialize items */
    n_choices = ARRAY_SIZE(choices);
    items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for(i = 0; i < n_choices; ++i)
        items[i] = new_item(choices[i], NULL);
    items[n_choices] = (ITEM *)NULL;

    menu = new_menu((ITEM **)items);

    initscr();
    start_color();
    cbreak();
    keypad(stdscr, true);

    // get screen size
    int yMax, xMax;
    getmaxyx(curscr, yMax, xMax);

    // create windows for the menu and output
    WINDOW * menu_win = newwin(yMax/3, xMax, 0, 0);
    WINDOW * output = newwin(yMax/3 * 2 + 1, xMax, yMax/3, 0);
    refresh();

    box(menu_win, 0, 0);
    mvwprintw(menu_win, 0, 1, "Menu:");
    mvwprintw(output, 0, 1, "Output:");
    wrefresh(output);
    set_menu_win(menu, menu_win);
    set_menu_sub(menu, derwin(menu_win, 6, 68, 1, 1));
    set_menu_format(menu, 5, 1);
    set_menu_mark(menu, ">> ");
    wmove(menu_win, 3, 3);
    wrefresh(menu_win);
    post_menu(menu);
    wrefresh(menu_win);

    while((c = getch()) != 27)
    {
        char args[80];
        switch(c)
        {       case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case KEY_LEFT:
                mvwprintw(menu_win, 10, 1, "Enter CLI arguments:\n");
                wmove(menu_win, 11, 1);
                wrefresh(menu_win);
                mvwgetstr(menu_win, 11, 1, args);
                break;
            case 10:	/* Enter */
                wclear(output);
                mvwprintw(output, 0, 1, "Output:");

                wmove(output,1, 0);
                wrefresh(output);
                char str[80];
                strcpy(str, "./cmake-build-debug/");
                strcat(str, item_name(current_item(menu)));
                strcat(str, " ");
                strcat(str, args);
                reset_shell_mode();
                system(str);
                reset_prog_mode();
                break;
        }
        wrefresh(menu_win);
    }
    endwin();
    return 0;
}
