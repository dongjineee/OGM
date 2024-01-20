
# Required Git Repositories
1. [OctoMap Messages](https://github.com/OctoMap/octomap_msgs)
2. [OctoMap RViz Plugins](https://github.com/OctoMap/octomap_rviz_plugins)

# Requirements
1. You need to create the following files in the `map_file` directory: `map_file/bt_file`, `map_file/pcd_file`.
2. Generate `bt_file` from `pcd_file`.
3. For creating `bt_file`, it is recommended to use [ETHZ-RobotX/smb_path_planner](https://github.com/ETHZ-RobotX/smb_path_planner).
4. Procedure to create `bt_file`:
    - Use `smd_path_planner/smd_navigation/~~/pcd_converter.launch`.
5. Place the generated `pcd_file` and `bt_file` in the `map_file` directory.
