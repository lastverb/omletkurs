package omletkurs;

@license(LGPL);

simple OmNomNom
{
    parameters:
        @display("i=block/routing");
    gates:
        input in;
}

simple RoundRobin
{
    parameters:
        double quantumLength = default(5.0);
        @display("i=block/routing");
    gates:
        input in[];
}

simple RoundRobin2
{
    parameters:
        double quantumLength = default(5.0);
        @display("i=block/routing");
    gates:
        input in[];
}

simple WRoundRobin
{
    parameters:
        double quantumLength = default(5.0);
        @display("i=block/routing");
    gates:
        input in[];
}

simple WFQ
{
    parameters:
        double quantumLength = default(5.0);
        @display("i=block/routing");
    gates:
        input in[];
}

simple FQ
{
    parameters:
        double quantumLength = default(5.0);
        @display("i=block/routing");
    gates:
        input in[];
}

simple BaseGenerator
{
    parameters:
        int packetLengthMin = default(5);
        int packetLengthMax = default(20);
        double sessionLength = default(10.0);
        int packetPriority = default(3);
        double quantumLength = default(10.0);
        @statistic[timeChange](title="Wait Time"; source="send"; record=vector,stats; interpolationmode=none);
        @display("i=block/routing");
    gates:
        output out[];
}

simple Poisson extends BaseGenerator
{
    parameters:
        @class(Poisson);
        double lambda=default(10.0);
}

simple Wykladniczy extends BaseGenerator
{
    parameters:
        @class(Wykladniczy);
        double lambda=default(1.5);
}

simple OnOffGenerator extends BaseGenerator
{
    parameters:
        @class(OnOffGenerator);
        double lambda = default(10.0);
        int minChangeTime = default(50);
        int maxChangeTime = default(100);
}

simple Mmpp extends BaseGenerator
{
    parameters:
        @class(Mmpp);
        double lambda=default(10.0);
}

simple Worker
{
    parameters:
        int workerId = default(0);
        double jobTimeMin = default(1.0);
    	double jobTimePerByte = default(0.1);
    gates:
        inout gate;
}

simple AdmissionControlModule
{
    gates:
        input inGates[];
        inout outGates[];
}

simple TailDrop extends AdmissionControlModule
{
    parameters:
        @class(TailDrop);
        int maxQueueSize = default(200);
}

simple FrontDrop extends AdmissionControlModule
{
    parameters:
        @class(FrontDrop);
        int maxQueueSize = default(200);
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

network laborki1_3A
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
        onOff1: OnOffGenerator{
            
        }
    connections:
      onOff1.out++ --> Channel --> omNomNom1.in;
}

network laborki1_4
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
        mmpp1: Mmpp{
            
        }
    connections:
      mmpp1.out++ --> Channel --> omNomNom1.in;
}

network laborki2_11
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel {}
    submodules:
        generator1: Poisson {}
        adm1: TailDrop {}
        worker1: Worker {}
    connections:
      generator1.out++ --> Channel --> adm1.inGates++;
      adm1.outGates++ <--> NoDelay <--> worker1.gate;
}

network laborki2_12
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel {}
    submodules:
        generator1: Poisson {}
        adm1: FrontDrop {}
        worker1: Worker {}
    connections:
      generator1.out++ --> Channel --> adm1.inGates++;
      adm1.outGates++ <--> NoDelay <--> worker1.gate;
}

network laborki2_RR
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        rr: RoundRobin {
            parameters:
                @display("i=,gold");
        }
        wykladniczy[3]: Wykladniczy{
            
        }
        
    connections:
      wykladniczy[0].out++ --> Channel --> rr.in++;
      wykladniczy[1].out++ --> Channel --> rr.in++;
      wykladniczy[2].out++ --> Channel --> rr.in++;

}

network laborki2_RR2
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        rr: RoundRobin2 {
            parameters:
                @display("i=,gold");
        }
        wykladniczy[3]: Wykladniczy{
            
        }
        
    connections:
      wykladniczy[0].out++ --> Channel --> rr.in++;
      wykladniczy[1].out++ --> Channel --> rr.in++;
      wykladniczy[2].out++ --> Channel --> rr.in++;

}

network laborki2_WRR
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        wrr: WRoundRobin {
            parameters:
                @display("i=,gold");
        }
        wykladniczy[3]: Wykladniczy{
            
        }
        
    connections:
      wykladniczy[0].out++ --> Channel --> wrr.in++;
      wykladniczy[1].out++ --> Channel --> wrr.in++;
      wykladniczy[2].out++ --> Channel --> wrr.in++;

}

network laborki2_WFQ
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        wfq: WFQ {
            parameters:
                @display("i=,gold");
        }
        wykladniczy[3]: Wykladniczy{
            
        }
        
    connections:
      wykladniczy[0].out++ --> Channel --> wfq.in++;
      wykladniczy[1].out++ --> Channel --> wfq.in++;
      wykladniczy[2].out++ --> Channel --> wfq.in++;

}

network laborki2_FQ
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
    submodules:
        fq: FQ {
            parameters:
                @display("i=,gold");
        }
        wykladniczy[3]: Wykladniczy{
            
        }
        
    connections:
      wykladniczy[0].out++ --> Channel --> fq.in++;
      wykladniczy[1].out++ --> Channel --> fq.in++;
      wykladniczy[2].out++ --> Channel --> fq.in++;

}
