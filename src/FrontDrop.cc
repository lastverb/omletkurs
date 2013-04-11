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

#include "FrontDrop.h"

FrontDrop::FrontDrop() {
    // TODO Auto-generated constructor stub

}

FrontDrop::~FrontDrop() {
    // TODO Auto-generated destructor stub
}

void FrontDrop::initialize()
{
    AdmissionControlModule::initialize();
    maxQueueSize = par("maxQueueSize");
}

void FrontDrop::newIncomePacket(Packet *p)
{
    if(queueSize + p->getPayloadArraySize() > maxQueueSize)
    {
        reject(p);
    }
    else
    {
        accept(p);
    }
}

void FrontDrop::reject(Packet *p)
{
    if(!q.empty())
    {
        Packet *t = q.front();
        q.erase(q.begin());
        delete t;
    }
    accept(p);
}



