# cpp-text-button

A premade terminal "clickable" and "customizable" button made for C++ using the built-in library for C++. This project allows you to create interactive buttons in the terminal with customizable styles, colors, and behaviors.

## Features
- **Customizable Button Appearance**: You can easily set text color, background color, border styles, and hover effects.
- **Interactive**: The button reacts to mouse events, making it possible to click on it within the terminal.
- **Terminal-Compatible**: Designed to work in text-based terminals with full compatibility for ANSI escape sequences.

## Installation
No installation is required as the file has been compiled. Just clone and run application.exe to check. If you want to make any changes to the button, please
install MinGW from https://sourceforge.net/projects/mingw/ and link it to the enviroment PATH settings to compile

```bash
g++ main.cpp -o application.exe
```

## Usage
The usage is very easy, just import and the header and windows.h then use! I optimized it a lot so i could work properly

```cpp
#include "buttons.h"
#include <windows.h>
#include <cstdlib>

void onButtonClick() {
  system("start cmd");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    system("chcp 65001 >nul");
    // style here if you want
    openCmd.rounded = true;
    Button openCmd = {2, 1, 20, "Open CMD"};

    //put new button into a while(true) to loop instead of just working once
    newButton(openCmd, onButtonClick);
    return 0;
}
```
