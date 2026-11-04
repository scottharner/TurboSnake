
#include <stdio.h>
#include "../../platform.h"
#include "huc.h"

/*
*   Snake: Turbografx implementation of snake using hucc framework.
*   Last Update: Nov 3, 2026
*   Author: Scott Harner
*/

#define SCREEN_HEIGHT 28
#define SCREEN_WIDTH 32
#define HALF_SCREEN_WIDTH 16
#define MAP_HEIGHT 25 // map has to be slightly smaller on turbo so tiles dont overwrite
#define MAP_WIDTH 30
#define TILE_SIZE 8
#define BLACK_COLOR_INDEX 0
#define WHITE_COLOR_INDEX 225
#define YELLOW_COLOR_INDEX 241
#define WHITE_PALETTE_INDEX 14
#define YELLOW_PALETTE_INDEX 15
#define TITLE_TRACKID 2
#define GAME_TRACKID 3

#incchr(title_tiles, "../assets/images/title.png", 0, 0, 32, 6, _OPTIMIZE)
#incpal(title_palette, "../assets/images/title.png", 0, 1)
#incbat(title_map, "../assets/images/title.png", 0x1000, 32, 6, title_tiles)
#incchr(credits_tiles, "../assets/images/credits.png", 0, 0, 12, 5, _OPTIMIZE)
#incpal(credits_palette, "../assets/images/credits.png", 0, 1)
#incbat(credits_map, "../assets/images/credits.png", 0x1000, 12, 5, credits_tiles)
#incchr(gameover_tiles, "../assets/images/gameover.png", 0, 0, 12, 5, _OPTIMIZE)
#incpal(gameover_palette, "../assets/images/gameover.png", 0, 1)
#incbat(gameover_map, "../assets/images/gameover.png", 0x1000, 12, 5, gameover_tiles)
#incchr(youwin_tiles, "../assets/images/youwin.png", 0, 0, 12, 5, _OPTIMIZE)
#incpal(youwin_palette, "../assets/images/youwin.png", 0, 1)
#incbat(youwin_map, "../assets/images/youwin.png", 0x1000, 12, 5, youwin_tiles)

#incchr(bordertl_tile, "../assets/tiles/bordertl.png")
#incchr(bordertr_tile, "../assets/tiles/bordertr.png")
#incchr(borderbl_tile, "../assets/tiles/borderbl.png")
#incchr(borderbr_tile, "../assets/tiles/borderbr.png")
#incchr(borderl_tile, "../assets/tiles/borderl.png")
#incchr(borderr_tile, "../assets/tiles/borderr.png")
#incchr(bordert_tile, "../assets/tiles/bordert.png")
#incchr(borderb_tile, "../assets/tiles/borderb.png")

#incpal(game_palette, "../assets/tiles/bordertl.png", 0, 1)

#define TILE_BORDER_TL  0x100
#define TILE_BORDER_TR  0x101
#define TILE_BORDER_BL  0x102
#define TILE_BORDER_BR  0x103
#define TILE_BORDER_L   0x104
#define TILE_BORDER_R   0x105
#define TILE_BORDER_T   0x106
#define TILE_BORDER_B   0x107

#define TILE_BORDER_TL_ADDRESS 0x1000
#define TILE_BORDER_TR_ADDRESS 0x1010
#define TILE_BORDER_BL_ADDRESS 0x1020
#define TILE_BORDER_BR_ADDRESS 0x1030
#define TILE_BORDER_L_ADDRESS 0x1040
#define TILE_BORDER_R_ADDRESS 0x1050
#define TILE_BORDER_T_ADDRESS 0x1060
#define TILE_BORDER_B_ADDRESS 0x1070

#incchr(apple_tile, "../assets/tiles/apple.png")
#incchr(snake_tile, "../assets/tiles/snake.png")
#incchr(empty_tile, "../assets/tiles/empty.png")

#define TILE_APPLE  0x108
#define TILE_SNAKE  0x109
#define TILE_EMPTY  0x10A

#define TILE_APPLE_ADDRESS 0x1080
#define TILE_SNAKE_ADDRESS 0x1090
#define TILE_EMPTY_ADDRESS 0x10A0

#define GAME_TILE_SIZE 0x0010

// Turbografx implementation of platform initialization
void platform_initialize()
{
    set_color_rgb(WHITE_COLOR_INDEX, 7, 7, 7);
    set_color_rgb(YELLOW_COLOR_INDEX, 7, 7, 0);
	set_font_color(WHITE_COLOR_INDEX, BLACK_COLOR_INDEX);
	set_font_pal(WHITE_PALETTE_INDEX);
	load_default_font();
    
    // load sfx
    ad_trans(2, 0x0000, 3, 0x0000); // pickup sound
    ad_trans(3, 0x0000, 7, 0x1800); // lose sound
}

// plays the requested sound effect
void platform_play_sound(sound_type current_sound_type)
{
    if (current_sound_type == SOUND_PICKUP)
    {
        ad_play(0x0000, 6144, ADPLAY_FREQ_16KHZ, ADPLAY_AUTOSTOP);
    }
    else if (current_sound_type == SOUND_LOSE)
    {
        ad_play(0x1800, 14336, ADPLAY_FREQ_16KHZ, ADPLAY_AUTOSTOP);
    }
}

static int get_centered_x_coord(char * text)
{
    int length;

    length = 0;
    while (text[length] != '\0')
    {
        length++;
    }

    return (SCREEN_WIDTH - length ) / 2;
}

// display a game over screen
void platform_draw_game_over_screen(int score, bool did_mode_change, loss_type current_loss_type)
{
    char score_string[12];
    char reason_string[25];
    char formatted_output_string[40];
    if (did_mode_change)
    {
        cd_reset(); // stop game music
        cls();
        load_vram(0x1000, gameover_tiles, 0x03C0);
        load_palette(0, gameover_palette, 1);
        load_bat(0x014A, gameover_map, 12, 5); // start mid 6th row
    }

    set_font_pal(WHITE_PALETTE_INDEX);
    sprintf(score_string, "Score: %d", score);
    sprintf(formatted_output_string, "\e%dX\e10Y%s", get_centered_x_coord(score_string), score_string);
    printf(formatted_output_string);
    sprintf(reason_string, "Reason: %s", current_loss_type == LOSS_TYPE_SELF ? "Self Collision" : "Wall Collision");
    sprintf(formatted_output_string, "\e%dX\e12Y%s", get_centered_x_coord(reason_string), reason_string);
    printf(formatted_output_string);
}

// display a win screen
void platform_draw_win_screen(int score, bool did_mode_change)
{
    char score_string[12];
    char formatted_score_string[20];
    if (did_mode_change)
    {
        cd_reset(); // stop game music
        cls();
        load_vram(0x1000, youwin_tiles, 0x03C0);
        load_palette(0, youwin_palette, 1);
        load_bat(0x014A, youwin_map, 12, 5); // start mid 6th row
    }

    set_font_pal(WHITE_PALETTE_INDEX);
    sprintf(score_string, "Score: %d", score);
    sprintf(formatted_score_string, "\e%dX\e10Y%s", get_centered_x_coord(score_string), score_string);
    printf(formatted_score_string);
}

// display a credits screen
void platform_draw_credits_screen(bool did_mode_change)
{
    char credit_string[50];
    if (did_mode_change)
    {
        cd_reset(); // stop game music
        cls();
        load_vram(0x1000, credits_tiles, 0x03C0);
        load_palette(0, credits_palette, 1);
        load_bat(0x000A, credits_map, 12, 5);
    }

    set_font_pal(WHITE_PALETTE_INDEX);
    sprintf(credit_string, "\e%dX\e7YGame Engineer - Stephen Bryant", get_centered_x_coord("Game Engineer - Stephen Bryant"));
	printf(credit_string);
    sprintf(credit_string, "\e%dX\e9YPort Engineer - Scott Harner", get_centered_x_coord("Port Engineer - Scott Harner"));
	printf(credit_string);
    sprintf(credit_string, "\e%dX\e11YQA Tester - Evan Harner", get_centered_x_coord("QA Tester - Evan Harner"));
	printf(credit_string);
    sprintf(credit_string, "\e%dX\e13YMusic - Safety Stoat Studios", get_centered_x_coord("Music - Safety Stoat Studios"));
	printf(credit_string);
    sprintf(credit_string, "\e%dX\e15YSound Effects - Kronbits", get_centered_x_coord("Sound Effects - Kronbits"));
	printf(credit_string);
    sprintf(credit_string, "\e%dX\e17YAdvisor - DarkKobold", get_centered_x_coord("Advisor - DarkKobold"));
	printf(credit_string);
    sprintf(credit_string, "\e%dX\e19YAdvisor - Elmer", get_centered_x_coord("Advisor - Elmer"));
	printf(credit_string);
    sprintf(credit_string, "\e%dX\e21YAdvisor - Kaminari", get_centered_x_coord("Advisor - Kaminari"));
	printf(credit_string);
    sprintf(credit_string, "\e%dX\e23YAdvisor - turboxray", get_centered_x_coord("Advisor - turboxray"));
	printf(credit_string);
    sprintf(credit_string, "\e%dX\e26YPowered By - HuCC", get_centered_x_coord("Powered By - HuCC"));
	printf(credit_string);
}

// calculate the color to display for a menu option
static int get_option_palette(option selected_option, option display_option)
{
    int selected_color = YELLOW_PALETTE_INDEX;
    int default_color = WHITE_PALETTE_INDEX;
    return selected_option == display_option ? selected_color : default_color;
}

void platform_copy_string(char * buffer, char * source)
{
    strcpy(buffer, source);
}

// display a title screen
void platform_draw_title_screen(bool did_mode_change, option title_option)
{
    char speed_string[6];
    char speed_menu_string[20];
    char title_line_string[40];
    if (did_mode_change)
    {
        cls();
        cd_playtrk(TITLE_TRACKID, GAME_TRACKID, CDPLAY_REPEAT);
        load_vram(0x1000, title_tiles, 0x0C00);
        load_palette(0, title_palette, 1);
        load_bat(0x0000, title_map, 32, 6);
    }

    game_get_speed_string(speed_string);

    set_font_pal(get_option_palette(title_option, OPTION_START));
    
    sprintf(title_line_string, "\e%dX\e12YStart Game", get_centered_x_coord("Start Game"));
    printf(title_line_string);
    sprintf(speed_menu_string, "Speed: < %s >", speed_string);
    set_font_pal(get_option_palette(title_option, OPTION_SPEED));
    sprintf(title_line_string, "\e%dX\e14Y%s", get_centered_x_coord(speed_menu_string), speed_menu_string);
    printf(title_line_string);
    set_font_pal(get_option_palette(title_option, OPTION_CREDITS));
    sprintf(title_line_string, "\e%dX\e16YCredits", get_centered_x_coord("Credits"));
    printf(title_line_string);

    set_font_pal(WHITE_PALETTE_INDEX);
    sprintf(title_line_string, "\e%dX\e24YGame (C) 2010 Stephen Bryant", get_centered_x_coord("Game (C) 2010 Stephen Bryant"));
    printf(title_line_string);
    sprintf(title_line_string, "\e%dX\e26YPort (C) 2026 Scott Harner", get_centered_x_coord("Port (C) 2026 Scott Harner"));
    printf(title_line_string);
}

// platform specific setting of random generator seed
void platform_set_random_seed(unsigned char seed)
{
    srand(seed);
}

// platform specific random number generation
int platform_get_random(int max)
{
    if (max <= 0) return 0;
    return rand() % max;
}

// steps to prepare to exit the game
void platform_shutdown()
{
    // we dont have any shutdown steps to perform on this platform
}

// track all current and previous input states so we can check on input presses
static void update_input_states(bool current_input_states[INPUT_TYPE_COUNT], int pad1_status)
{
    game_save_previous_inputstates();

    // read current state
    current_input_states[INPUT_TYPE_UP] = pad1_status & JOY_UP;
    current_input_states[INPUT_TYPE_DOWN] = pad1_status & JOY_DOWN;
    current_input_states[INPUT_TYPE_LEFT] = pad1_status & JOY_LEFT;
    current_input_states[INPUT_TYPE_RIGHT] = pad1_status & JOY_RIGHT;
    current_input_states[INPUT_TYPE_START] = pad1_status & JOY_RUN;    
}

// retrieve the input type from the user
input_type platform_get_input_type(mode game_mode, bool current_input_states[INPUT_TYPE_COUNT])
{
    int pad1_status;
    input_type current_input = INPUT_TYPE_NOTHING;
    pad1_status = joy(0);
    if (pad1_status)
    {
        update_input_states(current_input_states, pad1_status);
        switch(game_mode)
        {
            case MODE_GAME:

                if (game_input_pressed(INPUT_TYPE_START)) current_input = INPUT_TYPE_START;
                else if (pad1_status & JOY_LEFT) current_input = INPUT_TYPE_LEFT;
                else if (pad1_status & JOY_RIGHT) current_input = INPUT_TYPE_RIGHT;
                else if (pad1_status & JOY_DOWN) current_input = INPUT_TYPE_DOWN;
                else if (pad1_status & JOY_UP) current_input = INPUT_TYPE_UP;

                break;

            default:

                if (game_input_pressed(INPUT_TYPE_START)) current_input = INPUT_TYPE_START;    
                else if (game_input_pressed(INPUT_TYPE_DOWN)) current_input = INPUT_TYPE_DOWN;
                else if (game_input_pressed(INPUT_TYPE_UP)) current_input = INPUT_TYPE_UP;
                else if (game_input_pressed(INPUT_TYPE_LEFT)) current_input = INPUT_TYPE_LEFT;
                else if (game_input_pressed(INPUT_TYPE_RIGHT)) current_input = INPUT_TYPE_RIGHT;

                break;
        }
    }
    else
    {
        game_reset_input_states();
    }

    return current_input;
}

void platform_update_platform_state()
{
    // we dont have any updates to make on this platform
}

// perform platform specific actions when the game resets
void platform_reset(struct game_config *config)
{
    // no actions to perform on this platform
}

static void draw_border()
{
    int i;
    load_vram(TILE_BORDER_TL_ADDRESS, bordertl_tile, GAME_TILE_SIZE);
    load_vram(TILE_BORDER_TR_ADDRESS, bordertr_tile, GAME_TILE_SIZE);
    load_vram(TILE_BORDER_BL_ADDRESS, borderbl_tile, GAME_TILE_SIZE);
    load_vram(TILE_BORDER_BR_ADDRESS, borderbr_tile, GAME_TILE_SIZE);
    load_vram(TILE_BORDER_L_ADDRESS, borderl_tile, GAME_TILE_SIZE);
    load_vram(TILE_BORDER_R_ADDRESS, borderr_tile, GAME_TILE_SIZE);
    load_vram(TILE_BORDER_T_ADDRESS, bordert_tile, GAME_TILE_SIZE);
    load_vram(TILE_BORDER_B_ADDRESS, borderb_tile, GAME_TILE_SIZE);

    for (i = 1; i < SCREEN_WIDTH-1; i++)
    {
        // top
        put_vram(
            vram_addr(i, 1),
            TILE_BORDER_B
        );
    }

    for (i = 1; i < SCREEN_WIDTH-1; i++)
    {
        // bottom
        put_vram(
            vram_addr(i, SCREEN_HEIGHT-1),
            TILE_BORDER_T
        );
    }

    for (i = 1; i < SCREEN_HEIGHT-1; i++)
    {
        // left
        put_vram(
            vram_addr(0, i),
            TILE_BORDER_R
        );
    }

    for (i = 1; i < SCREEN_HEIGHT-1; i++)
    {
        // right
        put_vram(
            vram_addr(SCREEN_WIDTH-1, i),
            TILE_BORDER_L
        );
    }

    // upper left
    put_vram(
        vram_addr(0, 1),
        TILE_BORDER_BR
    );
    
    // upper right
    put_vram(
        vram_addr(SCREEN_WIDTH-1, 1),
        TILE_BORDER_BL
    );

    // lower left
    put_vram(
        vram_addr(0, SCREEN_HEIGHT-1),
        TILE_BORDER_TR
    );

    // lower right
    put_vram(
        vram_addr(SCREEN_WIDTH-1, SCREEN_HEIGHT-1),
        TILE_BORDER_TL
    );
}

void platform_draw_scores(int score, int high_score)
{
    char score_string[25];
    char high_score_string[28];

    // draw the score
    set_font_pal(WHITE_PALETTE_INDEX);    
    sprintf(score_string, "\e%dX\e0YScore: %d", SCREEN_WIDTH-12, score);
    printf(score_string);
    sprintf(high_score_string, "\e1X\e0YHigh Score: %d", high_score);
    printf(high_score_string);
}

void platform_draw_tile(object tile_object, int tile_x, int tile_y)
{
    unsigned int tile_id;
    tile_id = TILE_EMPTY;
    if (tile_object == OBJECT_APPLE)
        tile_id = TILE_APPLE;
    else if (tile_object == OBJECT_SNAKE)
        tile_id = TILE_SNAKE;
    
    put_vram(vram_addr(tile_x+1, tile_y+2), tile_id);
}

void draw_game_map(struct game_config *config, unsigned char *object_map)
{
    int i,j;
    int tile_index;

    //O(N^2) runtime for this, 24^2 is pretty big.. so we only do this at the very beginning of the game
    for (i = 0; i < config->map_height; i++)
    {
        for (j = 0; j < config->map_width; j++)
        {
            tile_index = i * config->map_width + j;
            if (object_map[tile_index] == OBJECT_NOTHING)
                continue;
            else
                platform_draw_tile(object_map[tile_index], j, i);
        }
    }
}

void platform_draw_game_screen(unsigned char *object_map, int score, bool did_mode_change, struct game_config *config, int high_score)
{
    if (did_mode_change)
    {        
        cd_reset(); // stop game music
        cd_playtrk(GAME_TRACKID, GAME_TRACKID+1, CDPLAY_REPEAT);
        cls();
        load_palette(0, game_palette, 1);
        draw_border();
        load_vram(TILE_APPLE_ADDRESS, apple_tile, GAME_TILE_SIZE);
        load_vram(TILE_SNAKE_ADDRESS, snake_tile, GAME_TILE_SIZE);
        load_vram(TILE_EMPTY_ADDRESS, empty_tile, GAME_TILE_SIZE);
        platform_draw_scores(score, high_score);
        draw_game_map(config, object_map);
    }
}

main()
{
    game_initialize(MAP_HEIGHT, MAP_WIDTH, TILE_SIZE);

    while (true)
    {
        vsync();

        game_update();        
    }

    game_shutdown();
}

/*
** END OF FILE
*/