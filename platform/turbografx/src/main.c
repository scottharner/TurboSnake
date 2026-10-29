
#include <stdio.h>
#include "../../platform.h"
#include "huc.h"

/*
*   Snake: Turbografx implementation of snake using hucc framework.
*   Last Update: Oct 27, 2026
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

#incchr(title_tiles, "../assets/images/title.png")
#incpal(title_palette, "../assets/images/title.png", 0, 1)
#incbat(title_map, "../assets/images/title.png", 0x1000, 32, 6)
#incchr(credits_tiles, "../assets/images/credits.png")
#incpal(credits_palette, "../assets/images/credits.png", 0, 1)
#incbat(credits_map, "../assets/images/credits.png", 0x1000, 32, 5)

#incchr_ex(border_tiles,
    "../assets/tiles/bordertl.png", 0,0,1,1,0, \ 
    "../assets/tiles/bordertr.png", 0,0,1,1,0, \ 
    "../assets/tiles/borderbl.png", 0,0,1,1,0, \ 
    "../assets/tiles/borderbr.png", 0,0,1,1,0, \ 
    "../assets/tiles/borderl.png", 0,0,1,1,0, \ 
    "../assets/tiles/borderr.png", 0,0,1,1,0, \ 
    "../assets/tiles/bordert.png", 0,0,1,1,0, \ 
    "../assets/tiles/borderb.png", 0,0,1,1,0
)
#incpal(game_palette, "../assets/tiles/bordertl.png", 0, 1)

#define TILE_BORDER_TL  0
#define TILE_BORDER_TR  1
#define TILE_BORDER_BL  2
#define TILE_BORDER_BR  3
#define TILE_BORDER_L   4
#define TILE_BORDER_R   5
#define TILE_BORDER_T   6
#define TILE_BORDER_B   7

#incchr_ex(game_tiles,
    "../assets/tiles/apple.png", 0,0,1,1,0, \ 
    "../assets/tiles/snake.png", 0,0,1,1,0, \ 
    "../assets/tiles/empty.png", 0,0,1,1,0
)

#define TILE_APPLE  0
#define TILE_SNAKE  1
#define TILE_EMPTY  2

// static int game_over_sprite_id;
// static int you_win_sprite_id;
// static short pickup_sound_id;
// static short lose_sound_id;

// Saturn implementation of platform initialization
void platform_initialize()
{
    set_color_rgb(WHITE_COLOR_INDEX, 7, 7, 7);
    set_color_rgb(YELLOW_COLOR_INDEX, 7, 7, 0);
	set_font_color(WHITE_COLOR_INDEX, BLACK_COLOR_INDEX);
	set_font_pal(WHITE_PALETTE_INDEX);
	load_default_font();

//     game_over_sprite_id = jo_sprite_add_tga("TEX", "GAMEOVER.TGA", JO_COLOR_Transparent);
//     you_win_sprite_id = jo_sprite_add_tga("TEX", "YOUWIN.TGA", JO_COLOR_Transparent);
//     pickup_sound_id = load_8bit_pcm((Sint8 *)"PICKUP.PCM", 15360); // using ponetone due to issues with jo engine audio
//     lose_sound_id = load_8bit_pcm((Sint8 *)"LOSE.PCM", 15360);
//     CDDA_SetVolume(4);
}

// plays the requested sound effect
void platform_play_sound(sound_type current_sound_type)
{
    // todo - implement
    // if (current_sound_type == SOUND_PICKUP)
    // {
    //     pcm_play(pickup_sound_id, PCM_PROTECTED, 6);
    // }
    // else if (current_sound_type == SOUND_LOSE)
    // {
    //     pcm_play(lose_sound_id, PCM_PROTECTED, 6);
    // }
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
    if (did_mode_change)
    {
        cd_reset(); // stop game music
        cls();
    }

//     draw_tile(0, 40, game_over_sprite_id, BORDER_ZINDEX, 0);
    
    set_font_pal(WHITE_PALETTE_INDEX);
    sprintf(score_string, "Score: %d", score);
    put_string(score_string, get_centered_x_coord(score_string), 10);
    sprintf(reason_string, "Reason: %s", current_loss_type == LOSS_TYPE_SELF ? "Self Collision" : "Wall Collision");
    put_string(reason_string, get_centered_x_coord(reason_string), 12);
}

// display a win screen
void platform_draw_win_screen(int score, bool did_mode_change)
{
    // todo - implement
//     if (did_mode_change)
//     {
//         CDDA_Stop(); // stop game music
//         jo_clear_screen();
//     }

//     draw_tile(0, 40, you_win_sprite_id, BORDER_ZINDEX, 0);

//     char score_string[12];
//     sprintf(score_string, "Score: %d", score);
//     print_centered_text(10, score_string, JO_COLOR_INDEX_White);
}

// display a credits screen
void platform_draw_credits_screen(bool did_mode_change)
{
    if (did_mode_change)
    {
        cd_reset(); // stop game music
        cls();
        load_vram(0x1000, credits_tiles, 0x0A00);
        load_palette(0, credits_palette, 1);
        load_bat(0x0000, credits_map, 32, 5);
    }

    set_font_pal(WHITE_PALETTE_INDEX);
    put_string("Game Engineer - Stephen Bryant", get_centered_x_coord("Game Engineer - Stephen Bryant"), 7);
    put_string("Port Engineer - Scott Harner", get_centered_x_coord("Port Engineer - Scott Harner"), 9);
    put_string("QA Tester - Evan Harner", get_centered_x_coord("QA Tester - Evan Harner"), 11);
    put_string("Music - Safety Stoat Studios", get_centered_x_coord("Music - Safety Stoat Studios"), 13);
    put_string("Sound Effects - Kronbits", get_centered_x_coord("Sound Effects - Kronbits"), 15);
    put_string("Advisor - Elmer", get_centered_x_coord("Advisor - Elmer"), 17);
    put_string("Powered By - HuCC", get_centered_x_coord("Powered By - HuCC"), 26);
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
    put_string("Start Game", get_centered_x_coord("Start Game"), 12);
    sprintf(speed_menu_string, "Speed: < %s >", speed_string);
    set_font_pal(get_option_palette(title_option, OPTION_SPEED));
    put_string(speed_menu_string, get_centered_x_coord(speed_menu_string), 14);
    set_font_pal(get_option_palette(title_option, OPTION_CREDITS));
    put_string("Credits", get_centered_x_coord("Credits"), 16);

    set_font_pal(WHITE_PALETTE_INDEX);
    put_string("Game (C) 2010 Stephen Bryant", get_centered_x_coord("Game (C) 2010 Stephen Bryant"), 24);
    put_string("Port (C) 2026 Scott Harner", get_centered_x_coord("Port (C) 2026 Scott Harner"), 26);
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

    return current_input; // todo - implement
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
    set_tile_data(border_tiles);
    load_tile(0x1000); // takes up 16 x 8 x 1 = 128 (0x0080)

    for (i = 1; i < SCREEN_WIDTH-1; i++)
    {
        // top
        put_tile(TILE_BORDER_B, i, 1);
    }

    for (i = 1; i < SCREEN_WIDTH-1; i++)
    {
        // bottom
        put_tile(TILE_BORDER_T, i, SCREEN_HEIGHT-1);
    }

    for (i = 1; i < SCREEN_HEIGHT-1; i++)
    {
        // left
        put_tile(TILE_BORDER_R, 0, i);
    }

    for (i = 1; i < SCREEN_HEIGHT-1; i++)
    {
        // right
        put_tile(TILE_BORDER_L, SCREEN_WIDTH-1, i);
    }

    // upper left
    put_tile(TILE_BORDER_BR, 0, 1);
    
    // upper right
    put_tile(TILE_BORDER_BL, SCREEN_WIDTH-1, 1);

    // lower left
    put_tile(TILE_BORDER_TR, 0, SCREEN_HEIGHT-1);

    // lower right
    put_tile(TILE_BORDER_TL, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);
}

void platform_draw_scores(int score, int high_score)
{
    char score_string[15];
    char high_score_string[20];

    // draw the score
    set_font_pal(WHITE_PALETTE_INDEX);    
    sprintf(score_string, "Score: %d", score);
    put_string(score_string, SCREEN_WIDTH-12, 0);
    sprintf(high_score_string, "High Score: %d", high_score);
    put_string(high_score_string, 1, 0);
}

void platform_draw_tile(object tile_object, int tile_x, int tile_y)
{
    unsigned char tile_id;
    tile_id = TILE_EMPTY;
    if (tile_object == OBJECT_APPLE)
        tile_id = TILE_APPLE;
    else if (tile_object == OBJECT_SNAKE)
        tile_id = TILE_SNAKE;
    
    put_tile(tile_id, tile_x+1, tile_y+2);
}

void draw_map(struct game_config *config, unsigned char *object_map)
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
        set_tile_data(game_tiles);
        load_tile(0x1080); // 1000 + 80 for border so we dont overwrite
        platform_draw_scores(score, high_score);
        draw_map(config, object_map);
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