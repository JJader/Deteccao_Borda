#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <stdlib.h>
#include <conio.h>
#include <iostream>

using namespace std;
using namespace cv;

//Bloco das vari�veis
typedef	struct Tamanho
{
	int first, second;
} Tamanho;

Tamanho y, x;
VideoCapture cam(0);
Mat img, gray, modelo; // <img> matriz da imagem
Mat borda, borda1; // <img> matriz da borda
string un;

bool unidade_cm = false, primeiro_Ponto = false, primeiro_retangulo = true, wh = true;
int nameim = 0, namebo = 0; // <namebo> Nome da borda; <nameim> Nome da imagem;
int a, b, tam[3], layout = 3; // <a,b> Configura��o do filtro;  <tam> posi��o da borda
float rel = 0.0; // <rel> rela��o entre pixel/cm

//------------------------------------------------------------------------------------------------------------------------------------
//Bloco das fun�oes

void troca(int *primeiro, int *segundo) {
	int a;
	a = *primeiro;
	*primeiro = *segundo;
	*segundo = a;

}


void anti_Bug() {
	// fazendo a se��o da borda

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
	float objcm, pxl; // <objcm> tamanho do objeto para calibra��o;
	cout << "Insira o Tamanho do Objeto em cm" << endl;
	cin >> objcm;
	cout << "Insira o Tamanho do Objeto em pxl ou digite zero para automatizar" << endl;
	cin >> pxl;
	if (pxl == 0){ pxl = tam[2];}
	rel = objcm * (1.0) / pxl;
	unidade_cm = true;
	cout << "Relac�o prixel centimetro : " << rel << endl;
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
	else if (op == "abort") { wh = false; }
	
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
		cout << "abort  --> Finalizar" << endl << endl;
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
		
		y.first = 100; y.second = 450;
		x.first = 100; x.second = 450;
		a = 100;
		b = 100;

		cam.read(img);
		cvtColor(img, gray, COLOR_BGR2GRAY);// Transformando img em cinza
		Canny(gray, borda, a, b);
		anti_Bug();
		

		//loop
		while (wh) {
		//_______________________________________________________________________________________________________________________________
		//Bloco da captura de imagem
			cvCreateTrackbar("A", "Teste", &a, 500);
			cvCreateTrackbar("B", "Teste", &b, 500);
			
			setMouseCallback("WebCam", mouse_callback);
			cam.read(img);
			cvtColor(img, gray, COLOR_BGR2GRAY);// Transformando img em cinza
			Canny(gray, borda, a, b); // Transformar img em borda com o m�todo canny
			
	
			for (int y = 0; y < borda1.rows - 1; y++) {
				for (int x = 0; x < borda1.cols - 1; x++) {
					if (borda1.at<uchar>(y, x) == 255 && !primeiro_Ponto) { tam[0] = y; primeiro_Ponto = true; }
					else if (borda1.at<uchar>(y, x) == 255) { tam[1] = y; }
				}
			}//fim do For
			primeiro_Ponto = false;
			tam[2] = tam[1] - tam[0]; // diferen�a da posi��o inicial e final
			
			colocar_texto(layout);
			if (_kbhit()) {configuracao();}
			waitKey(25);
		
		}//Fim do while
		
		destroyAllWindows;
		return 0;
	}//Fim da main