#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <conio.h>


using namespace std;
using namespace cv;






int main(void) {
	int a, b, aux1 = 1, aux2 = 1, aux3 = 1;
	int name = 0, nome = 0, tam[2];
	int col, row;
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
		
		cam.read(img);
		Canny(img, borda, a, b);
		
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
				else if (op == "saveb"){
					ostringstream con;
					con << name;
					imwrite("borda" + con.str() + ".jpg", borda);
					name++;
				}
				else if (op == "saveim") {
					ostringstream con;
					con << nome;
					imwrite("imagen" + con.str() + ".jpg", img);
					nome++;
				}
				else{
					system("cls");
					cout << "a      --> Alterar A" << endl;
					cout << "b      --> Alterar B" << endl;
					cout << "saveb  --> Salvar borda" << endl;
					cout << "saveim --> Salvar imagem" << endl;
					cout << "abort  --> Finalizar" << endl << endl;
				}}
	}
	col = borda.cols;
	row = borda.rows;

	for (int y = 0; y < col; y++)
	{
		for (int x = 0; x < row; x++)
		{
			if (borda.at<uchar>(x, y) == 255 && aux3 == 1){
				tam[0] = y;
				aux3++;
			}
			else if (borda.at<uchar>(x, y) == 255) {
				tam[1] = y;
			}
			printf("%d ", (borda.at<uchar>(x,y)));
		}
		printf(";\n");
	}
	printf("%d \n%d\n", tam[0], tam[1]);
	system("pause");
	return 0;
}