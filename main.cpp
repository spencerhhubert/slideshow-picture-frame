#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <opencv2/opencv.hpp>
namespace fs = std::filesystem;

std::vector <std::string> get_files(std::string directory) {
	std::vector <std::string> output;
	int i = 0;
	for (const auto& entry : fs::directory_iterator(directory)) {
		output.push_back(entry.path().filename());
		std::cout << output[i] << '\n';
		i+=1;
	}
	return output;
}

int main() {
	std::string directory = "pictures";
	std::vector <std::string> file_names = get_files(directory);

}
