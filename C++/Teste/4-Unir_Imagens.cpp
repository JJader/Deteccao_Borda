#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat img, ol, borda;
	VideoCapture cam(0);
	namedWindow("Borda");
	namedWindow("Borda1");
	Rect roi, roi2;
	roi = Rect(190, 230, 260, 60);
	roi2 = Rect(200, 240, 250, 50);
	while (1) {
	
		cam.read(img);
		Canny(img, borda, 100, 100);
		ol = borda(roi);
		cvtColor(ol, ol, CV_GRAY2BGR);
		//ol.copyTo(img(roi2));
		imshow("Borda", img(roi2));
		imshow("Borda1", ol);
		waitKey(25);

	}

}