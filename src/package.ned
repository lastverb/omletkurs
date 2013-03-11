package omletkurs;

@license(LGPL);

simple OmNomNom
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
}

simple BaseGenerator
{
    parameters:
        int packetLength = default(20);
        double sessionLength = default(10.0);
        int packetPriority = default(3);
        @statistic[timeChange](title="Wait Time"; source="send"; record=vector,stats; interpolationmode=none);
        @display("i=block/routing");
    gates:
        output out[];
}

simple Poisson extends BaseGenerator{
    
    parameters:
        @class(Poisson);
        double lambda=default(10.0);
}

simple Wykladniczy extends BaseGenerator{
    
    parameters:
        @class(Wykladniczy);
        double lambda=default(1.5);
}

network laborki1_1
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        omNomNom1: OmNomNom {
            parameters:
                @display("i=,gold");
        }
        poisson1: Poisson{
            
        }
    connections:
      poisson1.out++ --> Channel --> omNomNom1.in;

}

network laborki1_2
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        omNomNom1: OmNomNom {
            parameters:
                @display("i=,gold");
        }
        wykladniczy1: Wykladniczy{
            
        }
    connections:
      wykladniczy1.out++ --> Channel --> omNomNom1.in;

}
