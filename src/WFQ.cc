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

#include "WFQ.h"

WFQ::WFQ() {
    // TODO Auto-generated constructor stub

}

WFQ::~WFQ() {
    // TODO Auto-generated destructor stub
}


void WFQ::initialize() {
    messageSentSignal = registerSignal("send");
    processEvent = new cMessage("process");

    lastServedQueue = 0;
    actualQueue=0;
    timeConstant=1.2;
    quantumLength = double(par("quantumLength"));
    quantum= double(par("quantumLength"));
    int n = gateSize("in");
    queues.resize(n);
    schedule.resize(n);
    multipliers.resize(n);
    generateWeights();


    scheduleAt(simTime() + quantumLength, processEvent);
}

void WFQ::handleMessage(cMessage *msg) {

    if(msg!=processEvent){
        Packet *packet = check_and_cast<Packet *>(msg);
        EV << "przyszedl " << packet->getPacketId() << " \n";
        //w time w pakiecie mozna zapisac czas siedzenia w kolejce
        //double t = simTime();
        //packet->setTime(t);
        queues[packet->getSrc()].push_back(*packet);
        EV << "trafil do " << packet->getSrc() << " \n";
    }else{
        double time=0.0;
        actualQueue=chooseQueue();
        if(queues[actualQueue].size()>0){
            double k=ceil((double(queues[actualQueue].begin()->getPayloadArraySize())*timeConstant)/quantum);
            time+=k*quantum;

            schedule[actualQueue]+=double(queues[actualQueue].begin()->getPayloadArraySize());
            double c=schedule[chooseQueue()];
            computeWeights(c);

            // czas siedzenia w kolejce do konca obsugi, wypadaloby go jakos do statystyk dac
            //double t = simTime();
            //t = t - queues[actualQueue].begin()->getTime();

            EV << "obsluzony i usuniety " << queues[actualQueue].begin()->getPacketId() <<" dl kolejki "<<queues[actualQueue].size() << " \n";
            EV<<"mial "<< queues[actualQueue].begin()->getPayloadArraySize() << " \n";
            bubble("obsluzony i usuniety ");
            queues[actualQueue].erase(queues[actualQueue].begin());
            EV <<" dl kolejki po"<<queues[actualQueue].size() <<"czas czekania "<< time << " \n";

            EV << "actualQueue "<< actualQueue;
            scheduleAt(simTime() + time, processEvent);
        }else{

            scheduleAt(simTime() + 1, processEvent);
        }

    }

}

void WFQ::generateWeights(){
    for(int i=0;i<schedule.size();i++){
        schedule[i]=0.0;
        multipliers[i]=double(intuniform(1, schedule.size()*2))/double(schedule.size()*2);
        EV << "multipliers "<< multipliers[i];
    }

}

void WFQ::computeWeights(double value){
    for(int i=0;i<schedule.size();i++){
        schedule[i]-=value;
        if(schedule[i]<0.0){
            schedule[i]=0.0;
        }
        EV << "computeWeights "<< schedule[i];
    }

}

int WFQ::chooseQueue(){
    int q=0;
    double w=double(INT_MAX);
    for(int i=0;i<schedule.size();i++){
        if(queues[i].size()>0){
            if((schedule[i]*multipliers[i])<w){
                w=(schedule[i]*multipliers[i]);
                q=i;
            }
        }
    }
    return q;
}
