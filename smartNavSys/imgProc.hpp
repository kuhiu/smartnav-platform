#ifndef __IMGPROC_H__
#define __IMGPROC_H__

#include <fstream>
#include <sstream>
#include <tuple>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#include <opencv2/opencv.hpp>

class imgProc {
public:
    imgProc() = default;
    ~imgProc() = default;

    void initializer(cv::Scalar uperMask, cv::Scalar lowerMask);
    int updateInput(void);

    static constexpr double __RED_LOWER_MASK_H{175};
    static constexpr double __RED_LOWER_MASK_S{100};
    static constexpr double __RED_LOWER_MASK_V{20};
    static constexpr double __RED_UPER_MASK_H{179};
    static constexpr double __RED_UPER_MASK_S{255};
    static constexpr double __RED_UPER_MASK_V{255};
private:
    static constexpr auto __IMG_WIDTH{320};
    static constexpr auto __IMG_HEIGHT{240};
    static constexpr auto __IMG_CHANNELS{4};
    static constexpr off_t __READ_OFFSET{0x01000000};
    static constexpr off_t __WRITE_OFFSET{0x02000000};
    static constexpr auto __AREA_THRESHOLD{200};

    int __memFd;
    void *__readBuffer;
    void *__writeBuffer;
    cv::Scalar __uperMask;
    cv::Scalar __lowerMask;

    cv::Mat __image;
};



#endif // __IMGPROC_H__