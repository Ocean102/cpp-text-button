// Defining the header
#ifndef BUTTONS_H
#define BUTTONS_H

// Libaries
#include <iostream>
#include <windows.h>
#include <string>

// Namespace
using namespace std;

// Button Class
struct Button {
    int x, y, width;
    string label;
    bool hovered = false;
    bool rounded = false;
    string textColor = "\033[0m";
    string innerColor = "\033[0m";
    string borderColor = "\033[1;34m";
    string hoverColor = "\033[30;47m";
};

// Header Fuction
void newButton(Button& btn, void (*thread)());
void changeLabel(Button& btn);

#endif