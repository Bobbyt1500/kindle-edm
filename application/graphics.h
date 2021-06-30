#ifndef KINDLE_EDM_GRAPHICS
#define KINDLE_EDM_GRAPHICS

#include <string>
#include "data.h"

class Graphics {
    private:
        // Rpm and Map arc
        void get_point_on_arc(int arc_centerx, int arc_centery, int arc_radius, int angle, float& xout, float& yout);
        int get_rpm_angle(int rpm);
        float get_map_angle(float map);
        void draw_arc_marker(int arc_centerx, int arc_centery, int arc_radius, int angle);
        void draw_arc_graphics(int arc_centerx, int arc_centery, int arc_radius, int lower_bound, int upper_bound, int markerspacing1, int markerspacing2);

        void draw_rpm(int rpm);
        void draw_map(float map);

        void draw_egt(int egt);
        void draw_cht(int cht);

        void draw_rect_info(float rectposx, float rectposy, std::string label, std::string units, std::string value, bool degrees = false);
        void draw_rect_limits(float rectposx, float rectposy, int lower_pos, int upper_pos, std::string lower_text, std::string upper_text, bool skip_upper = false);
        void draw_rect_marker(float rectposx, float rectposy, int lower_bound, int upper_bound, int lower_offset, float value);
        void draw_info_bars(int oil_pressure, int oil_temperature, float fuel_flow, int fuel_pressure, int fuel_quantityL, int fuel_quantityR);

        void draw_singular_info_text(float xpos, float ypos, std::string label, std::string value);
        void draw_info_texts(float volts, int amps);

        void draw_oat(int oat);
    public:
        void init();
        bool should_close();
        void draw(Data);
        void close();
};

#endif