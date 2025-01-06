#include "display.h"
#include "ssd1306_driver.h"


bool display_init() {
    ssd1306_driver_init();
}

void display_point(float x, float y) {
    // Convert -1.0 to 1.0 range to 0 to DISPLAY_WIDTH-1 for x and 0 to DISPLAY_HEIGHT-1 for y
    int x_mapped = (int)((x + 1) * (SSD1306_WIDTH / 2));
    int y_mapped = (int)((y + 1) * (SSD1306_HEIGHT / 2));
    
    ssd1306_draw_pixel(x_mapped, y_mapped);
}

void display_clear() {
    ssd1306_clear();
}


