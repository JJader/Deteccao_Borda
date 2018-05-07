
    lenna=imread('lenna.jpg')
    lenna_g=rgb2gray(lenna)
    lenna_e=edge(lenna_g,'prewitt',0.16)
    T1=imread('T1.jpg')   
    
    valor=1

    while(valor>=1)
        
        clc
        imshow(T1)

        valor = input("Entre com um valor: ")

        if valor==1 then
            imshow(lenna)
        end

        if valor==2 then
            imshow(lenna_g)
        end

        if valor ==3 then
            imshow(lenna_e)
        end
        
    sleep(3000)
    
    end
clc
clf('reset');
subplot(2,2,1);imshow(lenna);title('Imagem de entrada');
subplot(2,2,2);imshow(lenna_g);title('Imagem em tom cinza');
subplot(2,2,3);imshow(lenna_e);title('Borda da imagem');
