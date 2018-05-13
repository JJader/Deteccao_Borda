//Developed by Miojo and Thiago
//1 Periodo Eng Computacao UFOP - ICEA


clc
clear
avicloseall();

n=camopen(0);
i=0;
sleep(2000);

while(i<100)


im=avireadframe(n);
im1=rgb2gray(im);
im2=edge(im1,'prewitt',0.3);

imshow(im2);

a=size(im2);
l=a(1,1);
c=a(1,2);
z=1;

for x=1:1:l
    for y=1:1:c
        if(im2(x,y)==%t && z==1) then
            tm1=x;
            z=0
        elseif (im2(x,y)== %t) then
            tm2=x;
        end
    end
end

//im3=[im,im2];

disp((tm2-tm1)*0.07714);

//imshow(im3);

i=i+1;
end

avicloseall();

