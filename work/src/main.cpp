
// std
#include <iostream>

// opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;


// main program
// 
int main( int argc, char** argv ) {

	// check we have exactly one additional argument
	// eg. res/vgc-logo.png
	if( argc != 1) {
		return -1;
	}


	// create a window for display and show our image inside it
	string img_display = "Image Display";
	namedWindow(img_display, WINDOW_AUTOSIZE);
	imshow(img_display, image);


	string inv_img_display = "Inverted Image Display";
	namedWindow(inv_img_display, WINDOW_AUTOSIZE);
	//imshow(inv_img_display, inverted);


	// wait for a keystroke in the window before exiting
	waitKey(0);
}