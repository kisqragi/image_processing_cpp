#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>

#include "proc.hpp"

int main() {
  
  std::string result = "result/result.mp4";
  std::string image_name = "test/test";
  double frame_rate = 30.0;
  int frame_num = 900; 
  std::string ext = ".jpg";

  //int ret = image_to_video(result, image_name, ext, frame_num, frame_rate);
  //int ret = video_to_image(image_name, result, ext);


  return 0;
  
}
