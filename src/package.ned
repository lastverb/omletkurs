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
    connections:

}
