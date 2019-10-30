#ifndef _PROC_H_
#define _PROC_H_


int image_to_video(std::string result, std::string image_name, std::string ext, int frame_num, double frame_rate);

int video_to_image(std::string result_image_name, std::string video_path, std::string ext);

#endif
