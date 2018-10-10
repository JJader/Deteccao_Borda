#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;
using namespace cv;

//Bloco das variáveis
typedef	struct Tamanho
{
	int first, second;
} Tamanho;

int nivelCinza;
Tamanho y, x, A, B;
VideoCapture cam(0);
Mat img, gray, model; // <img> matriz da imagem
Mat borda, borda1, dif; // <img> matriz da borda
string un;

bool unidade_cm = false, primeiro_Ponto = false, primeiro_retangulo = true;
int nameim = 0, namebo = 0; // <namebo> Nome da borda; <nameim> Nome da imagem;
int a, b, tam[3], layout = 3; // <a,b> Configuração do filtro;  <tam> posição da borda
float rel = 0.0; // <rel> relação entre pixel/cm

//------------------------------------------------------------------------------------------------------------------------------------
//Bloco das funçoes

void troca(int *primeiro, int *segundo) {
	int a;
	a = *primeiro;
	*primeiro = *segundo;
	*segundo = a;

}

void anti_Bug() {
	// fazendo a seção da borda

	if (y.first > y.second)
	{
		troca(&y.first, &y.second);
	}
	if (x.first > x.second)
	{
		troca(&x.first, &x.second);
	}
	if (y.second > img.rows) { y.second = img.rows; }
	if (x.second > img.cols) { x.second = img.cols; }

	borda1 = Mat(borda, Rect(x.first, y.first, (x.second - x.first), (y.second - y.first)));
}

void calibracao_tamanho() {
	float objcm, pxl; // <objcm> tamanho do objeto para calibração;
	cout << "Insira o Tamanho do Objeto em cm" << endl;
	cin >> objcm;
	cout << "Insira o Tamanho do Objeto em pxl ou digite zero para automatizar" << endl;
	cin >> pxl;
	if (pxl == 0){ pxl = tam[2];}
	rel = objcm * (1.0) / pxl;
	unidade_cm = true;
	cout << "Relacão prixel centimetro : " << rel << endl;
}

void configuracao() {
	string op;
	cin >> op;
	if (op == "a") { cin >> a; }
	else if (op == "b") { cin >> b; }
	else if (op == "saveb") {
		ostringstream con;//Numero para salvar borda
		con << nameim;
		imwrite("borda" + con.str() + ".jpg", borda);
		nameim++;
	}
	else if (op == "saveim") {
		ostringstream con;//Numero para salvar imagem
		con << namebo;
		imwrite("imagen" + con.str() + ".jpg", img);
		namebo++;
	}
	else if (op == "pl") { cin >> y.first; } // primeira linha
	else if (op == "sl") { cin >> y.second; } // segunda linha
	else if (op == "pc") { cin >> x.first; } // primeria coluna
	else if (op == "sc") { cin >> x.second; } // segunda coluna
	else if (op == "calibta") { calibracao_tamanho(); }
	//else if (op == "calibim") { calibracao_imagem(); }
	else if (op == "px") { unidade_cm = false; }
	else if (op == "cm") { unidade_cm = true; }
	else if (op == "lay") { cin >> layout; }
	
	else {

		system("cls");
		cout << "Linha: " << img.rows << endl;
		cout << "Coluna: " << img.cols << endl;
		cout << "Primeira-Linha: " << y.first << endl;
		cout << "Segunda-Linha: " << y.second << endl;
		cout << "Primeira-Coluna: " << x.first << endl;
		cout << "Segunda-Coluna: " << x.second << endl << endl;
		cout << "a      --> Alterar A" << endl;
		cout << "b      --> Alterar B" << endl;
		cout << "saveb  --> Salvar borda" << endl;
		cout << "saveim --> Salvar imagem" << endl;
		cout << "pl --> Primeira Linha" << endl;
		cout << "sl --> Segunda  Linha" << endl;
		cout << "pc --> Primeira Coluna" << endl;
		cout << "sc --> Segunda Coluna" << endl << endl;
		cout << "px --> Unidade pixel" << endl;
		cout << "cm --> Unidade cm" << endl;
		cout << "lay --> Layout" << endl;
		cout << "calibta --> Calibrar tamanho" << endl;
		cout << "calibim --> Calibrar imagem" << endl;
		cout << "esc  --> Finalizar" << endl << endl;
	}
	anti_Bug();
}

void colocar_texto(int layout) {
	ostringstream tamanho;

	if (unidade_cm == false) { // if para unidade px
		un = "px";
		tamanho << tam[2];
	}
	else if (unidade_cm == true) { // if para unidade cm
		un = "cm";
		tamanho << (tam[2] * rel);
	}

	putText(img, tamanho.str() + un, { 0,475 }, CV_FONT_HERSHEY_SIMPLEX, 1, { 0,255,0 }, 3, cv::LINE_AA);
	rectangle(img, { x.first,y.first }, { x.second,y.second }, { 0,255,0 }, 2, cv::LINE_AA, 0);
		
		switch (layout) {		
		case 1:
			imshow("WebCam", img);
			imshow("WebCam_Gray", gray);
			cvDestroyWindow("Borda");
			cvDestroyWindow("Borda1");
			break;
		case 2:
			imshow("WebCam", img);
			imshow("Borda", borda);
			cvDestroyWindow("Borda1");
			cvDestroyWindow("WebCam_Gray");
			break;
		case 3:
			imshow("WebCam", img);
			imshow("Borda", borda);
			imshow("Borda1", borda1);
			cvDestroyWindow("WebCam_Gray");
			break;

		case 4:
			imshow("WebCam", img);
			imshow("WebCam_Gray", dif);
			cvDestroyWindow("Borda");
			cvDestroyWindow("Borda1");
			break;

		default:
			imshow("WebCam", img);
			cvDestroyWindow("WebCam_Gray");
			cvDestroyWindow("Borda1");
			cvDestroyWindow("Borda");
		break;
	
	}
	
	
	
}

void mouse_callback(int  event, int  x1, int  y1, int  flag, void *param)
{
	if (event == EVENT_LBUTTONDBLCLK && primeiro_retangulo)
	{
		cout << "(" << x1 << ", " << y1 << ")" << endl;
		y.first = y1;
		x.first = x1;
		primeiro_retangulo = !primeiro_retangulo;
	}
	else if (event == EVENT_LBUTTONDBLCLK && !primeiro_retangulo)
	{
		cout << "(" << x1 << ", " << y1 << ")" << endl;
		y.second = y1;
		x.second = x1;
		primeiro_retangulo = !primeiro_retangulo;
	}

	
	anti_Bug();
}

void getModel() {

	if (getTrackbarPos("Fundo", "Teste") == 1)
	{
		setTrackbarPos("Fundo", "Teste", 0);
		gray.copyTo(model);
		gray.copyTo(dif);
	}
}

void background_Sub() {

	getModel();

	for (int i = 0; i < img.rows ; i++)
	{
		for (int j = 0; j < img.cols; j++) {
			if (abs(gray.at<uchar>(i, j) - model.at<uchar>(i, j)) < nivelCinza)
			{
				dif.at<uchar>(i, j) = 0;
			}
			else
			{
				dif.at<uchar>(i, j) = gray.at<uchar>(i, j);
			}
		}


	}
	
}

void metodoNissin() {

	for (int y = 0; y < borda1.rows; y++) {
		for (int x = 0; x < borda1.cols; x++) {
			if (borda1.at<uchar>(y, x) == 255 && !primeiro_Ponto) { tam[0] = y; primeiro_Ponto = true; }
			else if (borda1.at<uchar>(y, x) == 255) { tam[1] = y; }
		}
	}//fim do For
	primeiro_Ponto = false;
	tam[2] = tam[1] - tam[0]; // diferença da posição inicial e final

}

void metodoNorma(){
	
	for (int i = 0; i <= borda1.rows; i++) {
		for (int j = 0; j <= borda1.cols; j++) {
			if (borda1.at<uchar>(i, j) == 255 && !primeiro_Ponto) {
				A.first = i;
				A.second = j;
				primeiro_Ponto = true;

			}
		}
	}
	primeiro_Ponto = false;

	for (int j = 0; j <= borda1.cols; j++) {
		for (int i = borda1.rows; i >= 0; i--) {
			if (borda1.at<uchar>(i, j) == 255 && !primeiro_Ponto) {
				B.first = i;
				B.second = j;
				primeiro_Ponto = true;

			}
		}
	}
	primeiro_Ponto = false;

    line(borda1, {B.second, B.first }, { A.second, A.first }, { 255,255,255 }, 2, cv::LINE_AA, 0);
	//rectangle(img, { (y.first+A.second) - 3, (x.first+A.first) - 3 }, { (y.second+A.second) + 3, (x.second+A.first) + 3 }, { 255,255,255 }, 2, cv::LINE_AA, 0);


}

int main(void) {
	//setup
	    namedWindow("WebCam");
		namedWindow("WebCam_Gray");
		namedWindow("Borda");
		namedWindow("Borda1");
		namedWindow("Teste");
		moveWindow("WebCam", 0, 0);
		moveWindow("Borda", 700, 0);
		moveWindow("WebCam_Gray", 700, 0);
		moveWindow("Borda1", 815, 100);
		
		cvCreateTrackbar("A", "Teste", 0, 500);
		cvCreateTrackbar("B", "Teste", 0, 500);
		cvCreateTrackbar("Fundo", "Teste", 0, 1);
		cvCreateTrackbar("Cinza", "Teste", 0, 50);

		setTrackbarPos("A", "Teste", 100);
		setTrackbarPos("B", "Teste", 100);
		setTrackbarPos("Fundo", "Teste", 1);
		setTrackbarPos("Cinza", "Teste", 25);

		y.first = 100; y.second = 450;
		x.first = 100; x.second = 450;
		a = 100;
		b = 100;

		cam.read(img);
		cvtColor(img, gray, COLOR_BGR2GRAY);// Transformando img em cinza
		Canny(gray, borda, a, b);
		anti_Bug();
		

		//loop
		while (true) {
		//_______________________________________________________________________________________________________________________________
		//Bloco da captura de imagem
			
			a = getTrackbarPos("A", "Teste");
			b = getTrackbarPos("B", "Teste");
			nivelCinza = getTrackbarPos("Cinza", "Teste");

			setMouseCallback("WebCam", mouse_callback);
			cam.read(img);
			cvtColor(img, gray, COLOR_BGR2GRAY);// Transformando img em cinza
			background_Sub();
			Canny(dif, borda, a, b); // Transformar img em borda com o método canny
			
			//metodoNissin();
			metodoNorma();

			colocar_texto(layout);
			if (_kbhit()) {configuracao();}
			char c = waitKey(30);
			if (c == 27) { break; }
		
		}//Fim do while
		
		destroyAllWindows();
		return 0;
	}//Fim da main