#include "slamBase.h"

#include <iostream>
using namespace std;

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// PCL
#include <pcl/registration/icp.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/cloud_viewer.h>

// Eigen
#include <Eigen/Core>
#include <Eigen/Geometry>

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        cout<<"wrong input\n"<<endl;
        return 0;
    }

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_source (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_target (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_source_registration (new pcl::PointCloud<pcl::PointXYZ>);

    if(pcl::io::loadPCDFile<pcl::PointXYZ>(argv[1], *cloud_source)==-1) {
		std::cout << "load source failed!" << std::endl;
		return -1;
	}
    if(pcl::io::loadPCDFile<pcl::PointXYZ>(argv[2], *cloud_target)==-1) {
		std::cout << "load target failed!" << std::endl;
		return -1;
	}

    pcl::IterativeClosestPoint< pcl::PointXYZ, pcl::PointXYZ> icp;
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree1 (new pcl::search::KdTree<pcl::PointXYZ>);
    tree1->setInputCloud(cloud_source);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree2 (new pcl::search::KdTree<pcl::PointXYZ>);
    tree2->setInputCloud(cloud_target);
    icp.setSearchMethodSource(tree1);
	icp.setSearchMethodTarget(tree2);
	icp.setInputSource(cloud_source);
	icp.setInputTarget(cloud_target);
    icp.setMaxCorrespondenceDistance(1500);
	icp.setTransformationEpsilon(1e-10);
	icp.setEuclideanFitnessEpsilon(0.1);
	icp.setMaximumIterations(300);
    icp.align(*cloud_source_registration);
	Eigen::Matrix4f transformation = icp.getFinalTransformation();
    double score = icp.getFitnessScore();
	std::cout << transformation << std::endl
              << "fitness score: " << score << std::endl; 

    pcl::visualization::PCLVisualizer viewer( "viewer" );
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> src_r_h(cloud_source_registration, 255, 0, 0);
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> tgt_h (cloud_target, 0, 255, 0);
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> src_h (cloud_source, 0, 0, 255);
	viewer.addPointCloud(cloud_source_registration, src_r_h,"source_r");
	viewer.addPointCloud(cloud_target, tgt_h, "target");
	viewer.addPointCloud(cloud_source, src_h, "source");
	viewer.spin();
    return 0;
}
