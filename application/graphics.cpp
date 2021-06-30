#include "graphics.h"
#include "raylib.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

Font DSEG;
Font OpenSans;

void Graphics::get_point_on_arc(int arc_centerx, int arc_centery, int arc_radius, int angle, float& xout, float& yout) {
    xout = arc_centerx + (arc_radius* sin(angle * 0.01745));
    yout = arc_centery + (arc_radius * cos(angle * 0.01745));
}

int Graphics::get_rpm_angle(int rpm) {
    return 230 - ((100 * (rpm - 1000)) / 1700);
}

float Graphics::get_map_angle(float map) {
    return 230 - ((100 * (map - 10)) / 32);
}

void Graphics::draw_arc_marker(int arc_centerx, int arc_centery, int arc_radius, int angle) {
    Vector2 point1a;
    Vector2 point2a;
    Vector2 point3a;
    Vector2 point1b;
    Vector2 point2b;
    Vector2 point3b;
    get_point_on_arc(arc_centerx, arc_centery, arc_radius - 18, angle, point1a.x, point1a.y);
    get_point_on_arc(arc_centerx, arc_centery, arc_radius + 15, angle - 5, point2a.x, point2a.y);
    get_point_on_arc(arc_centerx, arc_centery, arc_radius + 15, angle + 5, point3a.x, point3a.y);
    get_point_on_arc(arc_centerx, arc_centery, arc_radius - 28, angle, point1b.x, point1b.y);
    get_point_on_arc(arc_centerx, arc_centery, arc_radius + 25, angle - 8, point2b.x, point2b.y);
    get_point_on_arc(arc_centerx, arc_centery, arc_radius + 25, angle + 8, point3b.x, point3b.y);
    
    DrawTriangle(point1b, point2b, point3b, BLACK);
    DrawTriangle(point1a, point2a, point3a, WHITE);
}

void Graphics::draw_arc_graphics(int arc_centerx, int arc_centery, int arc_radius, int lower_bound, int upper_bound, int markerspacing1, int markerspacing2) {
    Vector2 arc_center = {arc_centerx, arc_centery};
    DrawCircleSector(arc_center, arc_radius+2, 240, 120, 30, WHITE);
    DrawCircleSector(arc_center, arc_radius, 239.5, 230, 30, BLACK);
    DrawCircleSector(arc_center, arc_radius, 130, 120.5, 30, BLACK);
    DrawCircleSector(arc_center, arc_radius, 230, 130, 30, GREEN);
    DrawCircleSector(arc_center, arc_radius-20, 240, 120, 30, WHITE);
    DrawCircleSector(arc_center, arc_radius-22, 240, 120, 30, BLACK);
    
    // first markers
    for (int i = lower_bound; i < upper_bound; i += markerspacing1) {
        float x1, y1, x2, y2;
        int angle = 230 - ((100 * (i - lower_bound)) / (upper_bound - lower_bound));
        get_point_on_arc(arc_center.x, arc_center.y, arc_radius, angle, x1, y1);
        get_point_on_arc(arc_center.x, arc_center.y, arc_radius-40, angle, x2, y2);
        DrawLineEx({x1, y1}, {x2, y2}, 3.0, WHITE);
    }

    // second markers
    for (int i = lower_bound; i < upper_bound; i += markerspacing2) {
        if (i % markerspacing1 == 0) continue;

        float x1, y1, x2, y2;
        int angle = 230 - ((100 * (i - lower_bound)) / (upper_bound - lower_bound));
        get_point_on_arc(arc_center.x, arc_center.y, arc_radius-22, angle, x1, y1);
        get_point_on_arc(arc_center.x, arc_center.y, arc_radius-30, angle, x2, y2);
        DrawLineEx({x1, y1}, {x2, y2}, 1.0, WHITE);
    }

    
}

void Graphics::draw_rpm(int rpm) {

    // Adjust out of bounds
    int adjusted_rpm =  std::max(rpm, 800);

    // Display Arc
    Vector2 arc_center = {450, 250};
    int arc_radius = 200;
    draw_arc_graphics(arc_center.x, arc_center.y, arc_radius, 1000, 2700, 500, 50);
    

    // Limit marker
    float x1, y1, x2, y2;
    int angle = get_rpm_angle(2700);
    get_point_on_arc(arc_center.x, arc_center.y, arc_radius+15, angle, x1, y1);
    get_point_on_arc(arc_center.x, arc_center.y, arc_radius-40, angle, x2, y2);
    DrawLineEx({x1, y1}, {x2, y2}, 5.0, {252, 3, 3, 255});
    DrawLineEx({x1, y1}, {x1, y1-25}, 1.0, {252, 3, 3, 255});
    DrawTextEx(OpenSans, "2700", {x1-35, y1-50}, 30, 1, {252, 3, 3, 255});

    // Informational text
    int text_size = MeasureTextEx(DSEG, std::to_string(rpm).c_str(), 55, 3).x;

    DrawTextEx(DSEG, std::to_string(rpm).c_str(), {arc_center.x - text_size/2, arc_center.y - 120}, 55, 3, WHITE);

    DrawTextEx(OpenSans, "RPM", {arc_center.x-200, arc_center.y-245}, 50, 3, WHITE);
    
    
    // Triangle marker
    draw_arc_marker(arc_center.x, arc_center.y, arc_radius, get_rpm_angle(adjusted_rpm));

}

void Graphics::draw_map(float map) {
    // Adjust out of bounds
    int adjusted_map = std::max(map, 8.0f);

    // Display Arc
    Vector2 arc_center = {825, 250};
    int arc_radius = 200;
    draw_arc_graphics(arc_center.x, arc_center.y, arc_radius, 10, 42, 10, 2);

    // Limit marker
    float x1, y1, x2, y2;
    int angle = get_map_angle(42);
    get_point_on_arc(arc_center.x, arc_center.y, arc_radius+15, angle, x1, y1);
    get_point_on_arc(arc_center.x, arc_center.y, arc_radius-40, angle, x2, y2);
    DrawLineEx({x1, y1}, {x2, y2}, 5.0, {252, 3, 3, 255});
    DrawLineEx({x1, y1}, {x1, y1-25}, 1.0, {252, 3, 3, 255});
    DrawTextEx(OpenSans, "42.0", {x1-30, y1-50}, 30, 1, {252, 3, 3, 255});

    // Informational text
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << map;
    std::string map_str = ss.str();
    int text_size = MeasureTextEx(DSEG, map_str.c_str(), 55, 3).x;

    DrawTextEx(DSEG, map_str.c_str(), {arc_center.x - text_size/2, arc_center.y - 120}, 55, 3, WHITE);

    DrawTextEx(OpenSans, "MAP", {arc_center.x-200, arc_center.y-245}, 50, 3, WHITE);
    
    
    // Triangle marker
    draw_arc_marker(arc_center.x, arc_center.y, arc_radius, get_map_angle(adjusted_map));
}

void Graphics::draw_egt(int egt) {
    DrawTextEx(OpenSans, "EGT", {275, 530}, 40, 1, GREEN);
    DrawTextEx(DSEG, std::to_string(egt).c_str(), {350, 520}, 55, 1, WHITE);
}

void Graphics::draw_cht(int cht) {
    DrawTextEx(OpenSans, "CHT", {575, 530}, 40, 1, BLUE);
    DrawTextEx(DSEG, std::to_string(cht).c_str(), {650, 520}, 55, 1, WHITE);
}

void Graphics::draw_rect_info(float rectposx, float rectposy, std::string label, std::string units, std::string value, bool degrees) {
    DrawTextEx(OpenSans, label.c_str(), {rectposx, rectposy + 26}, 20, 1, WHITE);
    DrawTextEx(OpenSans, value.c_str(), {rectposx + 215 - (MeasureTextEx(OpenSans, value.c_str(), 30, 1).x), rectposy + 22}, 30, 1, WHITE);
    if (degrees) {
        DrawRing({rectposx + 222, rectposy + 32}, 1.5, 2.5, 0, 360, 30, WHITE);
    }
    DrawTextEx(OpenSans, units.c_str(), {rectposx + 225, rectposy + 26}, 20, 1, WHITE);
}

void Graphics::draw_rect_limits(float rectposx, float rectposy, int lower_pos, int upper_pos, std::string lower_text, std::string upper_text, bool skip_upper) {
    Color edmred = {252, 3, 3, 255};
    DrawTextEx(OpenSans, lower_text.c_str(), {(rectposx + lower_pos) - (MeasureTextEx(OpenSans, lower_text.c_str(), 25, 1).x / 2), rectposy - 37}, 25, 1, edmred);
    DrawLineEx({rectposx + lower_pos, rectposy - 10}, {rectposx + lower_pos, rectposy + 24}, 3.0, edmred);

    if (!skip_upper) {
        DrawTextEx(OpenSans, upper_text.c_str(), {(rectposx + upper_pos) - (MeasureTextEx(OpenSans, upper_text.c_str(), 25, 1).x / 2), rectposy - 37}, 25, 1, edmred);
        DrawLineEx({rectposx + upper_pos, rectposy - 10}, {rectposx + upper_pos, rectposy + 24}, 3.0, edmred);
    }
}

void Graphics::draw_rect_marker(float rectposx, float rectposy, int lower_bound, int upper_bound, int lower_offset, float value) {
    float triangle_posx = rectposx + lower_offset + ((200 * (value - lower_bound)) / (upper_bound - lower_bound));
    DrawTriangle({triangle_posx, rectposy + 24}, {triangle_posx + 15, rectposy - 12}, {triangle_posx - 15, rectposy - 12}, BLACK);
    DrawTriangle({triangle_posx, rectposy + 22}, {triangle_posx + 12, rectposy - 10}, {triangle_posx - 12, rectposy - 10}, WHITE);
}

void Graphics::draw_info_bars(int oil_pressure, int oil_temperature, float fuel_flow, int fuel_pressure, int fuel_quantityL, int fuel_quantityR) {
    Color edmred = {252, 3, 3, 255};
    // Oil Temperature
    int adjusted_oil_temperature = oil_temperature;
    if (oil_temperature < 85) adjusted_oil_temperature = 85;

    Vector2 oiltpos = {250, 250};
    DrawRectangle(oiltpos.x, oiltpos.y, 250, 24, WHITE);
    DrawRectangle(oiltpos.x + 25, oiltpos.y + 2, 200, 20, GREEN);
    DrawRectangle(oiltpos.x + 2, oiltpos.y + 2, 23, 20, BLACK);
    DrawRectangle(oiltpos.x + 225, oiltpos.y + 2, 23, 20, BLACK);

    draw_rect_limits(oiltpos.x, oiltpos.y, 25, 225, "100", "240");
    draw_rect_marker(oiltpos.x, oiltpos.y, 100, 240, 25, adjusted_oil_temperature);
    draw_rect_info(oiltpos.x, oiltpos.y, "OIL-T", "F", std::to_string(oil_temperature), true);
    
    // Oil Pressure
    Vector2 oilppos = {250, 350};
    DrawRectangle(oilppos.x, oilppos.y, 250, 24, WHITE);
    DrawRectangle(oilppos.x + 25, oilppos.y + 2, 200, 20, GREEN);
    DrawRectangle(oilppos.x + 25, oilppos.y + 2, 78, 20, YELLOW);
    DrawRectangle(oilppos.x + 205, oilppos.y + 2, 20, 20, YELLOW);
    DrawRectangle(oilppos.x + 2, oilppos.y + 2, 23, 20, BLACK);
    DrawRectangle(oilppos.x + 225, oilppos.y + 2, 23, 20, BLACK);

    draw_rect_limits(oilppos.x, oilppos.y, 25, 225, "10", "100");
    draw_rect_marker(oilppos.x, oilppos.y, 10, 100, 25, oil_pressure);
    draw_rect_info(oilppos.x, oilppos.y, "OIL-P", "PSI", std::to_string(oil_pressure));

    // Fuel Flow
    Vector2 fuelfpos = {250, 450};
    DrawRectangle(fuelfpos.x, fuelfpos.y, 250, 24, WHITE);
    DrawRectangle(fuelfpos.x + 10, fuelfpos.y + 2, 238, 20, GREEN);
    DrawRectangle(fuelfpos.x + 2, fuelfpos.y + 2, 8, 20, BLACK);
    draw_rect_limits(fuelfpos.x, fuelfpos.y, 10, 0, "1.0", "0", true);
    draw_rect_marker(fuelfpos.x, fuelfpos.y, 1, 25, 10, fuel_flow);

    // Information text
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << fuel_flow;
    std::string ff_str = ss.str();
    draw_rect_info(fuelfpos.x, fuelfpos.y, "FUEL-F", "GPH", ff_str);

    // Fuel Pressure
    Vector2 fuelppos = {550, 250};
    DrawRectangle(fuelppos.x, fuelppos.y, 250, 24, WHITE);
    DrawRectangle(fuelppos.x + 25, fuelppos.y + 2, 200, 20, GREEN);
    DrawRectangle(fuelppos.x + 225, fuelppos.y + 2, 23, 20, BLACK);
    DrawRectangle(fuelppos.x + 2, fuelppos.y + 2, 23, 20, BLACK);

    draw_rect_limits(fuelppos.x, fuelppos.y, 25, 225, "3", "35");
    draw_rect_marker(fuelppos.x, fuelppos.y, 3, 35, 25, fuel_pressure);
    draw_rect_info(fuelppos.x, fuelppos.y, "FUEL-P", "PSI", std::to_string(fuel_pressure));


    // L fuel quantity
    Vector2 fuellpos = {550, 350};
    DrawRectangle(fuellpos.x, fuellpos.y, 250, 24, WHITE);
    DrawRectangle(fuellpos.x + 10, fuellpos.y + 2, 150, 20, GREEN);
    DrawRectangle(fuellpos.x + 160, fuellpos.y + 2, 88, 20, BLACK);
    DrawRectangle(fuellpos.x + 2, fuellpos.y + 2, 8, 20, BLACK);

    draw_rect_limits(fuellpos.x, fuellpos.y, 10, 0, "1", "0", true);
    draw_rect_marker(fuellpos.x, fuellpos.y, 1, 35, 10, fuel_quantityL);
    draw_rect_info(fuellpos.x, fuellpos.y, "L-FUEL", "GAL", std::to_string(fuel_quantityL));

    // R fuel quantity
    Vector2 fuelrpos = {550, 450};
    DrawRectangle(fuelrpos.x, fuelrpos.y, 250, 24, WHITE);
    DrawRectangle(fuelrpos.x + 10, fuelrpos.y + 2, 150, 20, GREEN);
    DrawRectangle(fuelrpos.x + 2, fuelrpos.y + 2, 8, 20, BLACK);
    DrawRectangle(fuelrpos.x + 160, fuelrpos.y + 2, 88, 20, BLACK);

    draw_rect_limits(fuelrpos.x, fuelrpos.y, 10, 0, "1", "0", true);
    draw_rect_marker(fuelrpos.x, fuelrpos.y, 1, 35, 10, fuel_quantityR);
    draw_rect_info(fuelrpos.x, fuelrpos.y, "R-FUEL", "GAL", std::to_string(fuel_quantityR));

}

void Graphics::draw_singular_info_text(float xpos, float ypos, std::string label, std::string value) {
    DrawTextEx(OpenSans, label.c_str(), {xpos, ypos}, 35, 1, GRAY);
    DrawTextEx(OpenSans, value.c_str(), {xpos + 100, ypos}, 35, 1, WHITE);

}

void Graphics::draw_info_texts(float volts, int amps) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << volts;
    std::string volts_str = ss.str();
    draw_singular_info_text(820, 300, "VOLTS", volts_str);
    draw_singular_info_text(820, 350, "AMPS", std::to_string(amps));
}

void Graphics::draw_oat(int oat) {
    float xpos = 880;
    float ypos = 200;
    DrawRectangle(xpos, ypos, 144, 50, WHITE);
    DrawRectangle(xpos + 2, ypos + 2, 140, 46, {12, 0, 145, 255});
    DrawTextEx(OpenSans, "OAT", {xpos + 10, ypos + 10}, 30, 1, WHITE);
    DrawTextEx(OpenSans, std::to_string(oat).c_str(), {xpos + 75, ypos + 5}, 40, 1, WHITE);
    DrawRing({xpos + 122, ypos + 15}, 1.5, 2.5, 0, 360, 30, WHITE);
    DrawTextEx(OpenSans, "F", {xpos + 125, ypos + 10}, 30, 1, WHITE);
}

void Graphics::init() {
    const int screenWidth = 1024;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "KindleEDM");
    SetWindowState(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
    SetWindowPosition(2560, 0);
    SetTargetFPS(20); 
    

    DSEG = LoadFont("resources/DSEG7-Classic/DSEG7Classic-BoldItalic.ttf");
    OpenSans = LoadFont("resources/OpenSans/OpenSans-Bold.ttf");
    SetTextureFilter(DSEG.texture, FILTER_BILINEAR); 
}

bool Graphics::should_close() {
    return WindowShouldClose();
}

void Graphics::draw(Data data) {
    BeginDrawing();

    ClearBackground(BLACK);

    if (data.on == 1) {

        draw_rpm(data.rpm);
        draw_map(data.map);

        draw_cht(data.cht);
        draw_egt(data.egt);

        draw_info_bars(data.oilp, data.oilt, data.fuelf, data.fuelp, data.fuelL, data.fuelR);

        draw_info_texts(data.volts, data.amps);

        draw_oat(data.oat);

        // Seperator Line
        DrawLineEx({250, 200}, {1024, 200}, 2.0, WHITE);
    }

    EndDrawing();
}

void Graphics::close() {
    UnloadFont(DSEG);
    UnloadFont(OpenSans);
    CloseWindow(); 
}