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

#ifndef WFQ_H_
#define WFQ_H_

#include <omnetpp.h>
#include "packet_m.h"
#include <limits.h>
#include <math.h>
#include <vector>
using namespace std;

class WFQ: public cSimpleModule {
private:
    int lastServedQueue;
    cMessage *processEvent;
    double timeConstant;
    int lastSessionId;
    int actualQueue;
    vector <double> schedule;
    vector <double> multipliers;
    vector < vector <Packet*> > queues;
    vector < unsigned int> queueSize;
    unsigned int maxQueueSize;

public:
    WFQ();
    virtual ~WFQ();
    void initialize();
    virtual void handleMessage(cMessage *msg);
    void computeWeights(double value);
    void generateWeights();
    int chooseQueue();
};

    Define_Module(WFQ);

#endif /* WFQ_H_ */
