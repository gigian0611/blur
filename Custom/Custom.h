#pragma once
#include "../VisionSW/ImageObject.h"

#ifndef CUSTOM_H
#define CUSTOM_H

#ifdef CUSTOM_EXPORTS
#define CUSTOM_API __declspec(dllexport)
#else
#define CUSTOM_API __declspec(dllimport) 
#endif

namespace Custom {
    CUSTOM_API bool ImageBlur(const ImageObject* src, ImageObject* dst,
        const int kernelSize);
}

#endif