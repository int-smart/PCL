#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/filters/voxel_grid.h>
#include <pcl/keypoints/sift_keypoint.h>
#include<pcl/point_cloud.h>

using namespace std;

void downsample(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &points, float leaf_size, pcl::PointCloud<pcl::PointXYZRGB>::Ptr &downsampled_out)
{
  pcl::VoxelGrid<pcl::PointXYZRGB> vox_grid;
  vox_grid.setLeafSize(leaf_size,leaf_size,leaf_size);
  vox_grid.setInputCloud(points);
  vox_grid.filter(*downsampled_out);
}

void detect_keypoints(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &points, float min_scale,
int nr_octaves, int nr_scales_per_octave, float min_contrast, pcl::PointCloud<pcl::PointWithScale>::Ptr &keypoints_out){
  pcl::SIFTKeypoint<pcl::PointXYZRGB, pcl::PointWithScale> sift_detect;

  sift_detect.setSearchMethod(pcl::search::KdTree<pcl::PointXYZRGB>::Ptr(new pcl::search::KdTree<pcl::PointXYZRGB>));

  sift_detect.setScales(min_scale, nr_octaves, nr_scales_per_octave);
  sift_detect.setMinimumContrast(min_contrast);

  sift_detect.setInputCloud(points);
  sift_detect.compute(*keypoints_out);

}

void read_pcd(string filename){
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr filtered_output(new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointWithScale>::Ptr key(new pcl::PointCloud<pcl::PointWithScale>);
  if (pcl::io::loadPCDFile<pcl::PointXYZRGB> (filename, *cloud)==-1)
  {
    PCL_ERROR("Couldnt read the file\n");
  }
  downsample(cloud, 0.01, filtered_output);
  detect_keypoints(filtered_output, 0.01, 8, 2, 4, key);
  pcl::io::savePCDFileASCII("filtered_output.pcd",*key);
}

int main(int argc, char** argv)
{
  read_pcd("/home/abhishek/tensorflow/Projects/PCL/sample.pcd/1427157650.349046016.pcd");
  return 0;
}
