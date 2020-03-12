classdef ConvF1F2<MySignal
    properties 
        Normal_Signal = 1;           %Macro para acceder a los valores originales
        Fourier_Tri = 2;             %Macro para acceder a los valores serie trigonometrica       
        Fourier_Real = 3;            %Macro para acceder a la parte real
        Fourier_Imag = 4;            %Macro para acceder a la parte imag
        Fourier_Mag = 5;             %Macro para acceder a la magnitud
        Fourier_Angle = 6;           %Macro para acceder a la fase
        n_Elements                   %Calcula el dominio de la fx resultante
        Conv                         %Vector resultante de conv
        Columna                      %Columna a acceder
    end
    methods
        function fs = ConvF1F2()
        end
        %Funcion que recibe dos funciones para convolucionar
        function Convolu(fs,Vector)
            %Se calcula el dominio de la funcion resultante
            if fs(1).StartPoint < fs(2).StartPoint
               Conv_LowPoint = fs(1).StartPoint;
               Conv_HighPoint = fs(1).Signal_Size + fs(2).Signal_Size+ fs(1).StartPoint-1;
            else
               Conv_LowPoint = fs(2).StartPoint;
               Conv_HighPoint = fs(1).Signal_Size + fs(2).Signal_Size+ fs(2).StartPoint-1;
            end
            ConvSize = fs(1).Domain_Lenght + fs(2).Domain_Lenght - 1;
            Conv_Increments = ((Conv_HighPoint - Conv_LowPoint)/(ConvSize-1));
            fs(1).n_Elements = Conv_LowPoint:Conv_Increments:Conv_HighPoint;
            fs(1).Conv = zeros(1,ConvSize);
            suma = 0;
            disp('1. fx * fx2'); 
            disp('2. fx2 * fx1'); 
            x = input('Ingrese 1 ó 2: ');
            y = 1;
            if x==1
                y = 2;
            end
            aux = 1;
            if(Vector == 1)
            menuConv = menu('Opciones a convolucionar', 'Funcion normal','Serie Trigonometrica', 'Parte real', 'Parte Imaginaria', 'Magnitud', 'Fase');
                switch menuConv
                    case 1
                        aux = fs(1).Normal_Signal;
                        Titulo = 'Convolucion';
                        ejey = 'f1*f2';
                    case 2
                        aux = fs(1).Fourier_Tri;
                        Titulo = 'Convolucion Trigono';
                        ejey = 'F1*F2';
                    case 3 
                        aux = fs(1).Fourier_Real;
                        Titulo = 'Convolucion Real';
                        ejey = 'Real';
                    case 4
                        aux = fs(1).Fourier_Imag;
                        Titulo = 'Convolucion Imag';
                        ejey = 'Imag';
                    case 5
                        aux = fs(1).Fourier_Mag;
                         Titulo = 'Convolucion Mag';
                         ejey = 'Magnitud';
                    case 6
                        aux = fs(1).Fourier_Angle;
                         Titulo = 'Convolucion Angulo';
                         ejey = 'Fase';
                end
            end
            for i = 1 : ConvSize
                for j = 1 : fs(x).Domain_Lenght
                    if(i-j>=0 && i-j < fs(x).Domain_Lenght && i-j < fs(y).Domain_Lenght)              
                        suma = suma + fs(x).All_Function_Data(aux,j) * fs(y).All_Function_Data(aux,i-j+1);
                    end
                end
                fs.Conv(1,i) = suma;
                suma = 0;
            end
            %Grafica la informacion seleccionada por el usuario
            figure
            plot(fs(1).n_Elements,fs(1).Conv);
            title(Titulo);
            ylabel(ejey);
            xlabel('n');
            grid
        end
    end
end