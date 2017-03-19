/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.19
 */

#ifndef HWAUTOCLICKER_AUTOCLICKER_HPP
#define HWAUTOCLICKER_AUTOCLICKER_HPP


#include <X11/keysym.h>
#include <X11/Xlib.h>

class AutoClicker {
private:
    Display *display;
    bool clicking;
    XEvent ev;
    KeyCode hotkey;
    static bool running;
    Window window;

    void checkKeyEvent();
    void clickMouse();
public:
    int init();
    void loop();
    void static signalHandler(int signal);
    void shutdown();
};


#endif //HWAUTOCLICKER_AUTOCLICKER_HPP
