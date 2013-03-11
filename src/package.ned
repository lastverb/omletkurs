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
        @display("i=block/routing");
    gates:
        output out[];
}

simple Poisson extends BaseGenerator{
    
    parameters:
        @class(Poisson);
        double lambda=default(10.0);
}

network laborki1
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
