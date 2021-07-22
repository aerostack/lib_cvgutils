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

#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;


//Libreria opencv
 #include <opencv2/opencv.hpp>
 #include "opencv2/core/core.hpp"


#include "control/DMC.h"
#include <string>

#include "Timer.h"

int main(){

//    int drone_id(0);
//    std::string drone_stackpath_str("/home/jespestana/workspace/ros/quadrotor/stack");
//    CVG::MAV::AltSpeedController AltSpeedController( drone_id, drone_stackpath_str);

    int T;
    int N;
    Mat su;
    double alfa;
    Mat ym;
    Mat um;
    { // Read from file
    FileStorage fs2("dmc_altitude_controller_configuration.yml", FileStorage::READ);
    fs2["T_control_horizon"]             >> T;
    fs2["su"]                            >> su;
//    fs2["N"]                            >> N;
    N                                    = su.size().height;
    fs2["alpha_response_time_parameter"]  >> alfa;
    fs2["measured_output_2"]  >> ym;
    fs2["control_moves_2"]  >> um;
    fs2.release();
    } // ~FileStorage();
    std::cout << "su.size, height:" << su.size().height << " width:" << su.size().width << std::endl;

    CVG_BlockDiagram::DMC dmc(30,22,su,1);
    //Mat a=(Mat_<double>(1,1) <<1.3);
    //dmc.setParam(1,1,a,1);
    //dmc.setParam(30,22,su,1);
	dmc.setReference(1.0);

	double u[8];
	u[0]=dmc.getOutput();
    dmc.setFeedback(0.0);
    u[0]=dmc.getOutput();
	dmc.setFeedback(0.2864);
	u[1]=dmc.getOutput();
	dmc.setFeedback(0.5829);
	u[2]=dmc.getOutput();
	dmc.setFeedback(0.7976);
	u[3]=dmc.getOutput();
	dmc.setFeedback(0.9246);
	u[4]=dmc.getOutput();
	dmc.setFeedback(0.987);
	u[5]=dmc.getOutput();
	dmc.setFeedback(1.0108);
	u[6]=dmc.getOutput();
	dmc.setFeedback(1.0153);
	u[7]=dmc.getOutput();
	dmc.setFeedback(1.0124);

    cout<<"El valor de la acción de control es"<<endl;
    for(int i=0;i<8;i++)
        cout<<u[i]<<endl;

    dmc.reset();
    cout<<"reseteado correctamente"<<endl;

    double u2[101];
    for(int i=0;i<ym.size().height;i++){
        if (i==50) dmc.setReference(0.4);
        u2[i]=dmc.getOutput();
        dmc.setFeedback(ym.at<double>(i,0));
    }


	cout<<"El valor de la acción de control es"<<endl;
    for(int i=0;i<ym.size().height;i++)
        cout<<u2[i]<<endl;

    for(int i=0; i<51; i++){
        double d=u2[i]-um.at<double>(i,0);
        cout<<d<<endl;
    }
    Timer my_timer;
    my_timer.restart(false);
    for (int i=0; i<su.size().height; i++) {
        // Do calculations here
        dmc.setFeedback( su.at<double>(i,0) );
        u[0]=dmc.getOutput();
        //std::cout << " su[i]:" << su.at<double>(i,0) << std::endl;

        double elapsed_seconds = my_timer.getElapsedSeconds();
        my_timer.restart(true);
        std::cout << " elapsed_seconds:" << elapsed_seconds << std::endl;
    }

    return 0;
}
