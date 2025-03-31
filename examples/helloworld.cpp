#define TR_FROZEN_WAREFRAME

#include <stdio.h>
#include "trcc.h"

int main() {
    tr::Context ctx;
    if(!tr::init(&ctx)){
        printf("Could not initialize libusb\n");
        return 1;
    }
    tr::Device device;
    if(!tr::connect_to_device(ctx, &device)){
        printf("Could not connect to device\n");
        return 1;
    }

    uint16_t frame[TR_SCREEN_WIDTH*TR_SCREEN_HEIGHT];
    for(int x = 0; x < TR_SCREEN_WIDTH; x++){
        for(int y = 0; y < TR_SCREEN_HEIGHT; y++){
            int i = x*TR_SCREEN_HEIGHT + y;
            frame[i] = tr::rgb16(x*255/TR_SCREEN_WIDTH, y*255/TR_SCREEN_HEIGHT, 0);
        }
    }

    printf("Sending frames...\n");
    while(true){
        if(!tr::send_frame(device, frame)){
            printf("Failed to send frame.\n");
            return 1;
        }
    }

    tr::close_device(device);
    tr::close_context(ctx);

    return 0;
}