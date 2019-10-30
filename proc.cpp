#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>

/* 複数の画像ファイルから動画を作成する関数 */
int image_to_video(std::string result, std::string image_name, std::string ext, int frame_num, double frame_rate) {

  // {image_name}_00x.ext にするための桁数の取得
  int digit = std::to_string(frame_num).length();
  
  std::stringstream base;
  base << image_name << "_" << std::setw(digit) << std::setfill('0') << 0 << ext;
  cv::Mat Img = cv::imread(base.str().c_str());

  namedWindow("image", cv::WINDOW_AUTOSIZE);

  int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
  cv::VideoWriter writer(result, fourcc, frame_rate, cv::Size(Img.cols, Img.rows), true);

  int c;

  for (int i = 0; i < frame_num; i++) {

    // {image_name}_00x.extの文字列作成
    std::stringstream ss;
    ss << image_name << "_" << std::setw(digit) << std::setfill('0') << i << ext;
    std::cout << ss.str() << std::endl;

    // フレームを取得する
    Img = cv::imread(ss.str().c_str());

    /*
    リサイズする場合にはここを変更する
    Size size = {Img.rows, Img.cols};
    resize(Img, Img, size, 1, 1); // 後半二つの値は倍率を示す
    */

    if (Img.empty()) {
      return -1;
    }

    // フレームの書き出し
    writer << Img;

  }
  return 0;
}

/* 動画からフレームを切り出して出力する */
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


