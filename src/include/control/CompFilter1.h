/*
 * CompFilter1.h
 *
 *  Created on: 17/10/2012
 *      Author: Ignacio Mellado-Bataller
 *
 *  Description: 1st order complementary filter
 */

#ifndef COMPFILTER1_H_
#define COMPFILTER1_H_

#include <math.h>
#include "Filter.h"

namespace CVG_BlockDiagram {

class CompFilter1 {
public:
	CompFilter1();
	~CompFilter1();

	void setSamplingFrequency(float fs);
	void setCutoffFrequency(float fc);
    float filter(float sourceLow, float sourceHigh);

protected:
	void precalc();

private:
    float fs, fc, alpha;
    float value;
	Filter lowpass, hipass;
};

}

#endif /* COMPFILTER1_H_ */
