#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string>
#include "SwinGame.h"

using namespace std;

const int GRIDWIDTH = 150;
const int GRIDHEIGHT = 75;

class Position {
    public:
        float x,y;
    private:

    };

class Grid {
    public:
        int id;
        int row;
        int column;
        Position pos;
        bool is_selected = false;
        bool is_onCursor = false;
        bool is_loaded = false;
    private:

};

class BaseSet {
    public:
        Grid grids[225];
        Grid *first_selected;
        Grid *last_selected;
        int map_size;
        int map_divider;
        int map_width;
        int map_height;
    private:

};

class GameData {
    public:
        BaseSet base;
        Position campos;
        Position radar;
        int zoom;
        bool is_devmode;
    private:

};

int zoomed(int val, int zoom) {
	return val * zoom;
}

void calculate_base_set(GameData *game) {
	///CALCULATES MAPS HEIGH, WIDTH AND MAPDIVIDER (COEFFICIENT FOR DETERMINING ROW AND COLUMN NO)///
	game->base.map_divider = round(sqrt(game->base.map_size));
	game->base.map_width = game->base.map_divider * zoomed(GRIDWIDTH, game->zoom);
	game->base.map_height = game->base.map_divider * zoomed(GRIDHEIGHT, game->zoom);
}

void calculate_campos(GameData *game) {
	///CALCULATES INITIAL CAMERA POSITION///
	game->campos.x = (screen_width() / -2) + zoomed(GRIDHEIGHT, game->zoom);
	game->campos.y = (game->base.map_height / 2) - (screen_height() / 2);
}

void load_resources() {
    load_bitmap_named("radar", "radar.png");
    load_bitmap_named("base", "base.png");
	load_bitmap_named("selectedBase", "sel_base.png");
	load_bitmap_named("cursorBase", "cursor_base.png");
}

void initialise_game(GameData *game) {
    int map_size_select = 1;
	load_resources();
	game->is_devmode = false;
	open_graphics_window("Base", 1280, 720);
    show_swin_game_splash_screen();
	game->zoom = 1;
	switch(map_size_select){
		case 1: game->base.map_size = 225; break;
		case 2: game->base.map_size = 400; break;
		case 3: game->base.map_size = 900; break;
		case 4: game->base.map_size = 1600; break;
		case 5: game->base.map_size = 2500; break;
	}
	calculate_base_set(game);
	cout << "divider: " << game->base.map_divider << endl;
        cout << "size : " << game->base.map_size << endl;
	calculate_campos(game);
	game->base.first_selected = nullptr;
	game->base.last_selected = nullptr;
}

void draw_radar(GameData *game) {
    float campos_x_to_zero, campos_y_to_zero;
	float map_radar_x_ratio, map_radar_y_ratio;
	float area_width, area_height;

	///CALCULATIONS TO MATCH MAPSIZE TO RADAR RATIO///
	area_width = (260 * screen_width() / (game->base.map_width + 250)) / game->zoom;
	area_height = (135 * screen_height() / (game->base.map_height + 250)) / game->zoom;
	campos_x_to_zero = game->campos.x + (zoomed(game->base.map_width, game->zoom) / 2) - zoomed(GRIDHEIGHT, game->zoom) + 125;
	campos_y_to_zero = game->campos.y + 125;
	map_radar_x_ratio = (zoomed(game->base.map_width, game->zoom) - screen_width() + 250) / (260 - area_width);
	map_radar_y_ratio = (zoomed(game->base.map_height, game->zoom) - screen_height() + 250) / (135 - area_height);

	///DRAWS SMALL SCALE MAP ON THE LEFT TOP///
	game->radar.x = 1000 + (campos_x_to_zero / map_radar_x_ratio);
	game->radar.y = 20 + (campos_y_to_zero / map_radar_y_ratio) ;
	draw_bitmap("radar", 1005, 25);
	draw_rectangle(color_red(), game->radar.x, game->radar.y, area_width, area_height);

	draw_text("Radar X :  to_string(game->radar.x)", color_red(), "arial.ttf", 14, 15, 150);
	draw_text("Radar Y : + round(game->radar.y", color_red(), "arial.ttf", 14, 15, 165);
	draw_text("areaWidth : + round(area_width)", color_red(), "arial.ttf", 14, 15, 180);
	draw_text("areaHeight : + round(area_height)", color_red(), "arial.ttf", 14, 15, 195);
}

void draw_grid(Grid *grid, GameData *game) {
	grid->pos.x = (grid->column - grid->row) * zoomed(GRIDHEIGHT, game->zoom) - game->campos.x;
	grid->pos.y = (grid->row + grid->column) * (zoomed(GRIDHEIGHT, game->zoom) / 2) - zoomed(GRIDHEIGHT, game->zoom) - game->campos.y;
	///DRAWS GRID BITMAPS FOR NORMAL, CURSOR ON IT AND SELECTED///
	if(grid->is_selected = false) { draw_bitmap("base.png", grid->pos.x, grid->pos.y); } // bitmap OptionScaleBmp(game->zoom, game->zoom));
	if(grid->is_onCursor = true) { draw_bitmap("cursorBase", grid->pos.x, grid->pos.y); } // OptionScaleBmp(game->zoom, game->zoom));
	if(grid->is_selected = true) { draw_bitmap("selectedBase", grid->pos.x, grid->pos.y); } // OptionScaleBmp(game->zoom, game->zoom));
}

void draw_game(GameData *game) {
	///DRAW GRIDS///
    for(int i = 0; i < game->base.map_size; i++){
        game->base.grids[i].id = i + 1;
		game->base.grids[i].row = trunc((game->base.grids[i].id -1) / game->base.map_divider) + 1;
		game->base.grids[i].column = (game->base.grids[i].id % game->base.map_divider);
		if (game->base.grids[i].column == 0){
            game->base.grids[i].column = game->base.map_divider;
		}
		draw_grid(&game->base.grids[i], game);
    }
    draw_radar(game);
}

void move_base(Position *campos, char direction, GameData *game){
	int move_speed = 5; ///BASE MOVE SPEED///
	int blind_sector = 2; ///BLIND SECTOR FOR MOUSE CURSOR ON THE WINDOW EDGES///
	int blank_sector = 125 * game->zoom; ///BLANK AREA LEFT ON THE EDGE OF THE BASE///

	if ((mouse_x() > blind_sector) && (mouse_x() < (screen_width() - blind_sector)) && (mouse_y() > blind_sector) && (mouse_y() < (screen_height() - blind_sector))){
		/// L = LEFT // R = RIGHT // U = UP // D = DOWN ///
		if((direction == 'L') && ((campos->x) > (zoomed(game->base.map_width, game->zoom) / -2) + GRIDHEIGHT - blank_sector)){
            campos->x = campos->x - move_speed;
        }
		if((direction == 'R') && ((campos->x) < (zoomed(game->base.map_width, game->zoom) / 2) - screen_width() + GRIDHEIGHT + blank_sector)){
            campos->x = campos->x + move_speed;
        }
		if((direction == 'U') && ((campos->y) > -blank_sector)){
            campos->y = campos->y - move_speed;
        }
		if((direction == 'D') && ((campos->y) < zoomed(game->base.map_height, game->zoom) - screen_height() + blank_sector)){
            campos->y = campos->y + move_speed;
        }
	}
}

void developer_mode(GameData *game){
	if(game->is_devmode == true){
		draw_text("FPS : ", color_red(), "arial.ttf", 14, 15, 15);
		draw_text("Mouse X : ", color_red(), "arial.ttf", 14, 15, 30);
		draw_text("Mouse Y : ", color_red(), "arial.ttf", 14, 15, 45);
		draw_text("Zoom : x", color_red(), "arial.ttf", 14, 15, 60);

		draw_text("Map Size :  ", color_red(), "arial.ttf", 14, 15, 90);
		draw_text("CamPos X :  ", color_red(), "arial.ttf", 14, 15, 105);
		draw_text("CamPos Y :  ", color_red(), "arial.ttf", 14, 15, 120);

		draw_text("Radar X : ", color_red(), "arial.ttf", 14, 15, 150);
		draw_text("Radar Y : ", color_red(), "arial.ttf", 14, 15, 165);

		///SHOWS GRID.ID, GRID.ROW AND GRID.COLUMN FOR EACH GRID. REDUCES FPS///
		if(key_down(VK_LALT)){
            for(int i = 0; i < game->base.map_size; i++){
			draw_text("base id: " , color_white(), "arial.ttf", 12, (game->base.grids[i].pos.x + 40), (game->base.grids[i].pos.y + 20));
			draw_text("row: xx  clmn: xx ", color_white(), "arial.ttf", 12, (game->base.grids[i].pos.x + 38), (game->base.grids[i].pos.y + 35));
            }
		}
		///SHOWS FIRST SELECTED AND LAST SELECTED GRID POINTERS///
		if(game->base.first_selected != nullptr){
            draw_text("first", color_red(), "arial.ttf", 14, game->base.first_selected->pos.x, game->base.first_selected->pos.y);
		}
		if (game->base.last_selected != nullptr){
            draw_text("last", color_red(), "arial.ttf", 14, game->base.last_selected->pos.x, game->base.last_selected->pos.y);
		}
    }
}

void user_input(GameData *game){
    ///BOUNDRIES FROM EDGES FOR MOVING MAP IN NORMAL SPEED AND DOUBLE SPEED///
    float normal_spd_limit = 50;
    float double_spd_limit = 25;
	/// L = LEFT // R = RIGHT // U = UP // D = DOWN ///
	///NORMAL SPEED MAP MOVE///
	if (mouse_x() < normal_spd_limit)
        {move_base(&game->campos, 'L', game);}
	if (mouse_x() > screen_width() - normal_spd_limit)
        {move_base(&game->campos, 'R', game);}
	if (mouse_y() < normal_spd_limit)
        {move_base(&game->campos, 'U', game); }
	if (mouse_y() > screen_height() - normal_spd_limit)
        {move_base(&game->campos, 'D', game);}
	///DOUBLE SPEED MAP MOVE///
	if (mouse_x() < double_spd_limit)
        {move_base(&game->campos, 'L', game);}
	if (mouse_x() > screen_width() - double_spd_limit)
        {move_base(&game->campos, 'R', game);}
	if (mouse_y() < double_spd_limit)
        {move_base(&game->campos, 'U', game); }
	if (mouse_y() > screen_height() - double_spd_limit)
        {move_base(&game->campos, 'D', game);}
	///GRID SELECTION AND HIGHLIGHTING///
	for(int i = 0; i < game->base.map_size; i++){
        //check_cursor_on_grid(game->base.grids[i], game);
        if (mouse_clicked(RIGHT_BUTTON))
            {game->base.grids[i].is_selected = false;}
	}
	///ZOOM IN & ZOOM OUT)///
	if (key_typed(VK_Q) && game->zoom < 8){
        game->zoom = round(game->zoom * 2);
        game->campos.x = (game->campos.x * 2) + (screen_width()/4) + 245;
        game->campos.y = (game->campos.y * 2) + (screen_height()/4) + 140;
    }
    if (key_typed(VK_E) && game->zoom > 1){
        game->zoom = round(game->zoom / 2);
        game->campos.x = (game->campos.x - 245 - (screen_width()/4)) / 2;
        game->campos.y = (game->campos.y - 140 - (screen_height()/4)) / 2;
    }
	///DEVELOPER MODE///
	if (key_down(VK_LCTRL) && key_typed(VK_TAB))
        {game->is_devmode = not (game->is_devmode);}
	developer_mode(game);

	draw_line(color_black(), 0, screen_height()/2, screen_width(),screen_height()/2);
	draw_line(color_black(), screen_width()/2, 0, screen_width()/2, screen_height());
}

int main() {
    GameData game;
    initialise_game(&game);
    do {
        process_events();
        refresh_screen(60);
        clear_screen(color_green());
        draw_game(&game);
        user_input(&game);

    } while ( ! window_close_requested() );

    release_all_resources();
    return 0;
}
