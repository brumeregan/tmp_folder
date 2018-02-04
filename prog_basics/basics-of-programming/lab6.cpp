#include <cstring>
#include <cstdlib>

#include <ncurses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char projects[][10] = {
        "lab1",
        "lab2",
        "lab3",
        "lab4",
        "lab5"
};

int main(int argc, char *argv[]) {
    ITEM **items;
    MENU *menu;
    int key_pressed,
        num_project,
        i;

    num_project = ARRAY_SIZE(projects);
    items = (ITEM **)calloc(num_project + 1, sizeof(ITEM *));
    for(i = 0; i < num_project; ++i)
        items[i] = new_item(projects[i], NULL);
    items[num_project] = (ITEM *)NULL;

    menu = new_menu((ITEM **)items);

    initscr();
    start_color();
    cbreak();
    keypad(stdscr, true);

    // data for screen params
    int max_x, max_y;
    getmaxyx(curscr, max_y, max_x);

    // create separated window
    WINDOW *menu_win = newwin(max_y/3, max_x, 0, 0);
    WINDOW *result = newwin(max_y/3 * 2 + 1, max_x, max_y/3, 0);
    refresh();

    box(menu_win, 0, 0);
    mvwprintw(menu_win, 1, 1, "Menu:");
    mvwprintw(result, 0, 1, "Result:");
    wrefresh(result);
    set_menu_win(menu, menu_win);
    set_menu_sub(menu, derwin(menu_win, 6, 68, 2, 1));
    set_menu_format(menu, 5, 1);
    set_menu_mark(menu, "# ");
    wmove(menu_win, 3, 3);
    wrefresh(menu_win);
    post_menu(menu);
    wrefresh(menu_win);

    while((key_pressed = getch()) != 27) {
        char args[80];
        switch(key_pressed) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case KEY_LEFT:
            case KEY_RIGHT:
                mvwprintw(menu_win, 10, 1, "Enter CLI arguments:\n");
                wmove(menu_win, 11, 1);
                wrefresh(menu_win);
                mvwgetstr(menu_win, 11, 1, args);
                break;
            case 10:
                wclear(result);
                mvwprintw(result, 0, 1, "Result:");

                wmove(result,1, 0);
                wrefresh(result);
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
