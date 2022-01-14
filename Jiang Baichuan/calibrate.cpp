#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main() 
{
    int board_w = 6, board_h = 9;
    Size board_size( 6, 9 );
    Size img_size;
    Mat gray_img, drawn_img;
    vector< Point2f > point_pix_pos_buf;//����ÿ��ͼ�ϼ��Ľǵ�
    vector< vector<Point2f> > point_pix_pos;//���������⵽�����нǵ�

    int found ,successes = 0;

    int count = 0;
    int k = 0, n = 0;
     for (int i = 0; i < 20; i++){
        Mat src0 = imread(to_string(i).append(".jpg"));//����ͼ��

        if (i==0){
            img_size.width = src0.cols;
            img_size.height = src0.rows;
        }

        if(findChessboardCorners( src0, board_size, point_pix_pos_buf )==0){
            cout<<"�Ҳ����ǵ�"<<endl;
        }
        else{
           cvtColor( src0, gray_img, COLOR_BGR2GRAY );
           find4QuadCornerSubpix( gray_img, point_pix_pos_buf, Size( 5, 5 ) );//�����̸�Ľǵ���о���
           point_pix_pos.push_back( point_pix_pos_buf );//������Ľǵ㱣��
           drawn_img = src0.clone();
           drawChessboardCorners( drawn_img, board_size, point_pix_pos_buf, found );
           imshow( "corners", drawn_img );
           waitKey( 50 );
        }
        point_pix_pos_buf.clear();//���
        count++;
    };
    Size square_size( 10, 10 );
    vector< Point3f > point_grid_pos_buf;
    vector< vector< Point3f > > point_grid_pos;
    vector< int > point_count;

    Mat camera_matrix( 3, 3, CV_32FC1, Scalar::all( 0 ) );//������ڲξ���
    Mat dist_coeffs( 1, 5, CV_32FC1, Scalar::all( 0 ) );//����������
    vector< Mat > rvecs;//��ת����
    vector< Mat > tvecs;//ƽ������
   

    for (int i = 0; i < successes; i++ ) {
        for (int j = 0; j < board_h; j++ ) {
            for (int k = 0; k < board_w; k++ ){
                Point3f pt;
                pt.x = k * square_size.width;
                pt.y = j * square_size.height;
                pt.z = 0;
                point_grid_pos_buf.push_back( pt );
            }
        }
        point_grid_pos.push_back( point_grid_pos_buf );//����
        point_grid_pos_buf.clear();//���
        point_count.push_back( board_h * board_w );//��h*w��ӵ������
    }

    cout << calibrateCamera( point_grid_pos, point_pix_pos, img_size, camera_matrix, dist_coeffs, rvecs, tvecs ) <<endl;//����궨
    cout << camera_matrix << endl << dist_coeffs <<endl;
    return 0;
}