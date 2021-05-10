% THRUST_MAX_VALUE: askldasjldasjl
% input:
%   T:
%   ...

THRUST_MAX_VALUE = 32.00; % N

%Asignaci�n de valores al modelo del quadrotor
modelo_quadrotor = struct('input',struct('T', 0.3,'K',1,'c',1), ...
                          'solido',struct('m',2.110,'g',9.81,'Kf',0.1,'Z',0), ...
                          'filtro',struct('Kfil',1,'t',0.5));

% Ts=1/60; %El tiempo de muestreo para obtener el vector de respuesta escal�n. En este caso la frecuencia de muestreo son 60 Hz
Ts=0.1;
kf=modelo_quadrotor.solido.Kf;
a=modelo_quadrotor.input.T*modelo_quadrotor.solido.m/(2*kf); %coeficiente de s^2
b=modelo_quadrotor.input.T+modelo_quadrotor.solido.m/(2*kf); %coeficiente de s
sis=c2d(tf([0 0 THRUST_MAX_VALUE/(2*kf)],[a b 1]),Ts,'zoh'); %definici�n del sistema considerado como segundo orden
[numsis densis]=tfdata(sis,'v');
Su=step(sis);

Su=Su(2:end)'; %vector de respuesta escal�n. Corresponde a la matriz que se debe introducir en el archivo de configuraci�n del dmc
n=length(Su); %longitud del vector respuesta al escalon. Puede incluirse en el archivo de configuraci�n, aunque se recomienda obtener este valor a partir de la longitud de Su
t=60; %horizonte de control. El horizonte de control puede tomar valores entre 40 y 80.
