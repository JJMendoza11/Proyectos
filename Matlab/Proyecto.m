clear;
close all;
clc;
format long;
%Se crea un arreglo de la clase ConvF1F2
Senales=[ConvF1F2,ConvF1F2];
menu1 = menu('Convolucion', 'Timepo "continuo"', 'Tiempo discreto');
switch menu1
    case 1
        disp('Funcion 1');
        Senales(1).InitConSignal;
        clc
        disp('Funcion 2');
        Senales(2).InitConSignal();
    case 2
        disp('Funcion 1');
        Senales(1).InitDisSignal;
        clc
         disp('Funcion 2');
        Senales(2).InitDisSignal;
end

figure
Senales(1).plot
figure
Senales(2).plot

menu2 = menu('Operaciones', 'Convolucionar señales', 'Series de Fourier');
switch menu2
    case 1
        Senales.Convolu(0);
    case 2
        if(menu1 ==1)
            close all
            v = input('1. serie Trigonometrica o 2 Serie Compleja: ');
            Senales(1).Fourier(v);
            Senales(2).Fourier(v);
        else
            disp('No puedo calcular la Serie de Fourier sin una función'); 
        end
end
%Loop para mostrar conv: Norm,Trigo,Mag,Ang,Real,Imag
Loop = 1;
if(menu1==1 && menu2 ==2)
    while (Loop ==1)
        convolucionar = input('Desea convolucionar, Si = 1 No =0:  ');
        if convolucionar == 1
            close all;
            Senales.Convolu(1)
            Loop = input('Desesea hacer otra iteracion?');
        else
            Loop = 0;
        end
    end
end
    

