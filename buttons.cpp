#include "headers/buttons.h"
#include <windows.h>
#include <map>
#include <iostream>

string repeatString(const string& str, int length) {
    string rstr;
    for (int i = 0; i < length; i++) {
        rstr += str;
    }
    return rstr;
}

void changeLabel(Button& btn, string newLabel) {
    btn.label = newLabel;
}

void draw(const Button& btn) {
    // Neutral Color
    string ANSI_NEUTRAL_COLOR = "\033[0m";

    string btninnercolor = btn.innerColor;
    string borderColor = btn.borderColor;

    map<string, map<string, string>> styledBorders = {
        {"normal", {
            {"c_topleft", u8"┌"},
            {"c_topright", u8"┐"},
            {"c_botleft", u8"└"},
            {"c_botright", u8"┘"},
            {"pipe", u8"│"},
            {"dashes", u8"─"}
        }},
        {"rounded", {
            {"c_topleft", u8"╭"},
            {"c_topright", u8"╮"},
            {"c_botleft", u8"╰"},
            {"c_botright", u8"╯"},
            {"pipe", u8"│"},
            {"dashes", u8"─"}
        }}
    };

    map<string,string> border = styledBorders["normal"];

    if (btn.rounded)
        border = styledBorders["rounded"];

    if (btn.hovered)
        btninnercolor = btn.hoverColor;

    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int padding = (btn.width - 2 - btn.label.size()) / 2;

    pos = { (SHORT)btn.x, (SHORT)btn.y };
    SetConsoleCursorPosition(hConsole, pos);
    cout << borderColor << border["c_topleft"] << repeatString(border["dashes"], btn.width - 2) << border["c_topright"] << ANSI_NEUTRAL_COLOR;

    pos = { (SHORT)btn.x, (SHORT)(btn.y + 1) };
    SetConsoleCursorPosition(hConsole, pos);
    cout << borderColor << border["pipe"] << ANSI_NEUTRAL_COLOR << btninnercolor << string(padding, ' ') << btn.label
         << string(btn.width - 2 - padding - btn.label.size(), ' ') << ANSI_NEUTRAL_COLOR << borderColor << border["pipe"] << ANSI_NEUTRAL_COLOR;

    pos = { (SHORT)btn.x, (SHORT)(btn.y + 2) };
    SetConsoleCursorPosition(hConsole, pos);
    cout << borderColor << border["c_botleft"] << repeatString(border["dashes"], btn.width - 2) << border["c_botright"] << ANSI_NEUTRAL_COLOR;
    SetConsoleCursorPosition(hConsole, {(SHORT)0, (SHORT)0});
}


void newButton(Button& btn, void (*onClick)()) {
    while (true) {
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT);
        DWORD events;
        INPUT_RECORD inputRecord;

        ReadConsoleInput(hInput, &inputRecord, 1, &events);
        DWORD buttonState = inputRecord.Event.MouseEvent.dwButtonState;

        if (inputRecord.EventType == MOUSE_EVENT) {
            int mx = inputRecord.Event.MouseEvent.dwMousePosition.X;
            int my = inputRecord.Event.MouseEvent.dwMousePosition.Y;

            if (mx >= btn.x && mx <= btn.x + btn.width - 1 &&
                my >= btn.y && my <= btn.y + 2) {
                if (buttonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    onClick();
                }

                if (buttonState == 0) {
                    btn.hovered = true;
                }
            }
            else {
                btn.hovered = false;
            }
        }

        draw(btn);
    }
}