#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include<pcl/point_cloud.h>

using namespace std;

void outlier_removal(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &points, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &downsampled_out)
{
  pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> pass;
  pass.setMeanK(50);
  pass.setStddevMulThresh(1.0);
  pass.setInputCloud(points);
  pass.filter(*downsampled_out);
}

void read_pcd(string filename){
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr filtered_output(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  if (pcl::io::loadPCDFile<pcl::PointXYZRGB> (filename, *cloud)==-1)
  {
    PCL_ERROR("Couldnt read the file\n");
  }
  outlier_removal(cloud, filtered_output);
  pcl::io::savePCDFileASCII("StatisticalOutlierRemoval.pcd",*filtered_output);
}

int main(int argc, char** argv)
{
  read_pcd("/home/abhishek/tensorflow/Projects/PCL/sample.pcd/1427157650.349046016.pcd");
  return 0;
}
