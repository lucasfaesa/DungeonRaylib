#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"

class Logger {
public:
    // Variadic function for logging
    static void Log(const char* format, ...) {
        char buffer[256];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        DrawText(buffer, x, y, fontSize_, color_);
        y += fontSize_ + 5;  // Move to the next line for the next message
    }

    // Reset y position for new frame
    static void ResetPosition() {
        y = initialY;
    }

private:
    static int x, y, initialY;  // Position on screen
    static int fontSize_;       // Font size
    static Color color_;        // Text color
};