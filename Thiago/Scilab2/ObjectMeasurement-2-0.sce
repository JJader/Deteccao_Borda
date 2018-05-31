clc
clear
avicloseall();

n=camopen(0);
i=0;
tm1=0;
tm2=0;

sleep(2000);

obj=input("Insira a altura do objeto:");

while(i<50)

im=avireadframe(n);
im1=rgb2gray(im);
im2=edge(im1,'prewitt',0.4);
im3= [im2(100:380,200:440)];

a=size(im3);
l=a(1,1);
c=a(1,2);
z=1;

for x=100
    for y=1:1:c
        im2(x,y)=%t;
    end
end

for x=380
    for y=1:1:c
        im2(x,y)=%t;
    end
end

for y=100
    for x=1:1:l
        im2(x,y)=%t;
    end
end

for y=540
    for x=1:1:l
        im2(x,y)=%t;
    end
end

imshow(im2);

for x=1:1:l
    for y=1:1:c
        if(im3(x,y)==%t && z==1) then
            tm1=x;
            z=0
        elseif (im3(x,y)== %t) then
            tm2=x;
        end
    end
end

px=tm2-tm1;

printf("%d Pixels \n", px);

i=i+1;
end

pxl=input("Quantos pixels tem o objeto");

rel=obj/pxl;

i=0;

while(i<50)

im=avireadframe(n);
im1=rgb2gray(im);
im2=edge(im1,'prewitt',0.4);
im3= [im2(100:380,200:440)];

imshow(im2);

a=size(im3);
l=a(1,1);
c=a(1,2);
z=1;

for x=1:1:l
    for y=1:1:c
        if(im3(x,y)==%t && z==1) then
            tm1=x;
            z=0
        elseif (im3(x,y)== %t) then
            tm2=x;
        end
    end
end

px=(tm2-tm1)*rel;

printf("%d Tamanho em mm \n", px);

i=i+1;

end

avicloseall();
