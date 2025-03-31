#pragma once

#include <libusb.h>
#include <stdint.h>
#include <stdio.h>

#ifdef TR_BUILD_DLL
#define TR_API __declspec(dllexport)
#else
#define TR_API __declspec(dllimport)
#endif

#define TR_FROZEN_WAREFRAME

#ifdef TR_FROZEN_WAREFRAME
    #define TR_DEVICE_CHOSEN
    #define TR_DEVICE_VID        0x0416
    #define TR_DEVICE_PID        0x5302
    #define TR_INTERRUPT_OUT_EP  0x02
    #define TR_INTERRUPT_IN_EP   0x81
    #define TR_PACKET_SIZE       512
    #define TR_SIGNATURE_SIZE    22
    #define TR_SCREEN_WIDTH      320
    #define TR_SCREEN_HEIGHT     240
#endif

#ifndef TR_BUILD_DLL
#ifndef TR_DEVICE_CHOSEN
    #error No device was defined. For example add "#define TR_FROZEN_WAREFRAME"
#endif
#endif

namespace tr{
    typedef libusb_device_handle* Device;
    typedef libusb_context* Context;

    TR_API int init(Context* ctx);
    TR_API int connect_to_device(Context ctx, Device* device);

    TR_API void close_device(Device device);
    TR_API void close_context(Context ctx);

    TR_API uint16_t rgb16(uint8_t r, uint8_t g, uint8_t b);
    TR_API int send_frame(Device device, uint16_t* frame);
    TR_API void test();
}