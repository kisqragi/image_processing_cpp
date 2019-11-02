#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>

int video_to_image(std::string result_image_name, std::string video_path, std::string ext) {

  cv::VideoCapture video(video_path);

  if (!video.isOpened()) {
    return -1;
  }

  int frame_num = video.get(cv::CAP_PROP_FRAME_COUNT);

  // {image_name}_00x.ext にするための桁数の取得
  int digit = std::to_string(frame_num).length();

  cv::Mat frame;
  int i;

  for (i = 0; i < frame_num; i++) {

    // フレームを取得する
    video >> frame;

    if (frame.empty()) {
      return -1;
    }
    // {image_name}_00x.extの文字列作成
    std::stringstream ss;
    ss << result_image_name << "_" << std::setw(digit) << std::setfill('0') << i << ext;
    std::cout << ss.str() << std::endl;

    cv::imwrite(ss.str().c_str(), frame);

  }

  return i;
}

int main() {
  
  std::string video_path = "../../sample/video/video.mov";
  std::string result_image_name = "../../result/frame/frame";
  std::string ext = ".jpg";

  int ret = video_to_image(result_image_name, video_path, ext);

  if (ret && ret != -1) {
    std::cout << "画像の書き出しが完了しました。" << std::endl;
    std::cout << "動画の枚数は" << ret << "枚です。" << std::endl;
  }

  return 0;
  
}
