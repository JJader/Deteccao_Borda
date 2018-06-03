#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <conio.h>


using namespace std;
using namespace cv;






int main(void) {
//_______________________________________________________________________________________________________________________________
//Bloco das variáveis

int a, b, aux1 = 1, aux2 = 1, aux3 = 1; // <a,b> Configuração do filtro; <aux1> While; <aux2>; <aux3> Save da imagem
int name = 0, nome = 0, tam[3]; // <name> Nome da borda; <nome> Nome da imagem; <tam> posição da borda
int col, row; // <col> Coluna da borda; <row> linha da borda
int pc = 100, pl = 50, sc = 540, sl = 430;
string op; // <op> String tratada pelo if
Mat img; // <img> matriz da imagem
Mat borda; // <img> matriz da borda
VideoCapture cam(0);
namedWindow("WebCam");
namedWindow("Borda");
a = 100;
b = 100;
//_______________________________________________________________________________________________________________________________
//Bloco da captura de imagem

while (aux1 == 1) {

	cam.read(img);
	Canny(img, borda, a, b); // Transformar img em borda com o método canny
//______________________________________________________________________________________________________________________________
//Bloco para encontrar o tamanho da imagem 
	col = borda.cols;
	row = borda.rows;
	for (int y = 0; y < col; y++) {
		for (int x = 0; x < row; x++) {
			if (borda.at<uchar>(x, y) == 255 && aux3 == 1) { tam[0] = y;	aux3++; }
			else if (borda.at<uchar>(x, y) == 255) { tam[1] = y; }
			//printf("%d ", (borda.at<uchar>(x, y)));
		}
			//printf(";\n");
		}//fim do For

	tam[2] = tam[1] - tam[0];
	ostringstream tamanho; //Transformando int em string
	tamanho << tam[2];
//______________________________________________________________________________________________________________________________
//Bloco paraTratamento da tela

	putText(img, tamanho.str(), { 0,475 }, CV_FONT_HERSHEY_SIMPLEX, 1, { 0,255,0 }, 3, cv::LINE_AA);
	rectangle(img, { 100,50 }, { 540,430 }, { 0,255,0 }, 2, cv::LINE_AA, 0);
	imshow("WebCam", img);
	imshow("Borda", borda);
	waitKey(25);
//_______________________________________________________________________________________________________________________________
//Bloco dos IFs

	if (_kbhit()) {
		cin >> op;
		if (op == "a") { cin >> a; }
		else if (op == "b") { cin >> b; }
		else if (op == "abort") { aux1 += 1; }
		else if (op == "saveb") {
			ostringstream con;//Transformando int em string
			con << name;
			imwrite("borda" + con.str() + ".jpg", borda);
			name++;	}
		else if (op == "saveim") {
			ostringstream con;//Transformando int em string
			con << nome;
			imwrite("imagen" + con.str() + ".jpg", img);
			nome++;	}
		else {
			system("cls");
			cout << "a      --> Alterar A" << endl;
			cout << "b      --> Alterar B" << endl;
			cout << "saveb  --> Salvar borda" << endl;
			cout << "saveim --> Salvar imagem" << endl;
			cout << "abort  --> Finalizar" << endl << endl;	}
	}//Fim do IF
}//Fim do while

//_______________________________________________________________________________________________________________________________
//Finalização
system("pause");
return 0;
}//Fim da main