#ifndef OPENC_IMP
#define OPENC_IMP

#include "util/typeutil.h"

#define FLAG_DEAD   -1
#define FLAG_ALIVE  1

#define IS_NULL     1
#define IS_NOT_NULL -1

typedef struct {
    u8 R, G, B, ISNULL;
} RGB;

typedef struct {
    IVec2 term_window_size;
} OC_ctx_state;

typedef struct {
    RGB* buffer;
    IVec2 size;
    char* name;

    OC_ctx_state state;
    b8 flag;
} OC_ctx;

OC_ctx oc_initCtx(IVec2 size, char* name);
void oc_endCtx(OC_ctx* ctx);

void oc_fillScreen(OC_ctx* ctx, RGB color);
void oc_renderPixel(OC_ctx* ctx, IVec2 pos, RGB color);
void oc_updateScreen(OC_ctx* ctx);

b8 oc_isKeyPressed(char key);

#endif