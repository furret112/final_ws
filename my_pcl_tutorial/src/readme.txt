if you want to test example in rviz
1.roscore
2.roslaunch realsense2_camera rs_camera.launch filters:=pointcloud enable_infra1:=false enable_infra2:=false
3.rosrun my_pcl_tutorial example input:=/camera/depth/color/points
4.rosrun rviz rviz
