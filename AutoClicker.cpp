/**
 * @author Thomas Rudolph <me@holloway-web.de>
 * @since 2017.03.19
 */

#include <csignal>
#include <unistd.h>
#include <X11/extensions/XTest.h>

#include "AutoClicker.hpp"

/**
 * Determines if the program is running.
 */
bool AutoClicker::running;

/**
 * Checks for the hotkey and de-/activates the auto mouse click.
 */
void AutoClicker::checkKeyEvent() {
    if (0 >= XPending(display)) {
        return;
    }

    XNextEvent(display, &ev);
    switch (ev.type) {
        case KeyRelease:
            if (ev.xkey.state & Mod1Mask) {
                clicking = !clicking;
            }
            break;
        default:
            break;
    }
}

/**
 * Perform an auto mouse click at the current location.
 */
void AutoClicker::clickMouse() {
    XTestFakeButtonEvent(display, 1, True, CurrentTime);
    XTestFakeButtonEvent(display, 1, False, CurrentTime);
    XFlush(display);
}

/**
 * Initializes the display, window and hotkey grabbing.
 *
 * @return 1 if display could not be opened, otherwise 0
 */
int AutoClicker::init() {
    signal(SIGKILL, AutoClicker::signalHandler);
    signal(SIGINT, AutoClicker::signalHandler);
    signal(SIGTERM, AutoClicker::signalHandler);

    if (!(display = XOpenDisplay(NULL))) {
        return 1;
    }

    hotkey = XKeysymToKeycode(display, XK_a);
    window = DefaultRootWindow(display);
    XGrabKey(display, hotkey, Mod1Mask, window, False, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, hotkey, Mod1Mask | Mod2Mask, window, False, GrabModeAsync, GrabModeAsync);
    XSelectInput(display, window, KeyReleaseMask);

    clicking = false;
    AutoClicker::running = true;

    return 0;
}

/**
 * Main loop for auto clicker.
 */
void AutoClicker::loop() {
    while (AutoClicker::running) {
        checkKeyEvent();

        if (clicking) {
            clickMouse();
        }
        usleep(100'000);
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
/**
 * Stops the program via a signal.
 *
 * @param signal
 */
void AutoClicker::signalHandler(int signal) {
    AutoClicker::running = false;
}
#pragma clang diagnostic pop

/**
 * Shut down key grabbing and display access.
 */
void AutoClicker::shutdown() {
    XUngrabKey(display, hotkey, Mod1Mask, window);
    XUngrabKey(display, hotkey, Mod1Mask | Mod2Mask, window);
    XCloseDisplay(display);
}
