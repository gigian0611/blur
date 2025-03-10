#include "Custom.h"

namespace Custom {
    bool ImageBlur(const ImageObject* src, ImageObject* dst, const int kernelSize) {

        std::vector<unsigned char> s = *src;

        if (s.empty())
            return false;

        int pad = kernelSize / 2;
        int width = src->getWidth();
        int height = src->getHeight();

        std::vector<unsigned char> d;
        d.assign(width * height, 0);
        dst->resize(width * height, width, height);
            
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int sum = 0;
                int count = 0;

                for (int ky = -pad; ky <= pad; ky++) {
                    for (int kx = -pad; kx <= pad; kx++) {
                        int nx = x + kx;
                        int ny = y + ky;

                        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                            sum += s[ny * width + nx];
                            count++;
                        }
                    }
                }
                d[y * width + x] = sum / count;
            }
        }

        *dst = d;
        Log::log(src->getPath() + " custom blur conversion");
        return true;
    }
}
