#include "clicker.h"
#include "../gui/gui.h"



void vars::i::scanner::thread() {
	while (gui::isRunning) {
        
        
        
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
        CURSORINFO mouse = { sizeof(CURSORINFO) };
        if (GetCursorInfo(&mouse) && &vars::clicker::inventory::enabled) {

            HCURSOR mousehandle = mouse.hCursor;

            if ((int)mousehandle > 65000 && (int)mousehandle < 66000) {

                vars::clicker::inventory::open = true;

            }
            else {

                vars::clicker::inventory::open = false;

            }

        }
	}
}