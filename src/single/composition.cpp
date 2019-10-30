#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>

/* img1とimg2の差分を返す */
cv::Mat frame_sub(cv::Mat& img1, cv::Mat& img2, int th = 20) {

  cv::Mat diff;
  cv::Mat mask;

  cv::absdiff(img1, img2, diff);
  cv::threshold(diff, mask, th, 255, cv::THRESH_BINARY);

  return mask;

}

/* 画像を合成する */
int image_composition(std::string base_path, std::string fg_path, std::string bg_path, std::string result_path, int x_pos = 0, int y_pos = 0, int th = 10) {

  // ベース画像の設定
  cv::Mat base_frame;
  base_frame = cv::imread(base_path.c_str());
  cv::cvtColor(base_frame, base_frame, cv::COLOR_BGR2GRAY);

  // 画像の読み込み 
  cv::Mat bg = cv::imread(bg_path.c_str());
  cv::Mat fg = cv::imread(fg_path.c_str());

  // ROIがbg画像内に収まるように座標を調整
  if (x_pos + fg.cols > bg.cols) {
    x_pos = bg.cols - fg.cols;
  }
  if (y_pos + fg.rows > bg.rows) {
    y_pos = bg.rows - fg.rows;
  }
  if (x_pos < 0 || y_pos < 0)
    return -1;

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

int main() {
  
  std::string bg_path = "../../sample/images/bg.jpg";
  std::string fg_path = "../../sample/images/fg.jpg";
  std::string base_path = "../../sample/images/base.jpg";
  std::string result_path = "../../result/result.jpg";
  int x_pos = 0;
  int y_pos = 0;
  int th = 15;

  int ret = image_composition(base_path, fg_path, bg_path, result_path, x_pos, y_pos, th);

  if (!ret)
    std::cout << "合成完了" << std::endl;
  else
    std::cout << "エラー" << std::endl;

}
