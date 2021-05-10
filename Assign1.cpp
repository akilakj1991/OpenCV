#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <highgui.h>
#include <cv.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;

int main(int argc, char** argv){
	Mat src, src_gray;    // Create Matix variable for the imput image and the gray image
	Mat grad;			//Create Metrix variable for output image
	char* window_name = "Edge Detected Image"; //specify the name for the output window 
	char* window_name1 = "Original Image";  //specify the name for the original image window
	char* window_name2 = "SobelX";      //specify the name for the abolute x axis scan window
	char* window_name3 = "SobelY";		//specify the name for the abolute y axis scan window
	char* window_name4 = "Gray Image";  //specify the name for the gray window
	int scale = 2;    // scale put the brightness or contrast of the edge lines 
	int delta = 0;
	int ddepth = CV_64F;  
	int c;
	/// Load an image
	//src = imread(arg[1]); //assign the image as the argument of the function
	src = imread("Image1.JPG"); // reading out the image for the directory 
	resize(src, src, Size(), 0.3, 0.3, CV_INTER_AREA); // resize the image reduce the width of the x and y by 30%
	if (!src.data)  //check the image has been imported other wise break the function
	{
		return -1;  // return of -1 breaks the fuction because there is no image been loaded into the matrix
	}
	GaussianBlur(src, src, Size(3, 3), 1, 1, BORDER_CONSTANT); // blur the image in order to take out unwanted noise
															   // with a Gaussian function (X) SD=1 and (Y) SD=1
																
	/// Convert it to gray
	cvtColor(src, src_gray, CV_BGR2GRAY); // convert the image to a gray image in order to start the scaning process
										// CV_BGR2GRAY converts image colour gray
	/// Create window
	namedWindow(window_name, CV_WINDOW_AUTOSIZE); // Create a arbitary window for saving the gray colour image
													// CV_WINDOW_AUTOSIZE maintain the window size from previous operation
	/// Generate grad_x and grad_y
	Mat grad_x, grad_y;    // creating the matries for x axis scans and y axis scans
	Mat abs_grad_x, abs_grad_y;  // creating the matries for absoulte values of x axis scans and y axis scans
	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_CONSTANT); // scaning the gray image with dx=1 for x-axis image
																			// scale=1 delta=0 kernal size=3*3 ddepth=CV_16S
	convertScaleAbs(grad_x, abs_grad_x);     // convert prvious matrix into an absoulte value matrix
	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_CONSTANT); // scaning the gray image with dy=1 for y-axis image
																			 // scale=1 delta=0 kernal size=3*3 ddepth=CV_16S
	convertScaleAbs(grad_y, abs_grad_y);	 // convert prvious matrix into an absoulte value matrix
	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	imshow(window_name2, abs_grad_x);  //Show out puts of the images
	imshow(window_name3, abs_grad_y);
	imshow(window_name1, src);
	imshow(window_name4, src_gray);
	imshow(window_name, grad);			//Show the final processed image
	waitKey(0);
	return 0;
}
