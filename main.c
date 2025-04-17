#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <menu.h>

void start_sys() {
    ITEM **my_items;
    MENU *my_menu;
    int n_choices, i;
    char *choices[] = {
        "System Information",
        "Boot Sequence",
        "Memory Settings",
        "CPU Settings",
        "Power Management",
        "Load Setup Defaults",
        "Save & Exit",
        "Exit Without Saving",
        (char *)NULL
    };

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));

    n_choices = sizeof(choices) / sizeof(choices[0]) - 1;
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

    for(i = 0; i < n_choices; ++i) {
        my_items[i] = new_item(choices[i], "");
    }
    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);

    mvprintw(0, 0, "BIOS Setup Utility");
    mvprintw(LINES - 2, 0, "↑↓: Select Item  Enter: Select  ESC: Exit");

    post_menu(my_menu);
    refresh();

    while((i = getch()) != 27) {
        switch(i) {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
        }
    }

    free_item(my_items[0]);
    free_menu(my_menu);
    endwin();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <command>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "help") == 0) {
        printf("Available commands:\n");
        printf("  help    - Show this help message\n");
        return 0;
    }

    if (strcmp(argv[1], "start") == 0) {
        start_sys();
        return 0;
    }

    printf("Unknown command: %s\n", argv[1]);
    return 1;
}
