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

#include "FQ.h"

FQ::FQ() {
    // TODO Auto-generated constructor stub

}

FQ::~FQ() {
    // TODO Auto-generated destructor stub
}


void FQ::initialize() {
    messageSentSignal = registerSignal("send");
    processEvent = new cMessage("process");

    lastServedQueue = 0;
    actualQueue=0;
    timeConstant=1.2;
    quantumLength = double(par("quantumLength"));
    quantum= double(par("quantumLength"));
    int n = int(par("ilGeneratorow"));
    queues.resize(n);
    schedule.resize(n);
    for(int i=0;i<schedule.size();i++){
        schedule[i]=0.0;
    }

    scheduleAt(simTime() + quantumLength, processEvent);
}

void FQ::handleMessage(cMessage *msg) {

    if(msg!=processEvent){
        Packet *packet = check_and_cast<Packet *>(msg);
//        EV << "przyszedl " << packet->getPacketId() << " \n";
        queues[packet->getSrc()].push_back(packet);
//        EV << "trafil do " << packet->getSrc() << " \n";
    }else{
        double time=0.0;
        actualQueue=chooseQueue();
        if(queues[actualQueue].size()>0){
            Packet *p = queues[lastServedQueue].front();
            double k=ceil((double(p->getPayloadArraySize())*timeConstant)/quantum);
            time+=k*quantum;

            schedule[actualQueue]+=double(p->getPayloadArraySize());
            double c=schedule[chooseQueue()];
            computeParameters(c);

//            EV << "obsluzony i usuniety " << p->getPacketId() <<" dl kolejki "<<queues[actualQueue].size() << " \n";
//            EV<<"mial "<< p->getPayloadArraySize() << " \n";
            queues[actualQueue].erase(queues[actualQueue].begin());
            send(p,"out");
//            EV <<" dl kolejki po"<<queues[actualQueue].size() <<"czas czekania "<< time << " \n";

//            EV << "actualQueue "<< actualQueue;
            scheduleAt(simTime() + time, processEvent);
        }else{

            scheduleAt(simTime() + 1, processEvent);
        }

    }

}


void FQ::computeParameters(double value){
    for(int i=0;i<schedule.size();i++){
        schedule[i]-=value;
        if(schedule[i]<0.0){
            schedule[i]=0.0;
        }
//        EV << "computeWeights "<< schedule[i];
    }

}

int FQ::chooseQueue(){
    int q=0;
    double w=double(INT_MAX);
    for(int i=0;i<schedule.size();i++){
        if(queues[i].size()>0){
            if(schedule[i]<w){
                w=schedule[i];
                q=i;
            }
        }
    }
    return q;
}
