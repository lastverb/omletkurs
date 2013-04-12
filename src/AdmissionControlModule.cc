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

#include "AdmissionControlModule.h"

AdmissionControlModule::AdmissionControlModule() {
    // TODO Auto-generated constructor stub

}

AdmissionControlModule::~AdmissionControlModule() {
    // TODO Auto-generated destructor stub
}

void AdmissionControlModule::initialize()
{
    readyToSend = false;
    queueSize = 0;
    maxQueueSize = par("maxQueueSize");
}

void AdmissionControlModule::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(),"jobDone") == 0)
    {
        readyToSend = true;
        checkAndSend();
        delete msg;
    }
    else
    {
        Packet *p = check_and_cast<Packet *>(msg);
        newIncomePacket(p);
        checkAndSend();
    }
}

void AdmissionControlModule::newIncomePacket(Packet *p)
{
    accept(p);
}

void AdmissionControlModule::accept(Packet *p)
{
    q.push_back(p);
    queueSize += p->getPayloadArraySize();
}

void AdmissionControlModule::reject(Packet *p)
{
    delete p;
}

void AdmissionControlModule::checkAndSend()
{
    if(!readyToSend || q.empty()) return;
    readyToSend = false;
    send(q.front(),"outGates$o",0);
    queueSize -= q.front()->getPayloadArraySize();
    q.erase(q.begin());
}
