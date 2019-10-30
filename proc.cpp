#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>

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

cv::Mat frame_sub(cv::Mat& img1, cv::Mat& img2, int th = 20) {

  cv::Mat diff;
  cv::Mat mask;

  cv::absdiff(img1, img2, diff);
  cv::threshold(diff, mask, th, 255, cv::THRESH_BINARY);

  return mask;

}

int image_composition(std::string base_path, std::string fg_path, std::string bg_path, std::string result_path, int x_pos = 0, int y_pos = 0, int th = 10) {

  // ベース画像の設定
  cv::Mat base_frame;
  base_frame = cv::imread(base_path.c_str());
  cv::cvtColor(base_frame, base_frame, cv::COLOR_BGR2GRAY);

  // 画像の読み込み 
  cv::Mat bg = cv::imread(bg_path.c_str());
  cv::Mat fg = cv::imread(fg_path.c_str());

  // ROIがbg画像内に収まるように座標を調整
  if ((x_pos + fg.cols) > bg.cols) {
    x_pos = bg.cols - fg.cols;
  }
  if ((y_pos + fg.rows) > bg.rows) {
    y_pos = bg.rows - fg.rows;
  }
  if (x_pos < 0 || y_pos < 0) {
    return -1;
  }

  // ROI(領域)の作成 
  cv::Rect rect_roi(x_pos, y_pos, fg.cols, fg.rows);
  cv::Mat roi = bg(rect_roi);

  cv::Mat fg_gray;
  cv::cvtColor(fg, fg_gray, cv::COLOR_BGR2GRAY);

  cv::Mat mask;    
  mask = frame_sub(base_frame, fg_gray, th);

  cv::Mat mask_inv;
  cv::bitwise_not(mask, mask_inv);  

  cv::Mat fg_down;
  cv::bitwise_and(roi, roi, fg_down, mask_inv);  

  cv::Mat fg_up;
  cv::bitwise_and(fg, fg, fg_up, mask);  

  cv::Mat dst;
  cv::add(fg_down, fg_up, roi);

  cv::imwrite(result_path.c_str(), bg);

  return 0;
}

