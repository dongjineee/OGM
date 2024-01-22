#include <ros/ros.h>
#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <octomap_msgs/Octomap.h>
#include <nav_msgs/OccupancyGrid.h>
#include <octomap_msgs/conversions.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "octomap_to_grid");
    ros::NodeHandle nh;

    // OctoMap 파일 경로 설정
    std::string octomapFilePath;
    // gil
    nh.param<std::string>("octomap_path", octomapFilePath, "/");

    // OctoMap 읽기
    octomap::OcTree octree(octomapFilePath);
    double m_treeDepth, m_maxTreeDepth, m_res;
    nav_msgs::OccupancyGrid gridMap;

    octomap_msgs::Octomap octomap_msg;
    octomap_msgs::binaryMapToMsg(octree, octomap_msg);

    m_treeDepth = octree.getTreeDepth();
    m_maxTreeDepth = m_treeDepth;
    m_res = octree.getResolution();

    gridMap.info.resolution = m_res;

    double minX, minY, minZ;
    double maxX, maxY, maxZ;
    double width, length;

    octree.getMetricMin(minX, minY, minZ);
    octree.getMetricMax(maxX, maxY, maxZ);

    // 2D Grid 메시지 생성
    width = maxX - minX;
    length = maxY - minY;

    gridMap.info.height = (length / m_res) + 1;  // 세로 길이 설정
    gridMap.info.width = (width / m_res) + 1; //가로 길이 설정 + 1 한 이유는 테두리 여유분

    gridMap.info.origin.position.x = minX;  // 원점 위치 설정
    gridMap.info.origin.position.y = minY;

    // 2D Grid 데이터 생성
    gridMap.data.resize(gridMap.info.width * gridMap.info.height,-1);
    //gridMap.data.clear();
    // OctoMap 데이터를 2D Grid로 변환
    for(int i = 0; i < gridMap.info.height; i ++)
    {
        for(int k = 0; k < gridMap.info.width; k ++)
        {
            gridMap.data[i* gridMap.info.width+k] = 10;
        }
    }  // 여기 부분에 ground 만 알 수 있으면 if 하나 더써서 나머지 grid data는 0주면 될듯 현재는 모든 grid를 흰색을 주고 시작하긴 하는데 ground만 알 수 있으면 바로 한번에 될듯

    for (auto it = octree.begin_leafs(), end = octree.end_leafs(); it != end; ++it) {
        double x = it.getX();
        double y = it.getY();
        double z = it.getZ();

        // Z축을 기준으로 2D Grid에 매핑
        int gridX = static_cast<int>((x - gridMap.info.origin.position.x) / m_res);
        int gridY = static_cast<int>((y - gridMap.info.origin.position.y) / m_res);

        // 범위 검사
        if (gridX >= 0 && gridX < gridMap.info.width && gridY >= 0 && gridY < gridMap.info.height) {
            // 노드가 확률을 가지고 있는 경우, 2D Grid에 매핑
            if(z >= 1.5) gridMap.data[gridY * gridMap.info.width + gridX] = 100; //그리드맵데이터는 (y축데이터*폭+x축데이터) 로 되어있는듯 
        }
       // gridMap.data[gridY * gridMap.info.width + gridX] = 5;
    }

    //octo map에서 ground를 처리 해줘야할듯 아니면 pcd에서 ground를 잡아서 제거해야할듯 
    // Publisher 생성
    ros::Publisher gridMapPub = nh.advertise<nav_msgs::OccupancyGrid>("map", 1, true);

    // 메시지에 타임스탬프 설정
    gridMap.header.stamp = ros::Time::now();

    // 퍼블리셔에 메시지 전송
    gridMapPub.publish(gridMap);

    ROS_INFO("2D Grid map published to 'grid_map' topic");

    ros::spin();

    return 0;
}
