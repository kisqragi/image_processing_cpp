#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>

#include "proc.hpp"

int main() {
  
  std::string result = "../result/result.mp4";
  std::string video_path = "../sample/video/video.mov";
  std::string image_name = "../result/frame/frame";
  double frame_rate = 30.0;
  int frame_num = 900; 
  std::string ext = ".jpg";
  std::string bg_path = "../sample/images/bg.jpg";
  std::string fg_path = "../sample/images/fg.jpg";
  std::string base_path = "../sample/images/base.jpg";
  std::string result_path = "../result/result.jpg";
  int x_pos = 500;
  int y_pos = 500;
  int th = 10;

  int ret;

  frame_num = video_to_image(image_name, video_path, ext);
  ret = image_to_video(result, image_name, ext, frame_num, frame_rate);
  ret = image_composition(base_path, fg_path, bg_path, result_path, x_pos, y_pos, th);

  return 0;
  
}
