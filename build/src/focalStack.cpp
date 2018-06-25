// std
#include <iostream>


// opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

#include "focalStack.hpp"


void loadImages(char** argv, Mat lightField[17][17], Mat UV) {
	// parse all images
	std::cout << "Loading light field ..." << std::endl;
	std::vector<cv::String> lf_imgs;
	cv::glob(argv[1], lf_imgs);
	for (cv::String cv_str : lf_imgs) {
		// get the filepath
		std::string filepath(cv_str);
		size_t pos = filepath.find_last_of("/\\");
		if (pos != std::string::npos) {
			// replace "_" with " "
			std::string filename = filepath.substr(pos + 1);
			pos = 0;
			while ((pos = filename.find("_", pos)) != std::string::npos) {
				filename.replace(pos, 1, " ");
				pos++;
			}
			// parse for values
			std::istringstream ss(filename);
			std::string name;
			int row, col;
			float v, u;
			ss >> name >> row >> col >> v >> u;
			if (ss.good()) {
				// TODO something with the image file "filepath"
				// TODO something with the coordinates: row, col, v, u
				lightField[row][col] = imread(filepath, CV_LOAD_IMAGE_COLOR);
				UV.at<Vec2f>(row, col) = Vec2f(v, u);
				continue;
			}
		}
		// throw error otherwise
		std::cerr << "Filepath error with : " << filepath << std::endl;
		std::cerr << "Expected in the form : [prefix]/[name]_[row]_[col]_[v]_[u][suffix]";
		abort();
	}
	std::cout << "Finished loading light field" << std::endl;
}

cv::Vec2f getUV(int row, int col, Mat UV) {
	return UV.at<Vec2f>(row, col);
}

void generateFocalStack(cv::Mat output, cv::Mat lightField[17][17], float focalLength, cv::Mat UV) {
	int numRows = lightField[0][0].rows;
	int numCols = lightField[1][1].cols;
	Vec2f centre = Vec2f(-776.880371, 533.057190);
	//create new light field
	for (int r = 0; r < 17; r++) {
		for (int c = 0; c < 17; c++) {
			Vec2f uv = getUV(r, c, UV);
			Vec2f uvDist = centre - uv;
			for (int i = 0; i < numRows; i++) {
				for (int j = 0; j < numCols; j++) {
					Mat current = lightField[r][c];
					int s = ((focalLength*j) / uv[1]) + uv[1];
					int t = ((focalLength*i) / uv[0]) + uv[0];
					int newS = uvDist[1] + (((focalLength*j)-uvDist[1])/focalLength);
					int newT = uvDist[0] + (((focalLength*i) - uvDist[0]) / focalLength);
				}
			}
			
		}
	}


}

cv::Vec3b getPoint(int row, int col, int t, int s, Mat lightField[17][17]) {
	return lightField[row][col].at<Vec3b>(t, s);
}


void displayImage(Mat image, String name) {
	// create a window for display and show our image inside it
	namedWindow(name, WINDOW_NORMAL);
	imshow(name, image);
}

