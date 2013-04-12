//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "WRED.h"
#define CLASSES 5

WRED::WRED() {
    // TODO Auto-generated constructor stub

}

WRED::~WRED() {
    // TODO Auto-generated destructor stub
}

void WRED::initialize()
{
    AdmissionControlModule::initialize();
    minT = new unsigned int[CLASSES];
    multiplier = new double[CLASSES];
    int minTmin = par("minTmin");
    int minTmax = par("minTmax");
    double mulMin = double(par("multiplierMin"));
    double mulMax = double(par("multiplierMax"));

    for(int i=0; i<CLASSES; ++i)
    {
        minT[i] = intuniform(minTmin, minTmax);
        multiplier[i] = mulMin + dblrand() * (mulMax - mulMin);
    }
}

void WRED::newIncomePacket(Packet *p)
{
    unsigned int sizeT = queueSize + p->getPayloadArraySize();
    int c = p->getPriorityClass();
    if(c > CLASSES)
        c = 0;

    if(sizeT > maxQueueSize)
    {
        reject(p);
    }
    else if(sizeT > minT[c])
    {
        double k = multiplier[c] * (sizeT - minT[c])/double((maxQueueSize - minT[c]));
        if(intuniform(0,INT_MAX) / double(INT_MAX) > k)
            accept(p);
        else
            reject(p);
    }
    else
    {
        accept(p);
    }
}

