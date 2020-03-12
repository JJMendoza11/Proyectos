classdef MySignal<handle
   properties
       Name                  %Se castea Function_Syms a char
       Signal_Size = 1       %Tamaño de la señal
       Domain                %Puntos de n de la funcion
       Domain_Lenght         %Tamaño de n
       StartPoint            %Punto en el que inicia la señal
       EndPoint              %Punto en el que termina la señal
       Signal_Values         %Valores de la funcion
       Signal_Samples = 1    %Cuantas muestras se tomaran a la señal
       Increment = 1         %Como se haran los incrementos
       Trigono_Fourier       %Vector de la transformada
       Complex_Fourier       %Vector de la transformada compl
       Function_Syms         %Variable tipo syms
       All_Function_Data     %Matriz que concatena todos los resultados
       Real                  %Parte real de la transformada compl
       Imag                  %Parte imag de la transformada compl
       Mag                   %%magnitud de la transformada compl
       Angle                 %Fase de la trasformada compl
       m                     %Variables aux
       x                     %...
       n                     %..
       b                     %.
   end
   
   methods
       function obj = MySignal()
       end
       %Funcion donde se calcula los incrementos para que concuerde con el 
       %numero de samples.
       function CalculatedDomain(obj)
           obj.Signal_Size = obj.EndPoint - obj.StartPoint;
           if obj.Signal_Size >= obj.Signal_Samples
               obj.Signal_Samples = obj.Signal_Size;
               obj.Domain = [obj.StartPoint:1:obj.EndPoint];
           else
               obj.Increment = (obj.Signal_Size) / obj.Signal_Samples; %Le quiet un uno
               obj.Domain = [obj.StartPoint:obj.Increment:obj.EndPoint];
           end
           obj.Domain_Lenght = length(obj.Domain);
       end
       %Funcion de se ingresa el tamaño de toda tu funcion o vector
       function SetEndPoint(obj) 
         obj.EndPoint = input(strcat('En que punto termina la señal: '));
       end
       %Funcion donde se ingresa el punto en el que empieza la señal
       function SetStartPoint(obj)
           obj.StartPoint = input('En que punto inicia la señal: ');
       end
       %Funcion donde se guarda el numero de muestra que va a contener 
       %cada señal
       function SetNumofSamples(obj)
          obj. Signal_Samples = input('Cuantos puntos contendra la señal: ');
       end
       %Funcion donde se ingresa el valor que va a tener la señal en cada
       %punto.
       function SetSignalValues(obj)
           for u8i = 1 : obj.Signal_Size
               valor = input(strcat('Insertar el valor_',num2str(u8i),': '));
               obj.Signal_Values(u8i) = valor;
           end
           obj.Signal_Samples = obj.Signal_Size;
           obj.CalculatedDomain;
       end
       %Funcion que grafica la señal contra su dominio correspondiente.
       function plot(obj)
        plot(obj.Domain,obj.Signal_Values);
        grid;
       end
       %Funcion que define el flujo a seguir para conseguir una señal en
       %tiempo continuo
       function InitDisSignal(obj)
          obj.SetStartPoint;
           obj.SetEndPoint;
          obj.SetSignalValues;
       end
       %Funcion que define el flujo a seguir para conseguir una señal en
       %tiempo continuo
       function InitConSignal(obj)
          obj.SetStartPoint;
          obj.SetEndPoint;
          obj.SetNumofSamples;
          obj.CalculatedDomain;
          obj.SetSignalFun;
       end
       %Funcion para ingresar la funcion de la señal entrante
       function SetSignalFun (obj)
          y = menu('Forma de la funcion','mt+b','mt^n','sen(mt+b)','cos(mt+b)','me^(nt)');
          syms t
            switch y
                case 1
                    obj.m = input('Ingrese el valor de m: ');
                    obj.b = input('Ingrese el valor de b: ');
                    obj.Signal_Values = obj.m*obj.Domain+obj.b;
                    obj.Function_Syms = obj.m*t+obj.b;
                case 2
                    obj.m = input('Ingrese el valor de m: ');
                    obj.n = input('Ingrese el valor de n: ');
                    obj.Signal_Values = obj.m * obj.Domain.^obj.n;
                    obj.Function_Syms = obj.m*t^obj.n;
                case 3 
                     obj.m = input('Ingrese el valor de m: ');
                     obj.b = input('Ingrese el valor de b: ');
                     obj.Signal_Values  = sin(obj.m*obj.Domain+obj.b);
                     obj.Function_Syms = sin(obj.m*t+obj.b);
                case 4
                    obj.m = input('Ingrese el valor de m: ');
                     obj.b = input('Ingrese el valor de b: ');
                     obj.Signal_Values  = cos(obj.m*obj.Domain+obj.b);
                     obj.Function_Syms = cos(obj.m*t+obj.b);
                case 5
                    obj.m = input('Ingrese el valor de m: ');
                     obj.n = input('Ingrese el valor de n: ');
                     obj.Signal_Values = obj.m*exp(obj.n*obj.Domain);
                     obj.Function_Syms = obj.m+exp(obj.n*t);
%                 case 6
%                     Constante = input('Ingrese una constante: ');
%                     obj.Signal_Values = zeros(1,obj.Domain_Lenght) ;
%                     obj.Signal_Values(:) = Constante;
%                     obj.Function_Syms = Constante;
            end
            obj.All_Function_Data = obj.Signal_Values;
            %arrayfun() convierte syms a char
            obj.Name = arrayfun(@char, obj.Function_Syms, 'uniform', 0);
       end
       %Funcion que calcula las series de fourier tanto complejas como
       %trigonometrica. Recibe un parametro y dependiendo de parametro V
       %va hacer lo que grafica
       function Fourier(obj,V) 
           syms t k 
           Period = obj.Signal_Size; %obj.Signal_Size
           
           Half_Period = Period/2;
           serie_compleja = exp(i*2*pi*k*t*1/Period);
%          obj.Trigono_Fourier = zeros(1, obj.Domain_Lenght);
%          obj.Complex_Fourier = zeros(1, obj.Domain_Lenght);
           %Se calcula el valor de A0
           A0 = (2/obj.Signal_Size) * int(obj.Function_Syms,t);
           A0 = subs(A0,Half_Period) - subs(A0,-Half_Period); %-Hald_Period
           %Se integra la funcion con cos y sin respectivamente para 
           %Encontrar An y Bn
           An = (2/Period) * int(obj.Function_Syms*cos(2*pi*k*t/Period),t);
           Bn = (2/Period) * int(obj.Function_Syms*sin(2*pi*k*t/Period),t);
           %Se evalua la funcion desde -T/2 hasta T/2
           An = subs(An,t,Half_Period) - subs(An,t,-Half_Period); %-Hald_Period
           Bn = subs(Bn,t,Half_Period) - subs(Bn,t,-Half_Period); %-Hald_Period
           
           %Varaibles aux
           suma = 0;
           suma_comp = 0;
           aux = 1;
           
           %Se calcula el valor de cada punto desde k = 1 hasta k = 20.
           %Ademas t va de incrementos ya calculados para que no se repita
           %n veces en la serie.
           for u8j = obj.StartPoint + obj.Increment :obj.Increment:obj.EndPoint     %u8j = 0 :obj.Increment:obj.Signal_Size
               for u8i = 1:20
                   Cn = 1/2 * subs(An,k,u8i) + i * 1/2 * subs(Bn,k,u8i);
                   suma = subs(An,k,u8i)*cos(u8i*u8j)+subs(Bn,k,u8i)*sin(u8i*u8j)+suma;
                   suma_comp = Cn * subs(serie_compleja,[k t], [u8i u8j]) + suma_comp;
               end
               suma = suma + A0/2;
               position = int32(u8j*1/u8j)+aux
               obj.Trigono_Fourier(position) = suma;
               obj.Complex_Fourier(position) = suma_comp;
               suma = 0;
               suma_comp = 0;
               if u8j == 0
                   aux = aux;
               else
               aux = aux + 1;
               end
               u8j
           end
           
           %Se guarda las series Trigonometricas, real, imaginaria, 
           %magnitud y angulo.
           obj.Real = real(obj.Complex_Fourier);
           obj.Imag = imag(obj.Complex_Fourier);
           obj.Mag = abs(obj.Complex_Fourier);
           obj.Angle = angle(obj.Complex_Fourier);
           %Se concatenan todos los vecotres para acceder más facil a las
           %variables.
           obj.All_Function_Data = [obj.Signal_Values;
                                    obj.Trigono_Fourier(1:obj.Domain_Lenght);
                                    obj.Real(1:obj.Domain_Lenght);
                                    obj.Imag(1:obj.Domain_Lenght);
                                    obj.Mag(1:obj.Domain_Lenght);
                                    obj.Angle(1:obj.Domain_Lenght)];
           if(V == 1)
                figure
                plot(obj.Domain,obj.Trigono_Fourier);
                title([obj.Name 'Trigonometrica']);
                xlabel('n');
                ylabel('f(x)~');
                grid
           else
               %Grafica la magnitud
               figure
               plot(obj.Domain,obj.Mag);
               title([obj.Name 'Compleja']);
               xlabel('n');
               ylabel('Magnitud');
               grid
               
               %Grafica la fase
               figure
               plot(obj.Domain,obj.Angle);
               title([obj.Name 'Compleja']);
               xlabel('n');
               ylabel('Angle');
               grid
           end
           
       end
   end
end
