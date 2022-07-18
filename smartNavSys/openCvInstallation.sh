ARMCC_PREFIX=arm-linux-gnueabihf-

echo "----- Downloading OpenCV"
git clone https://github.com/opencv/opencv.git --branch 3.4
git clone https://github.com/opencv/opencv_contrib.git --branch 3.4

echo "----- Creating necessary directories"
cd opencv
mkdir buildCross
cd buildCross
mkdir installation
 
#make clean
 
#echo "----- Setting up compilation"
#cmake -D CMAKE_BUILD_TYPE=RELEASE   \
#    -D CMAKE_INSTALL_PREFIX=installation \
#    -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules   \
#    -D CMAKE_TOOLCHAIN_FILE=../platforms/linux/arm-gnueabi.toolchain.cmake ../  \
#    -D BUILD_TESTS=OFF \
#    -D BUILD_EXAMPLES=OFF \
#    -D ENABLE_NEON=ON  \
#    -D ENABLE_VFPV3=ON   \
#    -D WITH_TBB=OFF \
#    -DCMAKE_C_COMPILER=${ARMCC_PREFIX}gcc \
#    -DCMAKE_CXX_COMPILER=${ARMCC_PREFIX}g++ \
#    -D BUILD_TBB=OFF ..

echo "----- Setting up compilation"
cmake -D CMAKE_BUILD_TYPE=RELEASE   \
    -D CMAKE_INSTALL_PREFIX=installation \
    -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules   \
    -D CMAKE_TOOLCHAIN_FILE=../platforms/linux/arm-gnueabi.toolchain.cmake ../  \
    -D BUILD_TESTS=OFF \
    -D BUILD_EXAMPLES=OFF \
    -D ENABLE_NEON=ON  \
    -D ENABLE_VFPV3=ON   \
    -D WITH_TBB=OFF \
    -D CMAKE_C_COMPILER=${ARMCC_PREFIX}gcc \
    -D CMAKE_CXX_COMPILER=${ARMCC_PREFIX}g++ \
    -D BUILD_TBB=OFF ..
 
echo "----- Starting compilation"
make -j8
make install
