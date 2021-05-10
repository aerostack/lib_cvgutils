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

#ifndef DMC_H_
#define DMC_H_

//Libreria opencv
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"


using namespace cv;
using namespace std;

namespace CVG_BlockDiagram {

class DMC{
 private:
    // On/Off
    bool started;
    // Input/Output
    double reference;
	double feedback;
	double output;
	
	//Internal parameters
	Mat L;
	Mat w;
	Mat deltau;
	Mat R;
	Mat D;

	//Matrix for DMC
	Mat Su;  //Step response vector
	Mat Saux; //Auxiliar vector to create matrix A
	Mat Q1;
	Mat I2;
    Mat A;
    Mat M;
	
	//Prediction parameters
	int t;
	int n;
	int m;
	
 public:
    DMC(int T, int N, Mat su, double alfa);                  //Constructor
    DMC(const std::string &configuration_yml_file_location); //otro Constructor
	virtual ~DMC();  //Destructor
	inline void setReference(double ref){reference=ref;}
	inline void setFeedback(double measure){feedback=measure;}
	void setAlpha(double alpha); //Sets alpha parameter which allows to control the response time
	double getOutput();
    void setParam(const string &configuration_yml_file_location);
    void setParam(int T, int N, Mat su, double alfa);
	void printmatrices();
	
	void reset();

    // dummy functions enforced by PID class interface
    inline void setGains(const double p, const double i, const double d) { return; }

    // Antiwindup and saturation parameters
    bool   saturation_enabled;
    double saturation_min, saturation_max;
    inline void enableAntiWindup(bool enable, double max)               { enableAntiWindup( enable, -max, +max); return; }
    inline void enableAntiWindup(bool enable, double min, double max)   { return; }
    void enableMaxOutput(bool enable, double max);
    void enableMaxOutput(bool enable, double min, double max);

 };
}
#endif /* DMC_H_ */
