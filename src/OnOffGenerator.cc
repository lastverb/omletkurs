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

#include "OnOffGenerator.h"

OnOffGenerator::OnOffGenerator() {
    // TODO Auto-generated constructor stub

}

OnOffGenerator::~OnOffGenerator() {
    // TODO Auto-generated destructor stub
}

void OnOffGenerator::initializeBonus() {
    minChangeTime = par("minChangeTime");
    maxChangeTime = par("maxChangeTime");
    maxChangeTime -= minChangeTime;
    nextChangeTime = simTime();
    nextChangeTime += minChangeTime + intuniform(0, maxChangeTime);
}

simtime_t OnOffGenerator::getTimeChange() {
    double lambda=par("lambda");
    double l=exp(-lambda);
    int k=0;
    double p=1;
    int changeTime;

    do{
        double u=intuniform(0,INT_MAX)/double(INT_MAX);
        k=k+1;
        p=p*u;

    }while(p>l);
    --k;

    if(nextChangeTime < simTime() + k){
        changeTime = minChangeTime + intuniform(0, maxChangeTime);
        EV << changeTime << "\n";
        k += changeTime;
        nextChangeTime += changeTime;
        nextChangeTime += minChangeTime + intuniform(0, maxChangeTime);
    }

    return k;
}
