
Vreferencia=1; %Referencia
Ts=0.1;  %tiempo de muestreo

%Modelo del quadrotor 
%     T=tau de los actuadores
%     m=masa del quadrotor
%     Kf=Kfriccion
modelo_quadrotor=struct('input',struct('T',0.3,'K',1,'c',1),'solido',struct('m',2.112,'g',9.81,'Kf',0.15,'Z',0));
P=modelo_quadrotor.solido.m*modelo_quadrotor.solido.g;