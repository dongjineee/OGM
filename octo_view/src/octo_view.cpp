#include <ros/ros.h>
#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>
#include <octomap/OcTree.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "octomap_publisher");
  ros::NodeHandle nh;

  // 경로에 맞게 변경
  std::string octomapFilePath = "/home/dongjin/map_ws/src/map_file/bt_file/full_map.bt";

  // OctoMap 읽기
  octomap::OcTree octree(octomapFilePath);

  // OctoMap을 메시지로 변환
  octomap_msgs::Octomap octomap_msg;
  octomap_msgs::binaryMapToMsg(octree, octomap_msg);

  octomap_msg.header.frame_id = "map";
  octomap_msg.header.stamp = ros::Time::now();

  // Publisher 생성
  ros::Publisher octomapPub = nh.advertise<octomap_msgs::Octomap>("octomap", 1, true);

  ros::Rate rate(1.0);

  //while(ros::ok())
  //{
    octomapPub.publish(octomap_msg);

    ROS_INFO("OctoMap published to 'octomap' topic");
  //  rate.sleep();
    ros::spin();
 // }

  return 0;
}
