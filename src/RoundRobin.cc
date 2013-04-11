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

#include "RoundRobin.h"

RoundRobin::RoundRobin() {
    // TODO Auto-generated constructor stub

}

RoundRobin::~RoundRobin() {
    // TODO Auto-generated destructor stub
}

void RoundRobin::initialize() {
    messageSentSignal = registerSignal("send");
    processEvent = new cMessage("process");

    lastServedQueue = 0;
    quantumLength = double(par("quantumLength"));
    quantum= double(par("quantumLength"));
    int n = gateSize("in");
    queues.resize(n);



    scheduleAt(simTime() + quantumLength, processEvent);
}

void RoundRobin::handleMessage(cMessage *msg) {

    if(msg!=processEvent){
        Packet *packet = check_and_cast<Packet *>(msg);
        EV << "przyszedl " << packet->getPacketId() << " \n";
        queues[packet->getSrc()].push_back(*packet);
        EV << "trafil do " << packet->getSrc() << " \n";
    }else{
        if(queues[lastServedQueue].size()>0){
            double time=queues[lastServedQueue].begin()->getTime();
            if(time<=quantum){
                EV << "obsluzony i usuniety " << queues[lastServedQueue].begin()->getPacketId() <<" dl kolejki "<<queues[lastServedQueue].size() << " \n";
                EV<<"mial "<< queues[lastServedQueue].begin()->getTime() << " \n";
                bubble("obsluzony i usuniety ");
                queues[lastServedQueue].erase(queues[lastServedQueue].begin());
                EV <<" dl kolejki po"<<queues[lastServedQueue].size() << " \n";
            }else{
                EV << "obsluzony" << queues[lastServedQueue].begin()->getPacketId() <<"mial "<< queues[lastServedQueue].begin()->getTime() << " \n";
                queues[lastServedQueue].begin()->setTime(time-quantum);
                EV << "ma" << queues[lastServedQueue].begin()->getTime() << " \n";
            }
            lastServedQueue++;
            if(lastServedQueue>=queues.size()){
                lastServedQueue=0;
            }
            EV << "lastServedQueue "<< lastServedQueue;
            scheduleAt(simTime() + quantumLength, processEvent);
        }else{
            lastServedQueue++;
            if(lastServedQueue>=queues.size()){
                lastServedQueue=0;
            }
            scheduleAt(simTime() + 1, processEvent);
        }

    }



}

