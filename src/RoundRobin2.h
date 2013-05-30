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

#ifndef ROUNDROBIN2_H_
#define ROUNDROBIN2_H_

#include <omnetpp.h>
#include "packet_m.h"
#include <limits.h>
#include <math.h>
#include <vector>
using namespace std;

class RoundRobin2: public cSimpleModule {
private:
    simsignal_t messageSentSignal;
    int lastServedQueue;
    cMessage *processEvent;
    simtime_t quantumLength;
    double quantum;
    double timeConstant;
    int lastSessionId;
    int actualQueue;
    vector <int> schedule;
    vector < vector <Packet> > queues;

public:
    RoundRobin2();
    virtual ~RoundRobin2();
    void initialize();
    virtual void handleMessage(cMessage *msg);
    void computeWeights();
};

    Define_Module(RoundRobin2);

#endif /* ROUNDROBIN2_H_ */
