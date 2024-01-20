
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

# environment using Gazebo

<p align = "center">
<img src="https://github.com/dongjineee/OGM/assets/150753899/33f1c73f-0276-4cf1-bafc-91680279bfb2" width="700" height="400"/>
</p>


# Pcd_View

    $ rosrun pcd_view pcd_view

<p align = "center">
<img src="https://github.com/dongjineee/OGM/assets/150753899/bd1ce4e1-7f2b-4bac-911f-3688c296ea00" width="700" height="400"/>
</p>



# Pcd_View

    $ rosrun octo_view octo_view

<p align = "center">
<img src="https://github.com/dongjineee/OGM/assets/150753899/0eb53a2b-b7f8-41ac-acd3-7978ac87e20c" width="700" height="400"/>
</p>

# Octo to OGM

    $ rosrun octo2oc octo2oc

<p align = "center">
<img src="https://github.com/dongjineee/OGM/assets/150753899/38e0e3fa-b0de-48d9-b6ef-b02c501c1e78" width="700" height="400"/>
</p>


