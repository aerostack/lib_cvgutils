
%THRUST_MAX_VALUE = 32.0; % Maximo valor del thrust. Activar cuando se
%desee la accion de control en tanto por 1
THRUST_MAX_VALUE = 1.0;
alpha=1.0; % parametro que controla el tiempo de respuesta del DMC
Ts=0.1; % tiempo de muestreo

%Modelo del quadrotor tomado como un segundo orden 
kf=modelo_quadrotor.solido.Kf;
a=modelo_quadrotor.input.T*modelo_quadrotor.solido.m/(2*kf);
b=modelo_quadrotor.input.T+modelo_quadrotor.solido.m/(2*kf);
sis=c2d(tf([0 0 THRUST_MAX_VALUE/(2*kf)],[a b 1]),Ts,'zoh'); %definicion del sistema
[numsis densis]=tfdata(sis,'v');
Su=step(sis);
Su=Su(2:end); % vector respuesta al escalon 


n=length(Su); %longitud del vector respuesta al escalon
t=60; %horizonte de control
m=t+n; %horizonte de prediccion


Saux=[Su; ones(m-n,1)*Su(end)]; %vector auxiliar para construir la matriz A
A=zeros(m,t);
for i=1:t;
    A(i:end,i)=Saux(1:m-i+1); % construcción de la matriz A
end
Ap=ones(m,n-1)*Su(n);
for i=1:m;
    for j=i:n-1;
    Ap(i,j)=Su(n-j+i); %construcción de la matriz Ap
    end
end
I=eye(t,t);
Q1=zeros(n,n);
Q1(1:end-1,2:end)=eye(n-1,n-1);
Q1(end,end)=1;
I2=zeros(m,n);
I2(1:n-1,2:end)=eye(n-1,n-1);
I2(n:end,end)=1;

alfa=alpha;%parámetros alfa y lambda  
lambda=1;
alfa=alfa*eye(m,m);
lambda=lambda*eye(t,t);

M=(A'*alfa*A+lambda)\A'*alfa; %Matriz de minimos cuadrados