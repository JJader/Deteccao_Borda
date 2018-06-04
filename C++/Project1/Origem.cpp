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

int aux1 = 1, aux2 = 1, aux3 = 1, aux4 = 1; 
// <aux1> While; <aux2> Troca do maior; <aux3> Save da imagem; <aux4> Calibração (0 calibra,1 px, 2 cm)
int a, b, name = 0, nome = 0, tam[3];
// <a,b> Configuração do filtro; <name> Nome da borda; <nome> Nome da imagem; <tam> posição da borda
int col, row, col1, row1; 
// <col> Coluna da img; <row> linha da img; <col1> Coluna da seção da borda; <row> linha da seção da borda
int pc = 100, pl = 100, sc = 440, sl = 430; // primeira coluna e linha, segunda coluna e linha
float rel = 0; // <rel> relação entre pixel/cm
int objcm, pxl; // <objcm> tamanho do objeto para calibração;
string op,un; // <op> String tratada pelo if; <un> Unidade da medição;
Mat img; // <img> matriz da imagem
Mat borda; // <img> matriz da borda
VideoCapture cam(0);
namedWindow("WebCam");
namedWindow("Borda");
namedWindow("Borda1");
a = 100;
b = 100;
//_______________________________________________________________________________________________________________________________
//Bloco da captura de imagem

while (aux1 == 1) {

	cam.read(img);
	Canny(img, borda, a, b); // Transformar img em borda com o método canny

//______________________________________________________________________________________________________________________________
//Bloco para encontrar o tamanho da imagem 
	col = img.cols;
	row = img.rows;
	
	if (pl>sl)
	{
		aux2 = pl;
		pl = sl;
		sl = aux2;
		aux2 = 1;
	}
	if(pc>sc)
	{
		aux2 = pc;
		pc = sc;
		sc = aux2;
		aux2 = 1;
	}
	Mat borda1(borda, Rect(pc, pl, (sc - pc), (sl - pl))); // fazendo a seção da borda
	col1 = borda1.cols;
	row1 = borda1.rows;

	for (int y = 0; y <= row1; y++) {
		for (int x = 0; x <= col1; x++) {
			if (borda1.at<uchar>(y, x) == 255 && aux3 == 1) { tam[0] = y; aux3++; }
			else if (borda1.at<uchar>(y, x) == 255) { tam[1] = y; }
			//printf("%d ", (borda.at<uchar>(x, y)));
		}
			//printf(";\n");
		}//fim do For
	aux3 = 1;

	if (aux4 == 0) { // if para calibração 
		cout << "Insira o Tamanho do Objeto em cm" << endl;
		cin >> objcm;
		cout << "Insira o Tamanho do Objeto em pxl" << endl;
		cin >> pxl;
		rel = objcm*(1.0) / pxl;
		aux4 = 2;
		cout << rel << endl;
	}

	tam[2] = tam[1] - tam[0];
	ostringstream tamanho; //Transformando int em string

	if (aux4 == 1) {
		un = "px";
		tamanho << tam[2];
	}
	else if (aux4 == 2) {
		un = "cm";
		tamanho << (tam[2]*rel);
	}

	//______________________________________________________________________________________________________________________________
//Bloco para Tratamento da tela

	putText(img, tamanho.str() + un, { 0,475 }, CV_FONT_HERSHEY_SIMPLEX, 1, { 0,255,0 }, 3, cv::LINE_AA);
	rectangle(img, { pc,pl }, { sc,sl}, { 0,255,0 }, 2, cv::LINE_AA, 0);
	imshow("WebCam", img);
	imshow("Borda", borda);
	imshow("Borda1", borda1);
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
		else if (op == "pl") { cin >> pl; }
		else if (op == "sl") { cin >> sl; }
		else if (op == "pc") { cin >> pc; }
		else if (op == "sc") { cin >> sc; }
		else if (op == "calib") { aux4 = 0; }
		else if (op == "px") { aux4 = 1; }
		else if (op == "cm") { aux4 = 2; }

		else {
			
			system("cls");
			cout << "Linha: " << row << endl;
			cout << "Coluna: " << col << endl;
			cout << "Primeira-Linha: " << pl << endl;
			cout << "Segunda-Linha: " << sl << endl;
			cout << "Primeira-Coluna: " << pc << endl;
			cout << "Segunda-Coluna: " << sc << endl <<endl;

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
			cout << "calib --> Calibrar" << endl;
			cout << "abort  --> Finalizar" << endl << endl;	}
			
	}//Fim do IF
}//Fim do while

//_______________________________________________________________________________________________________________________________
//Finalização
system("pause");
return 0;
}//Fim da main