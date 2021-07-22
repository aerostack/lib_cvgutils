%Prueba del DMC empleando un valor de la masa de m=2.112 gramos para
%generar las matrices, y modificando la masa del modelo

modelo
matricesDMC
modelo_quadrotor.solido.m=1.512;

%Simulacion con masa del modelo=1.512
sim('DMC_AltSpeedController',100);
h=figure;
plot(time,Vref,'r','LineWidth',2.0);
hold on
plot(time,Velocidad,'LineWidth',2.0);
u=U;

%Simulacion con masa del modelo=1.812
modelo_quadrotor.solido.m=modelo_quadrotor.solido.m+0.3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'g','LineWidth',2.0);
u1=U;

%Simulacion con masa del modelo=2.112
modelo_quadrotor.solido.m=modelo_quadrotor.solido.m+0.3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'k','LineWidth',2.0);
u2=U;

%Simulacion con masa del modelo=2.412
modelo_quadrotor.solido.m=modelo_quadrotor.solido.m+0.3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'y','LineWidth',2.0);
u3=U;

%Simulacion con masa del modelo=2.712
modelo_quadrotor.solido.m=modelo_quadrotor.solido.m+0.3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'c','LineWidth',2.0);
u4=U;

legend('Vref','V_m=1.512','V_m=1.812','V_m=2.112','V_m=2.412','V_m=2.712');
title('Salida variando la m del modelo');
xlabel('tiempo(s)');
ylabel('velocidad(m/s)');
saveas(h,'salida_variando_masa','fig');

h=figure;
plot(time,u,'LineWidth',2.0);
hold on;
plot(time,u1,'g','LineWidth',2.0);
plot(time,u2,'k','LineWidth',2.0);
plot(time,u3,'y','LineWidth',2.0);
plot(time,u4,'c','LineWidth',2.0);

legend('u_m=1.512','u_m=1.812','u_m=2.112','u_m=2.412','u_m=2.712');
title('Accion de control variando la m del modelo');
xlabel('tiempo(s)');
ylabel('Fuerza(N)');
saveas(h,'accion_variando_masa','fig');

%En estas simulaciones se estima la respuesta escalon del modelo con la
%masa igual a 2.112, que corresponde al peso del pelican sin bateria(1.654)
%mas el peso estimado de la bateria ligera(0.458). Si cambiamos el peso del
%modelo suponiendo que existe algun error en la medida, apreciamos en las
%graficas que el controlador es capaz de seguir la referencia sin mayor
%problema, a pesar de que, obviamente, funciona mejor cuando coinciden peso
%del modelo y peso empleado para obtener las matrices DMC


