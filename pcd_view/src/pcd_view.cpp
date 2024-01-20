#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/filters/voxel_grid.h>

int main(int argc, char** argv) {
  ros::init(argc, argv, "pcd_visualizer");
  ros::NodeHandle nh;

  // PCD 파일 경로 설정
  std::string pcdFilePath = "/home/dongjin/map_ws/src/map_file/pcd_file/full_map.pcd";

  // PCL에서 사용할 PointCloud 타입 정의
  typedef pcl::PointXYZ PointType;
  typedef pcl::PointCloud<PointType> PointCloudType;

  // PCD 파일에서 PointCloud 읽기
  PointCloudType::Ptr cloud(new PointCloudType);
  pcl::io::loadPCDFile(pcdFilePath, *cloud);

  pcl::VoxelGrid<PointType> sor;
  sor.setInputCloud(cloud);
  sor.setLeafSize(0.05, 0.05, 0.05);  // 다운샘플링 크기 설정
  sor.filter(*cloud);

  // PointCloud를 ROS 메시지로 변환
  sensor_msgs::PointCloud2::Ptr cloudMsg(new sensor_msgs::PointCloud2);
  pcl::toROSMsg(*cloud, *cloudMsg);

  // Publisher 생성
  ros::Publisher cloudPub = nh.advertise<sensor_msgs::PointCloud2>("pcd_map", 1, true);

  // 노드를 1Hz로 실행
 // ros::Rate rate(1.0);

  //while (ros::ok()) {
    // 퍼블리셔에 메시지 전송
    cloudMsg->header.frame_id = "map";
    cloudMsg->header.stamp = ros::Time::now();
    cloudPub.publish(cloudMsg);

    ROS_INFO("PCD map published to 'pcd_map' topic");

    // 대기
    ros::spin();
  //}

  return 0;
}