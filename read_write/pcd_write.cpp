#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<iostream>
using namespace std;

void read_pcd(string filename){
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

  if (pcl::io::loadPCDFile<pcl::PointXYZ> (filename, *cloud)==-1)
  {
    PCL_ERROR("Couldn't_read_file_test_pcd.pcd_\n");
  }
  for (size_t i=0; i<cloud->points.size(); ++i)
  {
    cout<<cloud->points[i].x;
    cout<<cloud->points[i].y;
    cout<<cloud->points[i].z;
  }
}

int main(int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ> cloud;

  cloud.width = 50;
  cloud.height = 1;
  cloud.is_dense = false;
  cloud.points.resize(cloud.width*cloud.height);
  for (size_t i=0; i<cloud.points.size(); ++i)
  {
    cloud.points[i].x = 1024*rand()/(RAND_MAX+1.0f);
    cloud.points[i].y = 1024*rand()/(RAND_MAX+1.0f);
    cloud.points[i].z = 1024*rand()/(RAND_MAX+1.0f);
  }

  pcl::io::savePCDFileASCII("test_pcd.pcd",cloud);
  read_pcd("test_pcd.pcd");
  getchar();
  return 0;
}
