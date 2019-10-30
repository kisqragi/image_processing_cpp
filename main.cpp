#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>

#include "proc.hpp"

int main() {
  
  std::string result = "result/result.mp4";
  std::string image_name = "test/bg";
  double frame_rate = 30.0;
  int frame_num = 900; 
  std::string ext = ".jpg";

  int ret = image_to_video(result, image_name, ext, frame_num, frame_rate);

  if (ret)
    std::cout << "フレームが指定の数ありませんでした" << std::endl;
  else
    std::cout << "動画の書き出しが完了しました。" << std::endl;

  return 0;
  
}
