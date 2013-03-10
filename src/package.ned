package omletkurs;

@license(LGPL);

simple OmNomNom
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
}

network laborki1
{
    submodules:
        omNomNom1: OmNomNom {
            parameters:
                @display("i=,gold");
        }
    connections:

}
