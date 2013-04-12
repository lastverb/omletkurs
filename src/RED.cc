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

#include "RED.h"

RED::RED() {
    // TODO Auto-generated constructor stub

}

RED::~RED() {
    // TODO Auto-generated destructor stub
}

void RED::initialize()
{
    AdmissionControlModule::initialize();
    minT = par("minT");
    multiplier = double(par("multiplier"));
}

void RED::newIncomePacket(Packet *p)
{
    unsigned int sizeT = queueSize + p->getPayloadArraySize();
    if(sizeT > maxQueueSize)
    {
        reject(p);
    }
    else if(sizeT > minT)
    {
        double k = multiplier * (sizeT - minT)/double((maxQueueSize - minT));
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

