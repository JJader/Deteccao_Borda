#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <conio.h>

using namespace std;
using namespace cv;

int main(void) {
	int a, b;
	char op;
	Mat img;
	Mat borda;
	VideoCapture cam(0);
	namedWindow("WebCam");
	namedWindow("Borda");
	a = 100;
	b = 100;
	while (true)
	{
		cam.read(img);
		Canny(img, borda, a, b);
		imshow("WebCam", img);
		imshow("Borda", borda);
		waitKey(25);
		if (_kbhit()) {cin >> op; if (op == 'a') { cin >> a; }else {if (op == 'b') { cin >> b; }}}
	}
}