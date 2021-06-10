#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const int MAX=1e4+79;

/**
  u is the control parameter for logistic chaotic map,also known as population rate
  Here u is taken 3.94
  
  x is the vector that contain the value generated by chaotic map
  The initial value of the logistic chaotic map is 0.4
*/

int main()
{
  Mat image;
  int i,l;
  double u=3.94;         
  vector<pair<double,int >> x;
  Vec<unsigned char, 3>  pixel;

  image = imread("Image/encrypted_image.jpg", 0 );
  if ( !image.data )
  {
    cout<<"No image data \n";
    return -1;
  }

  x.push_back({0.4,0});


  double temp;
  for (int i = 1; i <= 511; ++i){
    temp=u*x[i-1].first*(1-x[i-1].first);
    x.push_back({temp,i});
  }

  sort(x.begin(), x.end());

  imshow("Decrepted image", image);
  waitKey(0);

  i=1;
  for(int r = 0; r < image.rows; ++r) {
    for(int c = 0; c < image.cols; ++c) {
      if(i>100){
        i=1;
      }
      l=x[i].first*MAX;
      l=l%255;
      image.at<Vec3b>(r,c)[0]=image.at<Vec3b>(r,c)[0]^l;
      image.at<Vec3b>(r,c)[1]=image.at<Vec3b>(r,c)[1]^l;
      image.at<Vec3b>(r,c)[2]=image.at<Vec3b>(r,c)[2]^l;
      i++;
    }
  }

  i=511;
  for(int r = image.rows-1; r >= 0; --r) {
    for(int c = image.cols-1; c >= 0 ; --c) {
      if(i<0)
        i=511;
      int temps= x[i].second;

      pixel= image.at<Vec3b>(r,temps);
      image.at<Vec3b>(r,temps)=image.at<Vec3b>(r,c);
      image.at<Vec3b>(r,c)=pixel;

      i--;
    }
  }

  namedWindow("Original_image", WINDOW_AUTOSIZE );
  imshow("Original_image", image);
  waitKey(0);

  return 0;

}