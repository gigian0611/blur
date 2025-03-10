#include "OpenCV.h"


namespace OpenCV {
    bool ImageBlur(const ImageObject* src, ImageObject* dst,
        const int kernelSize)
    {
        cv::Mat s = *src;

        if (s.empty())
            return false;

        cv::Mat d;
        cv::blur(s, d, cv::Size(kernelSize, kernelSize));
        dst->resize(src->getWidth() * src->getHeight(), src->getWidth(), src->getHeight());

        if (d.empty())
            return false;

        *dst = d;

        Log::log(src->getPath() + " opencv blur conversion");
        return true;
    }
}