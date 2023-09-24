#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<qimage.h>

#include<opencv2/opencv.hpp>
#include<opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>

#include <vtkSmartPointer.h>

#include<vtkCylinderSource.h>
#include<vtkPolyDataMapper.h>

#include<vtkActor.h>
#include<vtkRenderer.h>
#include<vtkGenericOpenGLRenderWindow.h>
#include <vtkGenericRenderWindowInteractor.h>

#include<pcl-1.13/pcl/point_types.h>
#include<pcl-1.13/pcl/io/ply_io.h>
#include<pcl-1.13/pcl/visualization/pcl_visualizer.h>

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scence_show_image();
    opengl_show_pcl();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::scence_show_image()
{
    cv::Mat src = cv::imread("/home/chen/Desktop/qt_image/untitled/val_y2011_003182.png",-1);
    int width = src.cols;
    int height = src.rows;
    cvtColor(src, src, cv::COLOR_BGR2RGB);
    QImage disImage = QImage(src.data, width, height,
                             QImage::Format_RGB888);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    scene->addPixmap(QPixmap::fromImage(disImage));
}
void MainWindow::opengl_show_pcl()
{
    PointCloudT::Ptr cloud(new PointCloudT);

    // 读取点云
    std::string filename = "/home/chen/Desktop/bunny/reconstruction/bun_zipper.ply";
    if (pcl::io::loadPLYFile(filename, *cloud)<0)
    {
        std::cout << "error";
    }
    vtkSmartPointer<vtkRenderer> render= vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> openglrender= vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer (render.Get(),openglrender.Get(),"3D",false));

    viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");


    ui->openGLWidget->setRenderWindow(viewer->getRenderWindow());
}

void MainWindow::on_pushButton_clicked()
{
    std::cout<<"button clicked";
    PointCloudT::Ptr cloud(new PointCloudT);
    std::string filename = "/home/chen/Desktop/models/obj_000001.ply";
    if (pcl::io::loadPLYFile(filename, *cloud)<0)
    {
        std::cout << "error";
    }
    vtkSmartPointer<vtkRenderer> render= vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> openglrender= vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer (render.Get(),openglrender.Get(),"3D",false));

    viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");
    ui->openGLWidget->setRenderWindow(viewer->getRenderWindow());
}
