#include <imgProc.hpp>

void imgProc::initializer(cv::Scalar uperMask, cv::Scalar lowerMask) {
    cv::Mat image;
    __uperMask = uperMask;
    __lowerMask = lowerMask;

    __memFd = open("/dev/mem", O_RDWR | O_SYNC);
    if (__memFd == -1) {
        std::ostringstream err;
        err << "Could not open /dev/mem ";
        throw std::runtime_error(err.str());
    }
    __readBuffer = mmap(NULL, __IMG_WIDTH*__IMG_HEIGHT*__IMG_CHANNELS, PROT_READ | PROT_WRITE, MAP_SHARED, __memFd, __READ_OFFSET);		
    if(__readBuffer == MAP_FAILED){
        std::ostringstream err;
        err << "Mapping read buffer Failed ";
        throw std::runtime_error(err.str());
    }
    __writeBuffer = mmap(NULL, __IMG_WIDTH*__IMG_HEIGHT*__IMG_CHANNELS, PROT_READ | PROT_WRITE, MAP_SHARED, __memFd, __WRITE_OFFSET );	
    if(__writeBuffer == MAP_FAILED){
        std::ostringstream err;
        err << "Mapping write buffer Failed ";
        throw std::runtime_error(err.str());
    }
    image.create(__IMG_HEIGHT,__IMG_WIDTH,CV_8UC4);
    __image = image;
}

int imgProc::updateInput(void) {
    cv::Mat imgHsv;
    cv::Mat imgBgr;
    cv::Mat mask;
    cv::Moments moment;
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Point> largestContour;
    int largestArea=0;
    int largestIndex=0;
    int cX, cY;
    
    // Read mem address 
    memcpy(__image.data, __readBuffer, __IMG_WIDTH*__IMG_HEIGHT*__IMG_CHANNELS);

    // Get HSV image
    cv::cvtColor(__image, imgBgr, cv::COLOR_RGBA2BGR);
    cv::cvtColor(imgBgr, imgHsv, cv::COLOR_BGR2HSV);

    // Mask
    cv::inRange(imgHsv, __lowerMask, __uperMask, mask);

    // Find Contours
    cv::findContours(mask, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    for( size_t i=0; i<contours.size(); i++ ) { 
        double area = cv::contourArea(contours[i]);  
        if( area > largestArea ){
            largestArea = area;
            largestIndex = i;               
        }
    }

    printf("The largest area is= %d \n", largestArea);
    cX = -1;
    if(largestArea > __AREA_THRESHOLD){
        // Largest contour
        largestContour = contours[largestIndex];

        // Draw largest contour
        cv::drawContours(__image, contours, largestIndex, cv::Scalar(0,0,0,255), 2);

        // Center of the contour
        moment = cv::moments(largestContour);
        cX = int(moment.m10 / moment.m00);
        cY = int(moment.m01 / moment.m00);

        printf("cX: %d\n", cX);

        // Draw center of area
        cv::circle(__image, cv::Point(cX, cY), 7, (255, 255, 255, 255), -1);
    }

    memcpy(__writeBuffer, __image.data, __IMG_HEIGHT*__IMG_WIDTH*__IMG_CHANNELS);
    return cX; 
}