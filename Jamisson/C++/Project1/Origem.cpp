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
	Mat source;
	Mat img;
	VideoCapture cam(0);
	namedWindow("WebCam");
	namedWindow("Borda");
	a = 100;
	b = 100;
	while (true)
	{
		cam.read(source);
		Canny(source, img, a, b);
		imshow("WebCam", source);
		imshow("Borda", img);
		waitKey(25);
		if (_kbhit()) {cin >> op; if (op == 'a') { cin >> a; }else {if (op == 'b') { cin >> b; }}}
	}
}