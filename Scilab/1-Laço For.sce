clc
clear
imagen = imread('C:\Users\JJader\Desktop\d.jpg'); // leitura da imagem
cinza = rgb2gray(imagen); // tratamento para cinza
borda = edge(cinza, 'prewitt');//tratamento da borda
//imshow(borda);

A = size(borda);//armazeno o tamanho da matriz em uma variável
l = A(1,1);// l = linha  que é o elemento a11 da matriZ A
c = A(1,2);// c = coluna que é o elemento a12 da matriz A

z =1; // faço meu z = 1 para que meu primeiro elemento armazene o primeiro true que ele achar
for x=1:1:l // for(int x =1; x<=L; x++){ trabalhando com as linhas x}
    for y=1:1:c //for(int y =1; y<=C; y++){trabalhando com as colunas y}
       if (borda(x,y) == %t && z == 1) then //vou analisando cada elemento
        tm(1,1) = x; // achou o primeiro true armazena em tm = tamanho
        z = 0; // isso ocorrerá apenas uma vez
elseif (borda(x,y) == %t) then // se não, se o elemento for true ele vai armazenando até chegar no último
    tm(1,2) = x;// e armazena esse valor na coluna 2 de tm;
end; 
end; 
end;
disp(tm); // mostra a matriz do primeiro true e do último true
