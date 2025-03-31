#define TR_BUILD_DLL
#include "trcc.h"

const uint8_t START_FRAME[TR_PACKET_SIZE] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
const uint8_t FRAME_SIGNATURE[TR_SIGNATURE_SIZE] = {0xDA, 0xDB, 0xDC, 0xDD, 0x02, 0x00, 0x01, 0x00, 0xF0, 0x00, 0x40, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x58, 0x02, 0x00, 0x00, 0x00};

int tr::init(Context* ctx){
    libusb_context* libusb_ctx = NULL;
    int result = libusb_init(&libusb_ctx);
    if (result < 0) {
        return 0;
    }
    *ctx = libusb_ctx;
    return 1;
}

int tr::connect_to_device(Context ctx, Device* device){
    libusb_device_handle *dev_handle = NULL;
    int result;

    dev_handle = libusb_open_device_with_vid_pid(ctx, TR_DEVICE_VID, TR_DEVICE_PID);
    if (!dev_handle) {
        libusb_exit(ctx);
        return 0;
    }


    result = libusb_claim_interface(dev_handle, 0);
    if (result < 0) {
        libusb_close(dev_handle);
        libusb_exit(ctx);
        return 0;
    }
    *device = dev_handle;
    return 1;
}

void tr::close_device(Device device){
    libusb_release_interface(device, 0);
    libusb_close(device);
}
void tr::close_context(Context ctx){
    libusb_exit(ctx);
}

uint16_t tr::rgb16(uint8_t r, uint8_t g, uint8_t b){
    r = r*31/255;
    g = g*63/255;
    b = b*31/255;
    return ((uint16_t)r << 11) | ((uint16_t)g << 5) | (uint16_t)b;
}

int tr::send_frame(Device device, uint16_t* frame){
    uint8_t packet_buffer[TR_PACKET_SIZE];
    int actual_length;

    memcpy(packet_buffer, START_FRAME, TR_PACKET_SIZE);
    int result = libusb_interrupt_transfer(device, TR_INTERRUPT_OUT_EP, packet_buffer, TR_PACKET_SIZE, &actual_length, 1000);
    if (result < 0) return 0;
    
    memcpy(packet_buffer, FRAME_SIGNATURE, TR_SIGNATURE_SIZE);
    memcpy(packet_buffer+TR_SIGNATURE_SIZE, (uint8_t*)frame+TR_SIGNATURE_SIZE, TR_PACKET_SIZE-TR_SIGNATURE_SIZE);
    result = libusb_interrupt_transfer(device, TR_INTERRUPT_OUT_EP, packet_buffer, TR_PACKET_SIZE, &actual_length, 1000);
    if (result < 0) return 0;
    
    for(int i = 1; i < 300; i++){
        memcpy(packet_buffer, (uint8_t*)frame+TR_PACKET_SIZE*i, TR_PACKET_SIZE);
        result = libusb_interrupt_transfer(device, TR_INTERRUPT_OUT_EP, packet_buffer, TR_PACKET_SIZE, &actual_length, 1000);
        if (result < 0) return 0;
    }
    return 1;
}

void tr::test(){
    printf("hello world\n");
}