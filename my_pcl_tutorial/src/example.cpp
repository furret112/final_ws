#include <ros/ros.h>
// PCL specific includes 。PCL 的相關的頭文件
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//濾波的頭文件
#include <pcl/filters/voxel_grid.h>
//申明發布器
ros::Publisher pub;
//回調函數
void 
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
 // 聲明存儲原始數據與濾波後的數據的點雲的格式  
// Container for original & filtered data
  pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; //原始的點雲的數據格式
  pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
  pcl::PCLPointCloud2 cloud_filtered;//存儲濾波後的數據格式
 
  // Convert to PCL data type。轉化爲PCL中的點雲的數據格式
  pcl_conversions::toPCL(*cloud_msg, *cloud);
 
  // Perform the actual filtering進行一個濾波處理
  pcl::VoxelGrid<pcl::PCLPointCloud2> sor; //創建濾波對象
  sor.setInputCloud (cloudPtr);  //設置輸入的濾波，將需要過濾的點雲給濾波對象
  sor.setLeafSize (0.1, 0.1, 0.1);  //設置濾波時創建的體素大小爲1cm立方體
  sor.filter (cloud_filtered);//執行濾波處理，存儲輸出cloud_filtered
 
  // Convert to ROS data type。// 再將濾波後的點雲的數據格式轉換爲ROS下的數據格式發佈出去
  sensor_msgs::PointCloud2 output;//聲明的輸出的點雲的格式
  pcl_conversions::moveFromPCL(cloud_filtered, output);//第一個參數是輸入，後面的是輸出
 
  // Publish the data
  pub.publish (output);
}
 
int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "my_pcl_tutorial");//聲明節點的名稱
  ros::NodeHandle nh;
 
  // Create a ROS subscriber for the input point cloud
// 爲接受點雲數據創建一個訂閱節點
  ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2> ("input", 1, cloud_cb);
 
  // Create a ROS publisher for the output point cloud
//創建ROS的發佈節點
  pub = nh.advertise<sensor_msgs::PointCloud2> ("output", 1);
 
  // Spin
// 回調
  ros::spin ();
}