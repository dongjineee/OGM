cmake_minimum_required(VERSION 3.0.2)
project(OGM)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
    pcl_ros
    roscpp
    sensor_msgs
    octomap_msgs
    octomap
    nav_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES pcd_view
#  CATKIN_DEPENDS pcl_ros roscpp sensor_msgs
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pcd_view pcd_view/src/pcd_view.cpp)
target_link_libraries(pcd_view ${catkin_LIBRARIES})

add_executable(octo_view octo_view/src/octo_view.cpp)
target_link_libraries(octo_view ${catkin_LIBRARIES})

add_executable(octo2oc octo2oc/src/octo2oc.cpp)
target_link_libraries(octo2oc ${catkin_LIBRARIES})