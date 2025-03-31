# open-trcc
> A library that interfaces with **Thermalright** screens in place of **Thermalright Control Center**.


I hate **TRCC** so much, and many others seem to as well. I own a **Thermalright Frozen Wareframe** and love the screen it comes with, although I really wanted more control over it to do more reactive/interactive stuff with, hence the creation of this project. At some point I plan on releasing a second project using this one in addition to `SFML` as something that'll be a little more user friendly than generating frame buffers directly through `C++`.

## Building
```
mkdir ./build       * Make and enter the build directory
cd build
cmake ..            * Generate the makefiles
cmake --build .     * Run the makefiles
```

## Usage
You can find the compiled libraries and headers in the Releases tab.

Here's some basic code that displays a black screen,
```c++
#define TR_FROZEN_WAREFRAME

#include <stdio.h>
#include "trcc.h"

int main() {
    // Initialize context and connect to a device.
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

    // Define a blank frame
    uint16_t frame[TR_SCREEN_WIDTH*TR_SCREEN_HEIGHT] = {0x00};


    // Send frames
    while(true){
        if(!tr::send_frame(device, frame)){
            printf("Failed to send frame.\n");
            return 1;
        }
    }

    // Close context and device
    tr::close_device(device);
    tr::close_context(ctx);

    return 0;
}
```

The important part is the formatting of the `frame` array. The astute among you might have realized that a 16bit integer is used for each pixel, that's because **Thermalright** screens use RGB525, or 16bit, colors. To convert from RGB to RGB525 you can use `tr::rgb16(r, g, b)`.