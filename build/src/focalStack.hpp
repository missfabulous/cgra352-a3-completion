

// opencv
#include <opencv2/core/core.hpp>


void loadImages(char** argv, cv::Mat lightField[17][17], cv::Mat UV);
void displayImage(cv::Mat image, cv::String name);
cv::Vec3b getPoint(int row, int col, int t, int s, cv::Mat lightField[17][17]);
void generateFocalStack(cv::Mat output, cv::Mat lightField[17][17], float focalLength, cv::Mat UV);
cv::Vec2f getUV(int row, int col, cv::Mat UV);