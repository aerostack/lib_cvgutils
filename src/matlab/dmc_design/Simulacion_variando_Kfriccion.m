%Prueba del DMC variando la Kf del modelo, y empleando una Kf de 0.15 para
%la simulacion y creacción de las matrices del DMC

modelo
matricesDMC
modelo_quadrotor.solido.Kf=modelo_quadrotor.solido.Kf/9;

%Simulacion con Kf=0.1/9;
sim('DMC_AltSpeedController',100);
h=figure;
plot(time,Vref,'r','LineWidth',2.0);
hold on
plot(time,Velocidad,'m','LineWidth',2.0);
u5=U;

%Simulacion con Kf=0.1/3;
modelo_quadrotor.solido.Kf=modelo_quadrotor.solido.Kf*3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'k','LineWidth',2.0);
u6=U;

%Simulacion con Kf=0.1;
modelo_quadrotor.solido.Kf=modelo_quadrotor.solido.Kf*3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'LineWidth',2.0);
u=U;

%Simulacion con Kf=0.3;
modelo_quadrotor.solido.Kf=modelo_quadrotor.solido.Kf*3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'g','LineWidth',2.0);
u1=U;

%Simulacion con Kf=0.9;
modelo_quadrotor.solido.Kf=modelo_quadrotor.solido.Kf*3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'y','LineWidth',2.0);
u2=U;

%Simulacion con Kf=2.7;
modelo_quadrotor.solido.Kf=modelo_quadrotor.solido.Kf*3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'k','LineWidth',2.0);
u3=U;

%Simulacion con Kf=8.1;
modelo_quadrotor.solido.Kf=modelo_quadrotor.solido.Kf*3;
sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'c','LineWidth',2.0);
u4=U;

legend('Vref','V_k_f=0.1/9','V_k_f=0.1/3','V_k_f=0.1','V_k_f=0.3','V_k_f=0.9','V_k_f=2.7','V_k_f=8.1');
title('Salida variando la Kf del modelo');
xlabel('tiempo(s)');
ylabel('velocidad(m/s)');
saveas(h,'salida_variando_Kf','fig');

h=figure;
plot(time,u5,'m','LineWidth',2.0);
hold on;
plot(time,u6,'k','LineWidth',2.0);
plot(time,u,'LineWidth',2.0);
plot(time,u1,'g','LineWidth',2.0);
plot(time,u2,'y','LineWidth',2.0);
plot(time,u3,'k','LineWidth',2.0);
plot(time,u4,'c','LineWidth',2.0);
legend('u_k_f=0.1/9','u_k_f=0.1/3','u_k_f=0.1','u_k_f=0.3','u_k_f=0.9','u_k_f=2.7','u_k_f=8.1');
title('Accion de control variando Kf del modelo');
xlabel('tiempo(s)');
ylabel('Fuerza(N)');
saveas(h,'accion_variando_Kf','fig');

%Tomando como referencia para la creaccion de todas las matrices que
%necesita el DMC a partir de la respuesta escalon el modelo con una
%constante de fricción igual a 0.1, se va modificando de forma geometrica
%el valor de dicha constante en el modelo, simulando que nuestro modelado
%no es exactamente como el de la realidad para apreciar lo que sucede en
%este caso.

%Al disminuir la Kf, el sistema simplemente supera la referencia pero no lo
%hace en exceso, y tiende a recuperarse y seguir a la misma con rapidez.
%Sin embargo, al aumentar la Kf en exceso, el sistema responde con una
%accion de control inferior a la demandada, y por tanto el sistema no
%alcanza la referencia en un instante inicial, y le lleva mas tiempo al
%controlador corregirlo. De todas formas cabe destacar que la Kf la hemos
%incrementado de forma geometrica, y esto puede darnos Kf demasiado grandes
%y alejadas de la realidad, ya que estimamos que la Kf real estará en torno
%a 0.1 o 0.2 N/m^2