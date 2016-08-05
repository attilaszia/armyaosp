/* Basic screen output handling functions
 * for Raspberry Pi arm port
 *
 * Copyright (c) 2016 Attila Szasz
 * Copyright (c) 2008, 2009 Zoltan Kovacs
 * Copyright (c) 2008 Kornel Csernai
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <types.h>
#include <console.h>
#include <lib/string.h>

#include <arch/screen.h>

static uint8_t screen_color = 7;
static uint16_t* video_memory;

static uint8_t console_buffer[2000];
uint8_t* cursor = console_buffer;

static void render_screen( int x, int y ) {
     int i, j, index;

     for ( i = 0; i < 25; i++ ) {
         for ( j= 0; j < 80; j++) {
             index = i * 80 + j;
             draw_character( console_buffer[index], j*8 , i*16 );
         }
     }    
}

static void screen_move_cursor( console_t* console ) {
    uint32_t tmp = ( console->y * console->width ) + console->x;
    cursor = ( uint8_t* )( console_buffer + tmp );    
}

static void screen_clear( console_t* console ) {
    /* Fill the video memory with spaces */
    int i;
     
    for ( i = 0; i < 2000; i++ ) {
        console_buffer[i] = ' ';
    }
    /* Set the cursor position to the top-left corner of the screen */
    console->x = 0;
    console->y = 0;

    /* Move the cursor to the specified position */
    screen_move_cursor( console );

    render_screen( 0, 0 );   
}

static void screen_putchar( console_t* console, char c ) {
    /* Get the position in the video memory according
       to the X and Y positions of the cursor */
    
    screen_move_cursor( console ); 

    /* Handle the printed character */

    switch ( c ) {
        case '\r' :
            console->x = 0;
            
            break;

        case '\n' :
            console->x = 0;
            console->y++;

            break;

        case '\b' :
            if ( console->x == 0 ) {
                if ( console->y > 0 ) {
                    console->y--;
                    console->x = console->width - 1;
                }
            } else {
                console->x--;
            }

            break;

        default :
            *cursor++ = c;
            console->x++;

            break;
    }

    /* Check if we reached the end of the line */

    if ( console->y == console->height) {
        console->y--;
        memmove( console_buffer, 
                 console_buffer + console->width,
                 console->width * ( console->height - 1 ) );
        cursor = ( uint8_t* ) ( console_buffer + console->width * ( console->height - 1 ) );
        memsetw( cursor, ' ', console->width );       
    }

    /* Move the cursor to the modified position */
    screen_move_cursor( console );
 
    render_screen( 0, 0 ); 
}

static void screen_gotoxy( console_t* console, int x, int y ) {
    /* Do a little sanity checking */

    if ( ( x < 0 ) || ( y < 0 ) ) {
        return;
    }

    if ( ( x >= console->width ) || ( y >= console->height ) ) {
        return;
    }

    /* Set the new cursor positions */
    
    console->x = x;
    console->y = y;
    
    /* ... and move the cursor */

    screen_move_cursor( console );

    render_screen( 0, 0 );
}

static void screen_set_fg_color( console_t* console, console_color_t fg ) {
    
}

static void screen_set_bg_color( console_t* console, console_color_t bg ) {
 
}

static console_operations_t screen_ops = {
    .init = NULL,
    .clear = screen_clear,
    .putchar = screen_putchar,
    .gotoxy = screen_gotoxy,
    .set_fg_color = screen_set_fg_color,
    .set_bg_color = screen_set_bg_color,
    .flush = NULL
};

static console_t screen = {
    .x = 0,
    .y = 0,
    .width = SCREEN_WIDTH,
    .height = SCREEN_HEIGHT,
    .ops = &screen_ops
};

static void debug_init( console_t* debug ) {
    /* Revisit this when UART driver is ok */    
}

static void debug_putchar( console_t* debug, char c ) {
    /* Revisit this when UART driver is ok */
}

static console_operations_t debug_ops = {
    .init = debug_init,
    .clear = NULL,
    .putchar = debug_putchar,
    .gotoxy = NULL,
    .set_fg_color = NULL,
    .set_bg_color = NULL,
    .flush = NULL
};

static console_t debug = {
    .x = 0,
    .y = 0,
    .width = 0,
    .height = 0,
    .ops = &debug_ops
};

int init_screen( void ) {
    int error;
    bool enable_debug;
    
    /* Initialize framebuffer */
 
    if ( init_framebuffer( 1024, 768, 16 ) != 0 ) {
        set_gpio_function(16,1);
        set_gpio(16,0);
        /* die here */
    }
    
    /* Setup the address of the framebuffer */

    set_graphics_address();
 
    screen_clear( &screen );
    console_set_screen( &screen );

    return 0;
}
