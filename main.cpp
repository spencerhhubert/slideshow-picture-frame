#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

namespace fs = std::filesystem;

std::vector <std::string> get_files(std::string directory) {
	std::vector <std::string> output;
	int i = 0;
	for (const auto& entry : fs::directory_iterator(directory)) {
		output.push_back(entry.path().filename());
		//std::cout << output[i] << '\n';
		i+=1;
	}
	return output;
}

cv::Mat scale(cv::Mat img, int des_width, int des_height) {
	int ori_width = img.size().width;
	int ori_height = img.size().height;
	float h_fac = (float)des_height / (float)ori_height;
	float w_fac = (float)des_width / (float)ori_width;
	float factor;
	if(h_fac <= w_fac){factor = h_fac;}else{factor = w_fac;} 

	int out_width = (int)(ori_width * factor);
	int out_height = (int)(ori_height * factor);

	cv::Mat output;
	cv::resize(img, output, cv::Size(out_width, out_height), cv::INTER_AREA);
	return output; 
}

int print_size(cv::Mat img) {
	std::cout << "Width: " << img.size().width << "\n";
	std::cout << "Height: " << img.size().height << "\n";
	return 0;
}

std::string addDir(std::string dir, std::string file) {
	return dir + "/" + file;
}

int fade(cv::Mat img1, cv::Mat img2, std::string window) {
	int fade_length = 1000; //in milliseconds
	cv::Mat blended;
	cv::imshow(window, img2);
	for(int i=0; i<100; i++){
		double alpha = (double)(100 - i) / (double)100;
		double beta = (1.0 - alpha);
		cv::addWeighted(img1, alpha, img2, beta, 0.0, blended);
		cv::imshow(window, blended);
		cv::waitKey(fade_length/100);
	}
	return 0;
}

int mat_deets(cv::Mat mat){
	std::cout << "Size: " << mat.size() << "\n";
	std::cout << "Channels: " << mat.channels() << "\n";
	std::cout << "Type: " << mat.type() << "\n";
	return 0;
}

int let_or_col_box(cv::Mat img, int res_w, int res_h){
	// 1 = letterbox
	// 2 = columnbox
	int img_w = img.cols;
	int img_h = img.rows;
	double img_asp_rat = (double)img_w / (double)img_h;
	double mon_asp_rat = (double)res_w / (double)res_h;
	if(img_asp_rat > mon_asp_rat) {
		return 1;
	} else {
		return 2;
	}
}

cv::Mat box(cv::Mat img, int res_w, int res_h) {
	// make new mat that is both the proper resolution and with black columns or rows
	// to represent letterboxing or pillarboxing
	cv::Mat output = cv::Mat::zeros(res_h, res_w , 16);
	img = scale(img, res_w, res_h);
	if(let_or_col_box(img, res_w, res_h)==1) {
		// letterbox
		img.copyTo(output(cv::Rect(0, (res_h - img.rows)/2, img.cols, img.rows)));
	} else {
		// columnbox
		img.copyTo(output(cv::Rect((res_w - img.cols)/2, 0, img.cols, img.rows)));
	}	
	return output;
}

int main(){
	int res_w = 3440;
	int res_h = 1440;
	std::string dir = "/media/spencer/pictures";
	while(true){
		
		std::vector <std::string> file_names = get_files(dir);
		for(int i=0; i<file_names.size()-1; i++) {
			cv::Mat img = cv::imread(addDir(dir, file_names[i]), cv::IMREAD_COLOR);
			img = box(img, res_w, res_h);
			cv::Mat next_img = cv::imread(addDir(dir, file_names[i+1]), cv::IMREAD_COLOR);
			next_img = box(next_img, res_w, res_h);
			//print_size(img);

			cv::namedWindow("window", cv::WND_PROP_FULLSCREEN);
			cv::setWindowProperty("window",cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
			
			cv::imshow("window", img);
			cv::waitKey(500);
			if(i<file_names.size()-1){
				fade(img, next_img, "window");
			}
			cv::waitKey(500);
			//std::cout << "next: \n\n";
			//mat_deets(img);
		}
		cv::destroyWindow("window");
	}
	return 0;
}
