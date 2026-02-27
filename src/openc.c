#include "openc.h"

#include <stdio.h>
#include <stdlib.h>
//#include <ncurses.h> ignore for now
#include <locale.h>

//#define stdscr 1
//#define TRUE   2
//#define ERR    -1
//void keypad(int null, int null1);

void init_ncurses(void)
{
    setlocale(LC_ALL, "");   // Enable UTF-8 support
    initscr();               // Start curses mode
    cbreak();                // Disable line buffering
    noecho();                // Don't echo typed characters
    keypad(stdscr, TRUE);    // Enable special keys (arrows, F-keys)
    curs_set(0);             // Hide cursor (optional)
    
    if (has_colors()) {
        start_color();       // Enable color support
        use_default_colors();// Allow terminal default background
    }

    nodelay(stdscr, TRUE);   // makes sure that getch runs instantly
    refresh();               // Refresh the screen
}

OC_ctx oc_initCtx(IVec2 size, char* name){
    OC_ctx ctx = {.flag = FLAG_DEAD};

    if(size.x <= 0 || size.y <= 0){return ctx;}
    if(name == NULL){return ctx;}

    ctx.buffer = calloc(size.x * size.y, sizeof(RGB));
    ctx.name = name;
    ctx.size = size;
    ctx.flag = FLAG_ALIVE;
    // TODO: when ncurses is implemented make sure to add state info

    int x, y;
    getmaxyx(stdscr, y, x);
    ctx.state.term_window_size = (IVec2){x, y};

    return ctx;

}

void oc_endCtx(OC_ctx* ctx){
    free(ctx->buffer);
    ctx->flag = FLAG_DEAD;
    ctx->name = NULL;
    ctx->size = (IVec2){0,0};
}

void oc_fillScreen(OC_ctx* ctx, RGB color){
    if(ctx->flag == FLAG_DEAD){return;}
    int size = ctx->size.x * ctx->size.y;
    for(int i = 0;i < size;i++){
        ctx->buffer[i] = color;
    }
}

void oc_renderPixel(OC_ctx* ctx, IVec2 pos, RGB color){
    if(ctx -> flag == FLAG_DEAD){return;}
    if(pos.x < 0 || pos.x >= ctx->size.x){return;}
    if(pos.y < 0 || pos.y >= ctx->size.y){return;}

    ctx->buffer[pos.y * ctx->size.x + pos.x] = color;
}

void oc_updateScreen(OC_ctx* ctx){
    int sx, sy;
    sx = ctx->size.x;
    sy = ctx->size.y;

    for(int y = 0;y < sy;y++){
        for(int x = 0;x < sx;x++){
            RGB c = ctx->buffer[y * sx + x];
            if(c.ISNULL == IS_NOT_NULL){
                mwprintw(y, x, "@"); // for now
            }
        }
    }
}

b8 oc_isKeyPressed(char key){
    int ch = getch();

    if (ch == ERR)
        return 0;

    return (ch == key) ? 1 : 0;
}