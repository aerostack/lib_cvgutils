%Prueba del DMC variando alfa, parametro que controla el tiempo de
%respuesta

modelo
matricesDMC

sim('DMC_AltSpeedController',100);
h=figure;
plot(time,Vref,'r','LineWidth',2.0);
hold on
plot(time,Velocidad,'LineWidth',2.0);
u=U;

alpha=alpha/3;
script_matrices

sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'g','LineWidth',2.0);
u1=U;

alpha=alpha/3;
script_matrices

sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'y','LineWidth',2.0);
u2=U;

alpha=alpha/3;
script_matrices

sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'k','LineWidth',2.0);
u3=U;

alpha=alpha/3;
script_matrices

sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'c','LineWidth',2.0);
u4=U;
title('salida');
xlabel('tiempo(s)');
ylabel('velocidad(m/s)');
legend('Vref','alfa=1','alfa=1/3','alfa=1/9','alfa=1/27','alfa=1/81');
saveas(h,'salida_decrementando_alfa','fig');

h=figure;
plot(time,u,'LineWidth',2.0);
hold on
plot(time,u1,'g','LineWidth',2.0);
plot(time,u2,'y','LineWidth',2.0);
plot(time,u3,'k','LineWidth',2.0);
plot(time,u4,'c','LineWidth',2.0);
legend('alfa=1','alfa=1/3','alfa=1/9','alfa=1/27','alfa=1/81');
title('acciones de control');
xlabel('tiempo(s)');
ylabel('Fuerza(N)');
saveas(h,'accion_decrementando_alfa','fig');

%La accion de control se suaviza al disminuir el valor del
%parametro alfa

modelo
matricesDMC

sim('DMC_AltSpeedController',100);
h=figure;
plot(time,Vref,'r','LineWidth',2.0);
hold on
plot(time,Velocidad,'LineWidth',2.0);
u=U;

alpha=alpha*3;
script_matrices

sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'g','LineWidth',2.0);
u1=U;

alpha=alpha*3;
script_matrices

sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'y','LineWidth',2.0);
u2=U;

alpha=alpha*3;
script_matrices

sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'k','LineWidth',2.0);
u3=U;

alpha=alpha*3;
script_matrices

sim('DMC_AltSpeedController',100);
plot(time,Velocidad,'c','LineWidth',2.0);
u4=U;
title('salida');
xlabel('tiempo(s)');
ylabel('velocidad(m/s)');
legend('Vref','alfa=1','alfa=3','alfa=9','alfa=27','alfa=81');
saveas(h,'salida_incrementando_alfa','fig');

h=figure;
plot(time,u,'LineWidth',2.0);
hold on
plot(time,u1,'g','LineWidth',2.0);
plot(time,u2,'y','LineWidth',2.0);
plot(time,u3,'k','LineWidth',2.0);
plot(time,u4,'c','LineWidth',2.0);
legend('alfa=1','alfa=3','alfa=9','alfa=27','alfa=81');
title('acciones de control');
xlabel('tiempo(s)');
ylabel('Fuerza(N)');
saveas(h,'accion_incrementando_alfa','fig');

%Conclusiones de la simulacion: variar el parámetro alfa nos permite
%influir en el tiempo de respuesta de nuestro sistema a costa de pedirte
%una accion de control mayor. Esto se debe a que el parametro alfa pondera
%el error entre referencia y salida, y por tanto exigira una accion de
%control mayor cuanto mayor sea dicho parámetro

%No obstante, cabe destacar que al disminuir el tiempo de respuesta aumenta
%la sobreoscilacion del sistema y la carga en los actuadores de las
%acciones de control, ya que se demanda un cambio mas brusco en los
%actuadores
