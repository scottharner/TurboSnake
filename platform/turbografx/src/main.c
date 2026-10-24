
// #include <jo/jo.h>
#include <stdio.h>
#include "../../platform.h"
// #include "pcmsys.h"
#include "huc.h"

/*
*   Snake: Turbografx implementation of snake using hucc framework.
*   Last Update: Oct 22, 2026
*   Author: Scott Harner
*/

// #define OBJECT_ZINDEX 450
// #define BORDER_ZINDEX 500
// #define JO_GRID_WIDTH (JO_TV_WIDTH / 8)
// #define JO_GRID_HEIGHT (JO_TV_HEIGHT / 8)
#define MAP_HEIGHT 28
#define HALF_MAP_WIDTH 16
#define MAP_WIDTH 32
#define TILE_SIZE 8
#define BLACK_COLOR_INDEX 0
#define WHITE_COLOR_INDEX 1
#define YELLOW_COLOR_INDEX 17
#define WHITE_PALETTE_INDEX 0
#define YELLOW_PALETTE_INDEX 1
// #define TITLE_TRACKID 3
// #define GAME_TRACKID 2

// static int snake_sprite_id;
// static int apple_sprite_id;
// static int border_top_sprite_id;
// static int border_left_sprite_id;
// static int border_corner_sprite_id;
// static int title_sprite_id;
// static int game_over_sprite_id;
// static int you_win_sprite_id;
// static int credits_sprite_id;
// static short pickup_sound_id;
// static short lose_sound_id;

// Saturn implementation of platform initialization
void platform_initialize()
{
    set_color_rgb(WHITE_COLOR_INDEX, 7, 7, 7); // first color index is white
    set_color_rgb(YELLOW_COLOR_INDEX, 7, 7, 0); // second color is yellow
	set_font_color(WHITE_COLOR_INDEX, BLACK_COLOR_INDEX);
	set_font_pal(WHITE_PALETTE_INDEX);
	load_default_font();

//     jo_core_init(JO_COLOR_Black);
//     load_drv(ADX_MASTER_2304);
//     snake_sprite_id = jo_sprite_add_tga("TEX", "SNAKE.TGA", JO_COLOR_Transparent);
//     apple_sprite_id = jo_sprite_add_tga("TEX", "APPLE.TGA", JO_COLOR_Transparent);
//     border_top_sprite_id = jo_sprite_add_tga("TEX", "BORDERT.TGA", JO_COLOR_Transparent);
//     border_left_sprite_id = jo_sprite_add_tga("TEX", "BORDERL.TGA", JO_COLOR_Transparent);
//     border_corner_sprite_id = jo_sprite_add_tga("TEX", "BORDERC.TGA", JO_COLOR_Transparent);
//     title_sprite_id = jo_sprite_add_tga("TEX", "TITLE.TGA", JO_COLOR_Transparent);
//     game_over_sprite_id = jo_sprite_add_tga("TEX", "GAMEOVER.TGA", JO_COLOR_Transparent);
//     you_win_sprite_id = jo_sprite_add_tga("TEX", "YOUWIN.TGA", JO_COLOR_Transparent);
//     credits_sprite_id = jo_sprite_add_tga("TEX", "CREDITS.TGA", JO_COLOR_Transparent);
//     pickup_sound_id = load_8bit_pcm((Sint8 *)"PICKUP.PCM", 15360); // using ponetone due to issues with jo engine audio
//     lose_sound_id = load_8bit_pcm((Sint8 *)"LOSE.PCM", 15360);
//     CDDA_SetVolume(4);
}

// void draw_tile(int x, int y, int sprite_id, int z, int angle)
// {
//     if (angle == 0)
//         jo_sprite_draw3D2(sprite_id, x, y, z);
//     else
//         jo_sprite_draw3D_and_rotate2(sprite_id, x, y, z, angle);

// #if JO_DEBUG
//     jo_printf_with_color(0, 0, JO_COLOR_INDEX_White, "tile x: %d", x);
//     jo_printf_with_color(0, 1, JO_COLOR_INDEX_White, "tile y: %d", y);
// #endif
// }

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

// static void print_centered_text(int y, const char *string, int color)
// {
//     int length = strlen(string);
//     int x = HALF_MAP_WIDTH - (length / 2);

//     if (x < 0)
//     {
//         x = 0;
//     }

//     jo_printf_with_color(x, y, color, string);
// }

static int get_centered_x_coord(char * text)
{
    int length;

    length = 0;
    while (text[length] != '\0')
    {
        length++;
    }

    return (MAX_MAP_WIDTH - length ) / 2;
}

// display a game over screen
void platform_draw_game_over_screen(int score, bool did_mode_change, loss_type current_loss_type)
{
    // todo - implement
//     if (did_mode_change)
//     {
//         CDDA_Stop(); // stop game music
//         jo_clear_screen();
//     }

//     draw_tile(0, 40, game_over_sprite_id, BORDER_ZINDEX, 0);

//     char score_string[12];
//     sprintf(score_string, "Score: %d", score);
//     print_centered_text(10, score_string, JO_COLOR_INDEX_White);
//     char reason_string[25];
//     sprintf(reason_string, "Reason: %s", current_loss_type == LOSS_TYPE_SELF ? "Self Collision" : "Wall Collision");
//     print_centered_text(12, reason_string, JO_COLOR_INDEX_White);
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
    // todo - implement
//     if (did_mode_change)
//     {
//         CDDA_Stop(); // stop game music
//         jo_clear_screen();
//     }

//     draw_tile(0, 0, credits_sprite_id, BORDER_ZINDEX, 0);

//     print_centered_text(7, "Game Engineer - Stephen Bryant", JO_COLOR_INDEX_White);
//     print_centered_text(9, "Port Engineer - Scott Harner", JO_COLOR_INDEX_White);
//     print_centered_text(11, "QA Tester - Evan Harner", JO_COLOR_INDEX_White);
//     print_centered_text(13, "Music Composer - Safety Stoat Studios", JO_COLOR_INDEX_White);
//     print_centered_text(15, "Sound Effects Designer - Kronbits", JO_COLOR_INDEX_White);
//     print_centered_text(17, "Audio Driver Engineer - Ponut64", JO_COLOR_INDEX_White);
//     print_centered_text(19, "Advisor - ReyeMe", JO_COLOR_INDEX_White);
//     print_centered_text(21, "Advisor - Hassmaschine", JO_COLOR_INDEX_White);
//     print_centered_text(23, "Advisor - supahfly", JO_COLOR_INDEX_White);
//     print_centered_text(28, "Powered By - Jo Engine", JO_COLOR_INDEX_White);
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
        // CDDA_PlaySingle(TITLE_TRACKID, true);
    }

    game_get_speed_string(speed_string);

    // draw_tile(0, 0, title_sprite_id, BORDER_ZINDEX, 0);

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
void platform_set_random_seed(unsigned int seed)
{
    // todo - implement
    // jo_random_seed = seed;
}

// platform specific random number generation
int platform_get_random(int max)
{
    if (max <= 0) return 0;
    return max; // todo - implement
    //return (jo_random(max)-1); // jo_random requires passing parm so we cant use modulo
}

// // platform specific memory allocation
// void * platform_memory_allocate(unsigned int size)
// {
//     return jo_malloc(size);
// }

// // platform specific memory free
// void platform_memory_free(void *pointer)
// {
//     jo_free(pointer);
// }

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
    //         case MODE_GAME:

    //             if (game_input_pressed(INPUT_TYPE_START)) current_input = INPUT_TYPE_START;
    //             else if (jo_is_pad1_key_pressed(JO_KEY_LEFT)) current_input = INPUT_TYPE_LEFT;
    //             else if (jo_is_pad1_key_pressed(JO_KEY_RIGHT)) current_input = INPUT_TYPE_RIGHT;
    //             else if (jo_is_pad1_key_pressed(JO_KEY_DOWN)) current_input = INPUT_TYPE_DOWN;
    //             else if (jo_is_pad1_key_pressed(JO_KEY_UP)) current_input = INPUT_TYPE_UP;

    //             break;

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

// static void draw_border(game_config *config)
// {
//     for (int i = 1; i < config->map_width-1; i++)
//     {
//         // top
//         draw_tile(i * config->tile_size, 0, border_top_sprite_id, BORDER_ZINDEX, 0);
//     }

//     jo_sprite_enable_vertical_flip();
//     for (int i = 1; i < config->map_width-1; i++)
//     {
//         // bottom
//         draw_tile(i * config->tile_size, (MAP_HEIGHT*config->tile_size)-config->tile_size-1, border_top_sprite_id, BORDER_ZINDEX, 0);
//     }
//     jo_sprite_disable_vertical_flip();

//     for (int i = 1; i < config->map_height-1; i++)
//     {
//         // left
//         draw_tile(0, i * config->tile_size, border_left_sprite_id, BORDER_ZINDEX, 0);
//     }

//     jo_sprite_enable_horizontal_flip();
//     for (int i = 1; i < config->map_height-1; i++)
//     {
//         // right
//         draw_tile((MAP_WIDTH*config->tile_size)-config->tile_size-1, i * config->tile_size, border_left_sprite_id, BORDER_ZINDEX, 0);
//     }
//     jo_sprite_disable_horizontal_flip();

//     // upper left
//     draw_tile(0, 0, border_corner_sprite_id, BORDER_ZINDEX, 0);
    
//     // upper right
//     jo_sprite_enable_horizontal_flip();
//     draw_tile((MAP_WIDTH*config->tile_size)-config->tile_size-1, 0, border_corner_sprite_id, BORDER_ZINDEX, 0);
//     jo_sprite_disable_horizontal_flip();

//     // lower left
//     jo_sprite_enable_vertical_flip();
//     draw_tile(0, (MAP_HEIGHT*config->tile_size)-config->tile_size-1, border_corner_sprite_id, BORDER_ZINDEX, 0);

//     // lower right
//     jo_sprite_enable_horizontal_flip();
//     draw_tile((MAP_WIDTH*config->tile_size)-config->tile_size-1, (MAP_HEIGHT*config->tile_size)-config->tile_size-1, border_corner_sprite_id, BORDER_ZINDEX, 0);
//     jo_sprite_disable_horizontal_flip();
//     jo_sprite_disable_vertical_flip();
// }

void platform_draw_game_screen(unsigned char *object_map, int score, bool did_mode_change, struct game_config *config, int high_score)
{
    // todo - implement
//     if (did_mode_change)
//     {        
//         CDDA_Stop(); // stop title
//         CDDA_PlaySingle(GAME_TRACKID, true);
//         jo_clear_screen();
//     }

//     int i,j;
//     //O(N^2) runtime for this, 24^2 is pretty big.. so we may change this
//     //but for now, we draw every tile every frame!
//     for (i = 0; i < config->map_height; i++)
//     {
//         for (j = 0; j < config->map_width; j++)
//         {
//             int sprite_id;
//             int tile_index = i * config->map_width + j;
//             if (object_map[tile_index] == OBJECT_APPLE)
//             {
//                 sprite_id = apple_sprite_id;
//             }
//             else if (object_map[tile_index] == OBJECT_SNAKE)
//             {
//                 sprite_id = snake_sprite_id;
//             }
//             else
//             {
//                 continue;
//             }

//             draw_tile(config->tile_size*j, config->tile_size*i, sprite_id, OBJECT_ZINDEX, 0);
//         }
//     }

//     //draw the score
//     jo_printf_with_color(JO_GRID_WIDTH-10, 1, JO_COLOR_INDEX_White, "Score: %d", score);
//     jo_printf_with_color(3, 1, JO_COLOR_INDEX_White, "High Score: %d", high_score);

//     draw_border(config);
}

main()
{
    game_initialize(MAP_HEIGHT, MAP_WIDTH, TILE_SIZE);
	// jo_core_add_vblank_callback(sdrv_vblank_rq);
    // jo_core_add_callback(game_update);
    // jo_core_run();

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