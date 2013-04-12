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
}

void LeakyBucket::handleMessage(cMessage *msg) {
    if (msg == handleOver) {

        send(msgInProgress, "out");
        if (queue.empty()) {
            msgInProgress = NULL;
        } else {
            msgInProgress = (cMessage *) queue.pop();
            scheduleAt(simTime() + delay, handleOver);
        }
    } else if (!msgInProgress) {

        msgInProgress = msg;
        scheduleAt(simTime() + delay, handleOver);
    } else {
        if (queue.getLength() > queueSize) {
            delete msg;
            return;
        }

        queue.insert(msg);

    }
}
