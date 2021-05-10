/************************************
* Dynamic Matrix Control - SISO Controller
*
* DMC.h
* DMC.cpp
*
* Author:				Miguel Gómez Gonzalez
* Property:				CVG-CAR-UPM
*
*
* Version:					1.0
*
* Creation Date:			29/07/2014
* Last Modification Date:	--
*
****************************************/


#include "control/DMC.h"  //Incluimos el objeto DMC

namespace CVG_BlockDiagram {

DMC::DMC(int T, int N, Mat su, double alfa){
    // It is advised to use the DMC(int idDrone, const string &stackPath_in) constructor.
    started=false;
    reference=0.0;
    feedback=0.0;
    output=0.0;
    enableAntiWindup(false, 0.0);
    enableMaxOutput(false, 0.0);

    setParam( T, N, su, alfa);
}

DMC::DMC(const string &configuration_yml_file_location)
{
    started=false;
    reference=0.0;
    feedback=0.0;
    output=0.0;

    setParam(configuration_yml_file_location);
}

DMC::~DMC(){
}
void DMC::setAlpha(double alpha){
    Mat ALPHA=Mat::eye(m,m,CV_64FC1);
    Mat I=Mat::eye(t,t,CV_64FC1);
    for (int i=0; i<m; i++)
        ALPHA.at<double>(i,i)=alpha;
    M=((A.t()*ALPHA*A+I).inv())*A.t()*ALPHA; //Matriz de mínimos cuadrados
}

double DMC::getOutput(){

    if (!started) {
        started = true;
        return output;
    }
    //Update free response
    L=Q1*L+Su*deltau.at<double>(0,0);
    //create reference vector and calculate non-measurable perturbance
    for(int i=0;i<m;i++){
        R.at<double>(i,0)=reference;
        w.at<double>(i,0)=feedback-L.at<double>(0,0);
    }
    //Obtain the future errors
    D=R-I2*L-w;
    //Get deltau with minimum square method
    deltau=M*D;  //M=(A'*alfa*A+lambda*I)\A'*alfa;

    //Output
    double output_km1 = output;
    output = output_km1 + deltau.at<double>(0,0);

    // Saturation
    if (saturation_enabled) {
        if (                 output > saturation_max) {
            // saturate
            output                 = saturation_max;
            deltau.at<double>(0,0) = output - output_km1;
            // std::cout << "Saturado max" << std::endl;
        }
        if (saturation_min > output                 ) {
            // saturate
            output                 = saturation_min;
            deltau.at<double>(0,0) = output - output_km1;
            // std::cout << "Saturado min" << std::endl;
        }
    }

    std::cout << "feedback:" << feedback << "\t L(1):" << L.at<double>(0,0) << "\t deltau:"<< deltau.at<double>(0,0) << "\t output:" << output << std::endl;
    return output;
}

void DMC::reset(){
    for(int i=0;i<n;i++) L.at<double>(i,0)=0.0;
    //for(int i=0;i<m;i++) w.at<double>(i,0)=0.0;
    for(int i=0;i<t;i++) deltau.at<double>(i,0)=0.0;
    started=false;
    output=0.0;
}

void DMC::enableMaxOutput(bool enable, double max) {
    enableMaxOutput( enable, -max, +max);
}

void DMC::enableMaxOutput(bool enable, double min, double max) {
    saturation_enabled = enable;
    saturation_min = min;
    saturation_max = max;
}

void DMC::printmatrices(){
    cout<<"El valor de L es"<<endl;
    cout<<L<<endl;
    cout<<"El valor de deltau es"<<endl;
    cout<<deltau<<endl;
}


void DMC::setParam(const string &configuration_yml_file_location)
{
    int T;
    int N;
    Mat su;
    double alfa;
    { // Read from file
        FileStorage fs2(configuration_yml_file_location, FileStorage::READ);
        fs2["T_control_horizon"]            >> T;
        fs2["su"]                           >> su;
        //    fs2["N"]                          >> N;
        N                                   =  su.size().height;
        fs2["alpha_response_time_parameter"] >> alfa;
        fs2.release();
    } //

    setParam( T, N, su, alfa);
}

void DMC::setParam(int T, int N, Mat su, double alfa){
    t=T;
    n=N;
    m=t+n; //Horizonte de predicción= horizonte de control + longitud respuesta escalón
    L=Mat::zeros(n,1,CV_64FC1); //Respuesta libre
    w=Mat::zeros(m,1,CV_64FC1); //Perturbación no medible
    deltau=Mat::zeros(t,1,CV_64FC1); //Incremento de la acción de control
    R=Mat::zeros(m,1,CV_64FC1); //Vector referencia
    D=Mat::zeros(m,1,CV_64FC1); //Error con respecto a la referencia
    Su=Mat::zeros(n,1,CV_64FC1);
    for(int i=0;i<n;i++)
        Su.at<double>(i,0)=su.at<double>(i,0);//Copio el vector respuesta escalón
    Saux=Mat::zeros(m,1,CV_64FC1); //Vector auxiliar para construir la matriz A
    for(int i=0; i<m; i++){
        if(i<n) Saux.at<double>(i,0)=Su.at<double>(i,0);
        else Saux.at<double>(i,0)=Su.at<double>(n-1,0);
    }

    A=Mat::zeros(m,t,CV_64FC1);  //Construcción de la matriz A
    for(int i=0; i<m; i++){
        for( int j=0; j<t; j++){
            if(j<=i)
                A.at<double>(i,j)=Saux.at<double>(i-j,0);
        }
    }

    Q1=Mat::zeros(n,n,CV_64FC1);  //Matriz Q1 que desplaza la respuesta libre
    for(int i=0;i<n-1; i++){
        for(int j=1;j<n;j++){
            if(i==j-1)
                Q1.at<double>(i,j)=1;
        }
    }
    Q1.at<double>(n-1,n-1)=1;

    I2=Mat::zeros(m,n,CV_64FC1);  //Matriz I2 que se emplea para calcular el error con respecto a la referencia
    for(int i=0;i<n-1; i++){
        for(int j=1;j<n;j++){
            if(i==j-1)
                I2.at<double>(i,j)=1;
        }
    }
    for(int i=n-2;i<m;i++)
        I2.at<double>(i,n-1)=1;

    //setAlpha(alfa); //Ponemos alfa=1 por defecto y creamos la matriz M
    Mat ALPHA=Mat::eye(m,m,CV_64FC1);
    Mat I=Mat::eye(t,t,CV_64FC1);
    for (int i=0; i<m; i++)
        ALPHA.at<double>(i,i)=alfa;
    M=((A.t()*ALPHA*A+I).inv())*A.t()*ALPHA;
}
} //namespace CVG_BlockDiagram


