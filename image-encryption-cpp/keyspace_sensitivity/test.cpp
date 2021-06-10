#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/**
  u is the control parameter for logistic chaotic map,also known as population rate
  Here u is taken 3.94
  x is the vector that contain the value generated by chaotic map
  The initial value of the logistic chaotic map is 0.4
*/

int main(){

  Mat image,encImage1,difference_perm_diff;
  int n;

  encImage1 = imread("perm_diff_1.jpg", 0 );
  if ( !image.data )
  {
    cout<<"No image data \n";
    return -1;
  }

  difference_perm_diff = imread("Image/keyspace_sensitivity/difference_perm_diff.jpg", 0 );
  if ( !image.data )
  {
    cout<<"No image data \n";
    return -1;
  }

  cout<<"Enter the number of iteration you want :";
  cin>>n;

  for (int i = 0; i < n; ++i){
    image = encImage1 - difference_perm_diff;
    encImage1 = image;
    imshow("The difference image from the difference image", image);
    waitKey(0);    
  }


  return 0;

}