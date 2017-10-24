#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/filters/voxel_grid.h>
#include<pcl/point_cloud.h>

using namespace std;

void downsample(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &points, float leaf_size, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &downsampled_out)
{
  pcl::VoxelGrid<pcl::PointXYZRGB> vox_grid;
  vox_grid.setLeafSize(leaf_size,leaf_size,leaf_size);
  vox_grid.setInputCloud(points);
  vox_grid.filter(*downsampled_out);
}

void read_pcd(string filename){
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr filtered_output(new pcl::PointCloud<pcl::PointXYZRGB>);
  if (pcl::io::loadPCDFile<pcl::PointXYZRGB> (filename, *cloud)==-1)
  {
    PCL_ERROR("Couldnt read the file\n");
  }
  for (size_t i=0; i<cloud->points.size(); i++)
  {
    cout<<cloud->points[i].x<<" ----  ";
    cout<<cloud->points[i].y<<" ----  ";
    cout<<cloud->points[i].z<<" ----  ";
    cout<<cloud->points[i].rgb<<" ---- ";

    cout<<"\n";
  }
  downsample(cloud, 0.01, filtered_output);
  pcl::io::savePCDFileASCII("filtered_output.pcd",*filtered_output);
}

int main(int argc, char** argv)
{
  read_pcd("/home/abhishek/tensorflow/Projects/PCL/sample.pcd/1427157650.349046016.pcd");
  
  return 0;
}
