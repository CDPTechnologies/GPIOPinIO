/**
GPIOPinIo header file. Include this file in the project to use the library.
*/

#ifndef GPIOPINIO_GPIOPINIO_H
#define GPIOPINIO_GPIOPINIO_H

#include "GPIOPinIOBuilder.h"

namespace GPIOPinIO {

/** Instantiate the GPIOPinIOBuilder for this object */
GPIOPinIOBuilder gGPIOPinIOBuilder("GPIOPinIO", __TIMESTAMP__);

}

#endif

