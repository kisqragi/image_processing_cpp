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
  std::string bg_path = "test/bg.jpg";
  std::string fg_path = "test/fg.jpg";
  std::string base_path = "test/base.jpg";
  std::string result_path = "result/result.jpg";
  int x_pos = 500;
  int y_pos = 500;
  int th = 10;

  //int ret = image_to_video(result, image_name, ext, frame_num, frame_rate);
  //int ret = video_to_image(image_name, result, ext);
  //int ret = image_composition(base_path, fg_path, bg_path, result_path, x_pos, y_pos, th);

  if (ret) {
    std::cout << "エラー" << std::endl;
  }


  return 0;
  
}
