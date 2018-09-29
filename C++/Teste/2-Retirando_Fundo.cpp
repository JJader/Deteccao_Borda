#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

using namespace cv;

//Vetor de auxiliares
int aux[] = { 0,0,0,0,0,0,0,0,0,0 };

//Struct para definição da área de interesse
struct ROI {
	int col;
	int row;
};

//Struct para definição dos limiares do método Canny
struct LIM {
	int sup;
	int inf;
};

//Struct pra definição das coordenadas dos pontos encontrados
struct COOR {
	int i;
	int j;
};

//Criação de uma variável do tipo ROI (Regiao de interesse) de tamanho 2 (início e fim)
struct ROI roi[2];

//Função para selecionar o ROI (Regiao de iteresse) a partir do click na tela
//Auxiliar 3 para comutar entre coordenadas inicial e final
void mouse_callback(int event, int x, int y, int flag, void *param) {
	if ((event == EVENT_LBUTTONDBLCLK) && (aux[3] == 0)) {
		cout << "(" << x << ", " << y << ")" << endl;
		roi[0].col = x;
		roi[0].row = y;
		aux[3] = 1;
	}
	else if ((event == EVENT_LBUTTONDBLCLK) && (aux[3] == 1)) {
		cout << "(" << x << ", " << y << ")" << endl;
		roi[1].col = x;
		roi[1].row = y;
		aux[3] = 0;
	}
}

int main() {

	namedWindow("Nissin");
	cvCreateTrackbar("Peao", "Nissin", 0, 1);
	cvCreateTrackbar("A", "Nissin", 0, 500);
	cvCreateTrackbar("B", "Nissin", 0, 500);
	cvSetTrackbarPos("A", "Nissin", 100);
	cvSetTrackbarPos("B", "Nissin", 100);

	struct LIM lim; //Variavel lim do tipo LIM para limiarização Canny
	struct COOR coor[4]; //Vetor coor de tamanho 4 para encontrar quatro pontos na imagem (em teste)
	Mat img; //A imagem lida da WebCam é armazenada nessa matriz
	Mat	model; //Uma primeira imagem do cenário é salva nessa matriz para fins de subtração (Background Subtraction)
	Mat	dif; //Nessa matriz sera armazenada a diferença entre a Matriz model e a Matriz img
	Mat gray; //Matriz para armazenar a transformação para escalas de cinza
	Mat channel[3]; //Matrizes para armazenar as três bandas (Red, blue, Green)
	Mat borda; //Matriz para armazenar a borda

	
	namedWindow("imBorda"); // Cria janela para impressão da imagem de bordas
	namedWindow("webcam"); // Cria janela para impressão da imagem de bordas
	namedWindow("Gray"); // Cria janela para impressão da imagem de bordas
	
	moveWindow("WebCam", 0, 0);
	moveWindow("imBorda", 700, 0);
	moveWindow("Gray", 0, 0);
	moveWindow("Nissin", 450, 400);


	VideoCapture cam(0); // Ativa webcam
	waitKey(2000);
	cam.read(model);
	model = Mat::zeros(model.size(),model.type());
	cvtColor(model, model, COLOR_RGB2GRAY);

	//Loop infinito
	while (true) {
		
		setMouseCallback("imColor", mouse_callback); // Definição do ROI
		lim.inf = cvGetTrackbarPos("A", "Nissin");
		lim.sup = cvGetTrackbarPos("B", "Nissin");
		
		cam.read(img); // Leitura da imagem em modo Vivo
		cvtColor(img, gray, COLOR_BGR2GRAY); // Conversão matriz DIF para escala de cinzas
	//	morphologyEx(gray, gray, 4, Mat1b(3, 3, 1));
		imshow("Gray", gray);

		if(cvGetTrackbarPos("Peao", "Nissin") == 1){
			gray.copyTo(model);
		}
		dif = abs(model - gray); // A matriz dif recebe a diferença entre o modelo e o Ao Vivo
		
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				if (dif.at<uchar>(i, j) >= 0 && dif.at<uchar>(i, j) < 50) {
					gray.at<uchar>(i, j) = 0;
				}
			}
		}
		
		GaussianBlur(gray, gray, Size(3, 3), 7, 7);
		Canny(gray, borda, lim.sup, lim.inf, 3);

		imshow("webcam", gray);
		imshow("imBorda", borda);
		waitKey(20);
	}

	return 0;
}

//GrabCut
