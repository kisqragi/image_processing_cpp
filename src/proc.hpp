#ifndef _PROC_H_
#define _PROC_H_

/* 複数の画像ファイルから動画を作成する関数 */
int image_to_video(std::string result, std::string image_name, std::string ext, int frame_num, double frame_rate);

/* 動画からフレームを切り出して出力する */
int video_to_image(std::string result_image_name, std::string video_path, std::string ext);

/* img1とimg2の差分をmaskとして返す
    image_compositionで使用         */
cv::Mat frame_sub(cv::Mat& img1, cv::Mat& img2, int th = 20);

/* 画像を合成する */
int image_composition(std::string base_path, std::string fg_path, std::string bg_path, std::string result_path, int x_pos = 0, int y_pos = 0, int th = 10);

#endif
