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
    // TODO Auto-generated constructor stub

}

LeakyBucket::~LeakyBucket() {
    // TODO Auto-generated destructor stub
}

void LeakyBucket::initialize() {
    delay = 2;
    queueSize = 50;

}

void LeakyBucket::handleMessage(cMessage *msg) {
    if (msg == endMsg) {

        if (!queue.isEmpty()) {
            handledMsg = queue.pop();
            send(handledMsg, "out");
        }

    }

    if (queue.length() > queueSize) {
        delete msg;
    } else {
        queue.insert(msg);
        scheduleAt(simTime() + delay, endMsg);

    }

}
