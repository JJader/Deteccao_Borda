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
struct COOR{
	int i;
	int j;
};

//Criação de uma variável do tipo ROI (Regiao de interesse) de tamanho 2 (início e fim)
struct ROI roi[2];

//Função para selecionar o ROI (Regiao de iteresse) a partir do click na tela
//Auxiliar 3 para comutar entre coordenadas inicial e final
void mouse_callback(int event, int x, int y, int flag, void *param) {
	if ((event == EVENT_LBUTTONDBLCLK) && (aux[3]==0)) {
		cout << "(" << x << ", " << y << ")" << endl;
		roi[0].col = x;
		roi[0].row = y;
		aux[3] = 1;
	} else if ((event == EVENT_LBUTTONDBLCLK) && (aux[3] == 1)) {
		cout << "(" << x << ", " << y << ")" << endl;
		roi[1].col = x;
		roi[1].row = y;
		aux[3] = 0;
	}
}

int main(void) {

	struct LIM lim; //Variavel lim do tipo LIM para limiarização Canny
	struct COOR coor[4]; //Vetor coor de tamanho 4 para encontrar quatro pontos na imagem (em teste)
	Mat img; //A imagem lida da WebCam é armazenada nessa matriz
	Mat	model; //Uma primeira imagem do cenário é salva nessa matriz para fins de subtração (Background Subtraction)
	Mat	dif; //Nessa matriz sera armazenada a diferença entre a Matriz model e a Matriz img
	Mat gray; //Matriz para armazenar a transformação para escalas de cinza
	Mat channel[3]; //Matrizes para armazenar as três bandas (Red, blue, Green)
	Mat borda; //Matriz para armazenar a borda
		
	//Solicita ao usuário no início do programa a inserção dos limiares (Canny) // Necessário fazer controle dinâmico (a qualquer momento)
	cout << "Insira o limiar inferior (a)" << endl;
	cin >> lim.inf;
	cout << "Insira o limiar superior (b)" << endl;
	cin >> lim.sup;

	VideoCapture cam(0); // Ativa webcam
	cam.read(model); // Salva imagem modelo

	//Loop infinito
	while (true) {

	setMouseCallback("imColor", mouse_callback); // Definição do ROI
	cam.read(img); // Leitura da imagem em modo Vivo

	dif = abs(model-img); // A matriz dif recebe a diferença entre o modelo e o Ao Vivo

	cvtColor(dif, gray, COLOR_BGR2GRAY); // Conversão matriz DIF para escala de cinzas
	Canny(gray, borda, lim.inf, lim.sup); // Conversão da matriz GRAY para bordas pelo método Canny

	flip(img, img, +1); // Inverte a imagem (epelhar)
	flip(borda, borda, +1); // Inverte a imagem (epelhar)

	waitKey(50); // Pequeno delay

	rectangle(img, {roi[0].col, roi[0].row, }, { roi[1].col ,roi[1].row }, { 0,255,0 }, 2, cv::LINE_AA, 0); // Insere na tela o retângulo referente ao ROI

	namedWindow("imColor"); // Cria janela para impressão da imagem colorida
	namedWindow("imBorda"); // Cria janela para impressão da imagem de bordas

	
	// For que lê de cima para baixo, todas as colunas da esquerda para a direita
	// Utilizado Auxiliar 1 para encerrar busca
	for (int i = roi[0].row; i <= roi[1].row; i++) {
		for (int j = roi[0].col; j <= roi[1].col; j++) {
			if ((borda.at<uchar>(i,j) == 255)&&(aux[1]==0)) {
				coor[0].i = i;
				coor[0].j = j;
				aux[1] = 1;
				rectangle(img, { coor[0].j - 3 ,coor[0].i - 3 }, { coor[0].j + 3 ,coor[0].i + 3 }, { 255,0,0 }, 2, cv::LINE_AA, 0); // Imprime na tela um retangulo nas coordenadas do ponto encontrado
			}
		}
	}

	// For que lê da esquerda para a direita todas as linhas de cima para baixo
	// Utilizado Auxiliar 2 para encerrar busca
	for (int j = roi[0].col ; j <= roi[1].col; j++) {
		for (int i = roi[0].row; i <= roi[1].row; i++) {
			if ((borda.at<uchar>(i, j) == 255) && (aux[2] == 0)) {
				coor[1].i = i;
				coor[1].j = j;
				aux[2] = 1;
				rectangle(img, { coor[1].j - 3 ,coor[1].i - 3 }, { coor[1].j + 3 ,coor[1].i + 3 }, { 0,255,0 }, 2, cv::LINE_AA, 0); // Imprime na tela um retangulo nas coordenadas do ponto encontrado
			}
		}
	}
	
	// For que lê da direita para a esquerda todas as linhas de cima para baixo
	// Utilizado Auxiliar 4 para encerrar busca
	for (int j = roi[1].col; j >= roi[0].col; j--) {
		for (int i = roi[0].row; i <= roi[1].row; i++) {
			if ((borda.at<uchar>(i, j) == 255) && (aux[4] == 0)) {
				coor[2].i = i;
				coor[2].j = j;
				aux[4] = 1;
				rectangle(img, { coor[2].j - 3 ,coor[2].i - 3 }, { coor[2].j + 3 ,coor[2].i + 3 }, { 0,0,255 }, 2, cv::LINE_AA, 0); // Imprime na tela um retangulo nas coordenadas do ponto encontrado
			}
		}
	}

	// For que lê de baixo para cima, todas as colunas da direita para a esquerda
	// Utilizado Auxiliar 6 para encerrar busca
	for (int i = roi[1].row; i >= roi[0].row; i--) {
		for (int j = roi[1].col; j >= roi[0].col; j--) {
			if ((borda.at<uchar>(i, j) == 255) && (aux[6] == 0)) {
				coor[3].i = i;
				coor[3].j = j;
				aux[6] = 1;
				rectangle(img, { coor[3].j - 3 ,coor[3]. i- 3 }, { coor[3].j + 3 ,coor[3].i + 3 }, { 50,50,50 }, 2, cv::LINE_AA, 0); // Imprime na tela um retangulo nas coordenadas do ponto encontrado
			}
		}
	}

	// Impressão na tela de uma linha que liga os pontos encontrados
	line(img, { coor[0].j ,coor[0].i }, { coor[2].j ,coor[2].i }, { 255,0,0 }, 2, cv::LINE_AA, 0); //blue
	line(img, { coor[2].j ,coor[2].i }, { coor[3].j ,coor[3].i }, { 0,255,0 }, 2, cv::LINE_AA, 0); //green
	line(img, { coor[3].j ,coor[3].i }, { coor[1].j ,coor[1].i }, { 0,0,255 }, 2, cv::LINE_AA, 0); //red
	line(img, { coor[1].j ,coor[1].i }, { coor[0].j ,coor[0].i }, { 100,100,100 }, 2, cv::LINE_AA, 0);
	
	//Zera os auxiliares
	aux[1] = 0;
	aux[2] = 0;
	aux[4] = 0;
	aux[6] = 0;

	//putText(img, "Peoes", { pc-50,pl}, CV_FONT_HERSHEY_SIMPLEX, 2, { 255,0,0 }, 2, cv::LINE_AA, 0);
	
	// Imprime tela
	imshow("imColor", img);
	imshow("imBorda", borda);
	
	}

	waitKey(0);
	return 0;

}

/*
//Essa funcao pode ser usada para subtrair canais RGB, no exemplo abaixo o canal Red é excluido
img -= Scalar(255, 255, 0);
*/

/*
//Funcao para dividir a imagem em 3 canais
split(img, channel); // Dividir canais
channel[0] = Mat::zeros(img.rows, img.cols, CV_8UC1); // Zerar canal blue
channel[1] = Mat::zeros(img.rows, img.cols, CV_8UC1); // Zerar canal green
channel[2] = Mat::zeros(img.rows, img.cols, CV_8UC1); // Zerar canal red
merge(channel, 3, img); // Mesclar os canais resultantes
*/