#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;
using namespace cv;

int main(void) {
	int a, b, aux1 = 1, aux2 = 1, aux3 = 1, tam[2];
	string op;
	Mat img;
	Mat borda;
	VideoCapture cam(0);
	namedWindow("WebCam");
	namedWindow("Borda");
	a = 100;
	b = 100;
	while (aux1 == 1)
	{
		aux3 = 1;
		cam.read(img);
		Canny(img, borda, a, b);
		if (aux2 == 1){
			int col = borda.cols;
			int row = borda.rows;
			aux2 += 1;
		}
		/*
		for (int y = 50; y <= 430 ; y++){
			for (int x = 100; x <= 540; x++){
				if (borda.at<int>(x, y) == 255 && aux3 == 1) { tam[0] = y; aux3 = 2; }
				else if (borda.at<int>(x, y) == 255) { tam[1] = y; }
			}
		}
		cout << tam[1] - tam[0] << endl;
		*/
		putText(img, "Ola  mundo", { 0,475 }, CV_FONT_HERSHEY_SIMPLEX, 1,{ 0,255,0 }, 3, cv::LINE_AA);
		rectangle(img, { 100,50 }, { 540,430 }, { 0,255,0 }, 2, cv::LINE_AA,0);
		imshow("WebCam", img);
		imshow("Borda", borda);
		waitKey(25);
		if (_kbhit()) {
			cin >> op;
			if (op == "a") { cin >> a; }
				else if (op == "b") { cin >> b; }
				else if (op == "abort") { aux1 +=1;}
		}	
	}
	
	system("pause");
}