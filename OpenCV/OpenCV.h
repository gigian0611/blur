#pragma once
#include <opencv2/opencv.hpp>
#include "../VisionSW/ImageObject.h"

#ifndef OPENCV_H
#define OPENCV_H

#ifdef OPENCV_EXPORTS
#define OPENCV_API __declspec(dllexport)
#else
#define OPENCV_API __declspec(dllimport) 
#endif

extern "C" {
    namespace OpenCV {
        OPENCV_API bool ImageBlur(const ImageObject* src, ImageObject* dst,
            const int kernelSize);
    }

}

#endif