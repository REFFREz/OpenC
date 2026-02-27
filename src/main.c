#include "openc.h"

void main(void){
    OC_ctx ctx_ = oc_initCtx((IVec2){10, 10}, "test");
    OC_ctx* ctx = &ctx_;

    while(!oc_isKeyPressed('q')){
        oc_renderPixel(ctx, (IVec2){2, 2}, (RGB){255, 255, 200, IS_NOT_NULL});
    }

    oc_endCtx(ctx);
}