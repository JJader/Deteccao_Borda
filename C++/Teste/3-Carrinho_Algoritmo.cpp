#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "tserial.h"
#include "bot_control.h"

using namespace std;
using namespace cv;
serial comm;
bool k = true;

struct LIM {
	int sup;
	int inf;
};

void Arduino(char data) {
	char com = 'COM6';
	comm.startDevice(&com, 9600);
	comm.send_data(data);
	comm.stopDevice();
}

void configuracao() {
	string a = "v";
	cin >> a;
	if (a == "V" || a == "v") { Arduino('V'); }
	else if (a == "W" || a == "w") { Arduino('W'); }
	else if (a == "abort") { k = false; }
	else { system("cls"); }
}

int main() {

	namedWindow("Nissin");
	namedWindow("imBorda"); // Cria janela para impressão da imagem de bordas
	namedWindow("webcam"); // Cria janela para impressão da imagem de bordas

	cvCreateTrackbar("Peao", "Nissin", 0, 1);
	cvCreateTrackbar("A", "Nissin", 0, 500);
	cvCreateTrackbar("B", "Nissin", 0, 500);
	cvSetTrackbarPos("A", "Nissin", 150);
	cvSetTrackbarPos("B", "Nissin", 150);
	cvSetTrackbarPos("Peao", "Nissin", 1);

	struct LIM lim; //Variavel lim do tipo LIM para limiarização Canny
	Mat img, gray, borda; //A imagem lida da WebCam é armazenada nessa matriz
	Mat	model, dif;  //Uma primeira imagem do cenário é salva nessa matriz para fins de subtração (Background Subtraction)
					//<Dif>Nessa matriz sera armazenad a diferença entre a Matriz model e a Matriz img
	bool move = false, stop = true;

	//Setup(){
	VideoCapture cam(0); // Ativa webcam
	waitKey(2000);
	cam.read(model);
	cvtColor(model, model, COLOR_BGR2GRAY); // Conversão matriz DIF para escala de cinzas
	Arduino('V');

	//Loop()
	while (k) {

		lim.inf = cvGetTrackbarPos("A", "Nissin");
		lim.sup = cvGetTrackbarPos("B", "Nissin");

		//______________________________________________________________________________________________________________________________
				//Tratamento das imagens
		cam.read(img);
		cvtColor(img, gray, COLOR_BGR2GRAY);
		if (cvGetTrackbarPos("Peao", "Nissin") == 1) {
			gray.copyTo(model);
			cvSetTrackbarPos("Peao", "Nissin", 0);
		}


		rectangle(img, { 0,0 }, { 50,50 }, { 255,255,255 }, 2, cv::LINE_AA, 0);
		rectangle(img, { 590,50 }, { 640,0 }, { 255,255,255 }, 2, cv::LINE_AA, 0);
		rectangle(img, { 0,480 }, { 50,430 }, { 255,255,255 }, 2, cv::LINE_AA, 0);
		rectangle(img, { 590,480 }, { 640,430 }, { 255,255,255 }, 2, cv::LINE_AA, 0);

		dif = abs(model - gray); // A matriz dif recebe a diferença entre o modelo e o Ao Vivo

		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				if (dif.at<uchar>(i, j) >= 0 && dif.at<uchar>(i, j) < 50) {
					gray.at<uchar>(i, j) = 0;
				}}}

		GaussianBlur(gray, gray, Size(3, 3), 7, 7);
		Canny(gray, borda, lim.sup, lim.inf, 3);
		//______________________________________________________________________________________________________________________________
				//Detecção de objetos		
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				if (borda.at<uchar>(i, j) >= 255) {
					Arduino('B');
					cout << "Tras" << endl;
					move = true;
					stop = true;
					break;
				}}}

		for (int i = 430; i < 480; i++) {
			for (int j = 0; j < 50; j++) {
				if (borda.at<uchar>(i, j) >= 255) {
					Arduino('R');
					cout << "Direita" << endl;
					move = true;
					stop = true;
					break;
				}}}

		for (int i = 430; i < 480; i++) {
			for (int j = 590; j < 640; j++) {
				if (borda.at<uchar>(i, j) >= 255) {
					Arduino('L');
					cout << "Esquerda" << endl;
					move = true;
					stop = true;
					break;
				}}}

		for (int i = 0; i < 50; i++) {
			for (int j = 590; j < 640; j++) {
				if (borda.at<uchar>(i, j) >= 255) {
					Arduino('F');
					cout << "Frente" << endl;
					move = true;
					stop = true;
					break;
				}}}

		if (!move && stop) { Arduino('S'); stop = false; }
		move = false;

		//______________________________________________________________________________________________________________________________
				//Mostrar a imagem 
		flip(img, img, 1);
		putText(img, "Frente", { 0,80 }, CV_FONT_HERSHEY_SIMPLEX, 1, { 0,255,0 }, 3, cv::LINE_AA);
		putText(img, "Traz", { 570,80 }, CV_FONT_HERSHEY_SIMPLEX, 1, { 0,255,0 }, 3, cv::LINE_AA);
		putText(img, "Esquerda", { 0,410 }, CV_FONT_HERSHEY_SIMPLEX, 1, { 0,255,0 }, 3, cv::LINE_AA);
		putText(img, "Direita", { 540,410 }, CV_FONT_HERSHEY_SIMPLEX, 1, { 0,255,0 }, 3, cv::LINE_AA);


		imshow("webcam", img);
		imshow("imBorda", borda);
		waitKey(20);
		if (_kbhit()) { configuracao(); }
	}
	return 0;
}