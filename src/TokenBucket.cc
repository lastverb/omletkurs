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

#include "TokenBucket.h"

TokenBucket::TokenBucket() {
    // TODO Auto-generated constructor stub

}

TokenBucket::~TokenBucket() {
    // TODO Auto-generated destructor stub
}

void TokenBucket::initialize() {
    fillTokens = new cMessage("refill");
    sendMsg = new cMessage("send");
    msgInProgress = NULL;
    delay = par("delay");
    queueSize = par("queueSize");
    beginCount = true;

    tokensCount = tokensMax = par("tokensMax");
    request();
}

void TokenBucket::handleMessage(cMessage *msg) {
    if (msg == fillTokens) {
        tokensCount = tokensMax;
        scheduleAt(simTime() + delay, fillTokens);
        if(msgInProgress) {scheduleAt(simTime(), sendMsg);}
    } else if (msg == sendMsg) {
        if (tokensCount > 0) {
            send(msgInProgress, "out$o");
            tokensCount--;
            if (queue.empty()) {
                msgInProgress = NULL;
                request();
            } else {
                msgInProgress = (cMessage *) queue.pop();
               if(tokensCount > 0){
                   scheduleAt(simTime(), sendMsg);
               }

            }
        }
    } else if (!msgInProgress) {
        if(beginCount){
            scheduleAt(simTime() + delay, fillTokens);
            beginCount = false;
        }
        msgInProgress = msg;
        scheduleAt(simTime(), sendMsg);
    } else {
        if (queue.getLength() > queueSize) {
            delete msg;
            return;
        }

        queue.insert(msg);
    }
}

void TokenBucket::request()
{
    JobDone* msg = new JobDone("jobDone");
    send(msg, "in$o");
}
