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

#include "LeakyBucket.h"

LeakyBucket::LeakyBucket() {

}

LeakyBucket::~LeakyBucket() {

}

void LeakyBucket::initialize() {
     handleOver = new cMessage("finished-handling");

     delay = par("delay");
     queueSize = par("queueSize");
     request();
}

void LeakyBucket::handleMessage(cMessage *msg) {

    if(strcmp(msg->getName(),"jobDone") == 0) {
        delete msg;
    } else if (msg == handleOver) {
        send((cMessage *) queue.pop(), "out$o");
        if (queue.empty()) {
            request();
        } else {
            scheduleAt(simTime() + delay, handleOver);
        }

    } else {
        if (queue.getLength() > queueSize) {
            send(msg,"rejectGate");
            return;
        }
        if (queue.empty()) {
            scheduleAt(simTime() + delay, handleOver);
        }
        queue.insert(msg);
    }
}

void LeakyBucket::request()
{
    JobDone* msg = new JobDone("jobDone");
    send(msg, "in$o");
}
