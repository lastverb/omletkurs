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

#include "Mmpp.h"

Mmpp::Mmpp() {
    // TODO Auto-generated constructor stub

}

Mmpp::~Mmpp() {
    // TODO Auto-generated destructor stub
}

simtime_t Mmpp::getTimeChange(){
    int lambda[4] = {4,6,8,10};
    int delay[4] = {0,10,20,30};
    int random = intuniform(0,3);

    double l=exp(-lambda[random]);
    int k=0;
    double p=1;

    do{
        double u=intuniform(0,INT_MAX)/double(INT_MAX);
        k=k+1;
        p=p*u;

    }while(p>l);

    return k-1 + delay[random];
}

