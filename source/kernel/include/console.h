/* Console structure definitions and functions
 *
 * Copyright (c) 2008, 2009 Zoltan Kovacs
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

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <types.h>
#include <config.h>
#include <lib/stdarg.h>

struct console;

#ifdef MK_RELEASE_BUILD
#define DEBUG_LOG(args...)
#else
#define DEBUG_LOG(format, args...) dprintf( format, ##args )
#endif /* MK_RELEASE_BUILD */

enum {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

typedef enum console_color {
    COLOR_BLACK,
    COLOR_BLUE,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_RED,
    COLOR_MAGENTA,
    COLOR_BROWN,
    COLOR_LIGHT_GRAY,
    COLOR_DARK_GRAY,
    COLOR_LIGHT_BLUE,
    COLOR_LIGHT_GREEN,
    COLOR_LIGHT_CYAN,
    COLOR_LIGHT_RED,
    COLOR_LIGHT_MAGENTA,
    COLOR_LIGHT_BROWN,
    COLOR_WHITE
} console_color_t;

typedef void console_init_t( struct console* console );
typedef void console_clear_t( struct console* console );
typedef void console_putchar_t( struct console* console, char c );
typedef void console_gotoxy_t( struct console* console, int x, int y );
typedef void console_set_fg_t( struct console* console, console_color_t fg );
typedef void console_set_bg_t( struct console* console, console_color_t bg );
typedef void console_flush_t( struct console* console );

typedef struct console_operations {
    console_init_t* init;
    console_clear_t* clear;
    console_putchar_t* putchar;
    console_gotoxy_t* gotoxy;
    console_set_fg_t* set_fg_color;
    console_set_bg_t* set_bg_color;
    console_flush_t* flush;
} console_operations_t;

typedef struct console {
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
    console_operations_t* ops;
} console_t;

typedef struct framebuffer_info {
    uint32_t width;
    uint32_t height;
    uint32_t v_width;
    uint32_t v_height;
    uint32_t pitch;
    uint32_t bitdepth;
    uint32_t x;
    uint32_t y;
    void* pointer;
    uint32_t size;
} framebuffer_info_t;

console_t* console_get_real_screen( void );

/**
 * This is used by architecture specific part of the kernel to
 * specify the screen properties and callbacks. The arch. code
 * has to fill a console_t structure that is passed to this
 * function as the first argument.
 *
 * @param console The screen instance
 * @return On success 0 is returned
 */
int console_set_screen( console_t* console );
int console_switch_screen( console_t* new_console, console_t** old_console );

int console_set_debug( console_t* console );

int kprintf( int loglevel, const char* format, ... );
int kvprintf( int loglevel, const char* format, va_list args );

int dprintf( const char* format, ... );
int dprintf_unlocked( const char* format, ... );

int kernel_console_read( char* buffer, int size );

#endif /* _CONSOLE_H_ */
