# Generated by superflore -- DO NOT EDIT
#
# Copyright Open Source Robotics Foundation

inherit ros_distro_humble
inherit ros_superflore_generated

DESCRIPTION = "The rplidar ros package, support rplidar A2/A1 and A3/S1"
AUTHOR = "Hunter L. Allen <hunterlallen@protonmail.com>"
ROS_AUTHOR = "Slamtec ROS Maintainer <ros@slamtec.com>"
HOMEPAGE = "https://wiki.ros.org"
SECTION = "devel"
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://package.xml;beginline=9;endline=9;md5=d566ef916e9dedc494f5f793a6690ba5"

ROS_CN = "rplidar_ros"
ROS_BPN = "rplidar_ros"

ROS_BUILD_DEPENDS = " \
    rclcpp \
    rclcpp-components \
    sensor-msgs \
    std-srvs \
"

ROS_BUILDTOOL_DEPENDS = " \
    ament-cmake-auto-native \
    ament-cmake-ros-native \
"

ROS_EXPORT_DEPENDS = ""

ROS_BUILDTOOL_EXPORT_DEPENDS = ""

ROS_EXEC_DEPENDS = " \
    rclcpp \
    rclcpp-components \
    sensor-msgs \
    std-srvs \
"

# Currently informational only -- see http://www.ros.org/reps/rep-0149.html#dependency-tags.
ROS_TEST_DEPENDS = ""

DEPENDS = "${ROS_BUILD_DEPENDS} ${ROS_BUILDTOOL_DEPENDS}"
# Bitbake doesn't support the "export" concept, so build them as if we needed them to build this package (even though we actually
# don't) so that they're guaranteed to have been staged should this package appear in another's DEPENDS.
DEPENDS += "${ROS_EXPORT_DEPENDS} ${ROS_BUILDTOOL_EXPORT_DEPENDS}"

RDEPENDS:${PN} += "${ROS_EXEC_DEPENDS}"

# matches with: https://github.com/ros2-gbp/rplidar_ros-release/archive/release/humble/rplidar_ros/2.0.2-3.tar.gz
ROS_BRANCH ?= "branch=release/humble/rplidar_ros"
SRC_URI = "git://github.com/ros2-gbp/rplidar_ros-release;${ROS_BRANCH};protocol=https"
SRCREV = "48658faf36a322e9d4d04c8d8db7ce563b62d5da"
S = "${WORKDIR}/git"

ROS_BUILD_TYPE = "ament_cmake"

inherit ros_${ROS_BUILD_TYPE}
