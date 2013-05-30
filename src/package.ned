package omletkurs;

@license(LGPL);

simple OmNomNom
{
    parameters:
        @display("i=block/routing");
    gates:
        input in[];
}

simple RoundRobin2
{
    parameters:
        double quantumLength = default(5.0);
        int ilGeneratorow = default(3);
        @display("i=block/routing");
    gates:
        inout in[];
}

simple WRoundRobin
{
    parameters:
        double quantumLength = default(5.0);
        int ilGeneratorow = default(3);
        @display("i=block/routing");
    gates:
        inout in[];
}

simple WFQ
{
    parameters:
        double quantumLength = default(5.0);
        int ilGeneratorow = default(3);
        @display("i=block/routing");
    gates:
        inout in[];
}

simple FQ
{
    parameters:
        double quantumLength = default(5.0);
        int ilGeneratorow = default(3);
        @display("i=block/routing");
    gates:
        inout in[];
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
        inout out;
}

simple Poisson extends BaseGenerator
{
    parameters:
        @class(Poisson);
        double lambda = default(10.0);
}

simple Wykladniczy extends BaseGenerator
{
    parameters:
        @class(Wykladniczy);
        double lambda = default(1.5);
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
        double lambda = default(10.0);
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
    parameters:
        int maxQueueSize = default(200);
    gates:
        inout inGates[];
        output rejectGate;
        inout outGate;
}

simple TailDrop extends AdmissionControlModule
{
    parameters:
        @class(TailDrop);
}

simple FrontDrop extends AdmissionControlModule
{
    parameters:
        @class(FrontDrop);
}

simple RED extends AdmissionControlModule
{
    parameters:
        @class(RED);
        int minT = default(100);
        double multiplier = default(0.4);
}

simple WRED extends AdmissionControlModule
{
    parameters:
        @class(WRED);
        int minTmin = default(50);
        int minTmax = default(150);
        double multiplierMin = default(0.2);
        double multiplierMax = default(0.6);
}

simple LeakyBucket
{
    parameters:
        @class(LeakyBucket);
        int queueSize = default(200);
        int delay = default(0.5);

    gates:
        inout in;
        inout out;
        output rejectGate;
}

simple TokenBucket
{
    parameters:
        @class(TokenBucket);
        int queueSize = default(200);
        int delay = default(10);
        int tokensMax = default(2);

    gates:
        inout in;
        inout out;
        output rejectGate;
}


//network laborki1_1
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//    submodules:
//        omNomNom1: OmNomNom {
//            parameters:
//                @display("i=,gold");
//        }
//        poisson1: Poisson;
//    connections:
//        poisson1.out++ --> Channel --> omNomNom1.in;
//}
//
//network laborki1_2
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//    submodules:
//        omNomNom1: OmNomNom {
//            parameters:
//                @display("i=,gold");
//        }
//        wykladniczy1: Wykladniczy;
//    connections:
//        wykladniczy1.out++ --> Channel --> omNomNom1.in;
//}
//
//network laborki1_3A
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//    submodules:
//        omNomNom1: OmNomNom {
//            parameters:
//                @display("i=,gold");
//        }
//        onOff1: OnOffGenerator;
//    connections:
//        onOff1.out++ --> Channel --> omNomNom1.in;
//}
//
//network laborki1_4
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//    submodules:
//        omNomNom1: OmNomNom {
//            parameters:
//                @display("i=,gold");
//        }
//        mmpp1: Mmpp;
//    connections:
//        mmpp1.out++ --> Channel --> omNomNom1.in;
//}
//
//network laborki2_11
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//        channel NoDelay extends ned.IdealChannel
//        {
//        }
//    submodules:
//        generator1: Poisson;
//        adm1: TailDrop;
//        worker1: Worker;
//    connections:
//        generator1.out++ --> Channel --> adm1.inGates++;
//        adm1.outGate <--> NoDelay <--> worker1.gate;
//}
//
//network laborki2_12
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//        channel NoDelay extends ned.IdealChannel
//        {
//        }
//    submodules:
//        generator1: Poisson;
//        adm1: FrontDrop;
//        worker1: Worker;
//    connections:
//        generator1.out++ --> Channel --> adm1.inGates++;
//        adm1.outGate <--> NoDelay <--> worker1.gate;
//}
//
//network laborki2_13
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//        channel NoDelay extends ned.IdealChannel
//        {
//        }
//    submodules:
//        generator1: Poisson;
//        adm1: RED;
//        worker1: Worker;
//    connections:
//        generator1.out++ --> Channel --> adm1.inGates++;
//        adm1.outGate <--> NoDelay <--> worker1.gate;
//}
//
//network laborki2_14
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//        channel NoDelay extends ned.IdealChannel
//        {
//        }
//    submodules:
//        generator1: Poisson;
//        adm1: WRED;
//        worker1: Worker;
//    connections:
//        generator1.out++ --> Channel --> adm1.inGates++;
//        adm1.outGate <--> NoDelay <--> worker1.gate;
//}

//network laborki2_21
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//    submodules:
//        generator1: Poisson;
//        leaky1: LeakyBucket {
//            @display("i=block/bucket");
//        }
//        omnom1: OmNomNom;
//    connections:
//        generator1.out++ --> Channel --> leaky1.in++;
//        leaky1.out --> Channel --> omnom1.in;
//
//}
//
//network laborki2_22
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//    submodules:
//        generator1: Poisson;
//        leaky1: LeakyBucket {
//            @display("i=block/bucket");
//        }
//        leaky2: LeakyBucket {
//            @display("i=block/bucket");
//        }
//        omnom1: OmNomNom;
//    connections:
//        generator1.out++ --> Channel --> leaky1.in++;
//        leaky1.out --> Channel --> leaky2.in++;
//        leaky2.out --> Channel --> omnom1.in;
//
//}
//
//network laborki2_23
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//    submodules:
//        generator1: Poisson;
//        token1: TokenBucket {
//            @display("i=block/bucket");
//        }
//        omnom1: OmNomNom;
//    connections:
//        generator1.out++ --> Channel --> token1.in++;
//        token1.out --> Channel --> omnom1.in;
//
//}
//
//network laborki2_24
//{
//    types:
//        channel Channel extends ned.DelayChannel
//        {
//            delay = 100ms;
//        }
//    submodules:
//        generator1: Poisson;
//        token1: TokenBucket {
//            @display("i=block/bucket");
//        }
//        token2: TokenBucket {
//            @display("i=block/bucket");
//        }
//        omnom1: OmNomNom;
//    connections:
//        generator1.out++ --> Channel --> token1.in++;
//       token1.out --> Channel --> token2.in++;
//        token2.out --> Channel --> omnom1.in;
//
//}

//network laborki2_RR2
//{
//    types:
//        channel Channel extends ned.DelayChannel {
//            delay = 100ms;
//        }
//    submodules:
//        rr: RoundRobin2 {
//            parameters:
//                @display("i=,gold");
//        }
//        wykladniczy[3]: Wykladniczy{
//            
//        }
//        
//    connections:
//      wykladniczy[0].out++ --> Channel --> rr.in++;
//      wykladniczy[1].out++ --> Channel --> rr.in++;
//      wykladniczy[2].out++ --> Channel --> rr.in++;
//
//}
//
//network laborki2_WRR
//{
//    types:
//        channel Channel extends ned.DelayChannel {
//            delay = 100ms;
//        }
//    submodules:
//        wrr: WRoundRobin {
//            parameters:
//                @display("i=,gold");
//        }
//        wykladniczy[3]: Wykladniczy{
//            
//        }
//        
//    connections:
//      wykladniczy[0].out++ --> Channel --> wrr.in++;
//      wykladniczy[1].out++ --> Channel --> wrr.in++;
//      wykladniczy[2].out++ --> Channel --> wrr.in++;
//
//}
//
//network laborki2_WFQ
//{
//    types:
//        channel Channel extends ned.DelayChannel {
//            delay = 100ms;
//        }
//    submodules:
//        wfq: WFQ {
//            parameters:
//                @display("i=,gold");
//        }
//        wykladniczy[3]: Wykladniczy{
//            
//        }
//        
//    connections:
//      wykladniczy[0].out++ --> Channel --> wfq.in++;
//      wykladniczy[1].out++ --> Channel --> wfq.in++;
//      wykladniczy[2].out++ --> Channel --> wfq.in++;
//
//}
//
//network laborki2_FQ
//{
//    types:
//        channel Channel extends ned.DelayChannel {
//            delay = 100ms;
//        }
//    submodules:
//        fq: FQ {
//            parameters:
//                @display("i=,gold");
//        }
//        wykladniczy[3]: Wykladniczy{
//            
//        }
//        
//    connections:
//      wykladniczy[0].out++ --> Channel --> fq.in++;
//      wykladniczy[1].out++ --> Channel --> fq.in++;
//      wykladniczy[2].out++ --> Channel --> fq.in++;
//
//}
//testowy
//network laborki2_FQ
//{
//    types:
//        channel Channel extends ned.DelayChannel {
//            delay = 100ms;
//        }
//    submodules:
//        fq: FQ {
//            parameters:
//                @display("i=,gold");
//        }
//        adm1[3]: RED;
//        
//        
//    connections:
//      adm1[0].outGates++ <--> Channel <--> fq.in++;
//      adm1[1].outGates++ <--> Channel <--> fq.in++;
//      adm1[2].outGates++ <--> Channel <--> fq.in++;
//
//}


network laborki_test1
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel
        {
        }
    submodules:
        generator1: Poisson;
        adm1: TailDrop;
        bucket1: LeakyBucket;
        scheduler1: RoundRobin2;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> adm1.inGates++;
        adm1.outGate <--> NoDelay <--> bucket1.in;
        bucket1.out <--> NoDelay <--> scheduler1.in++;
        adm1.rejectGate --> NoDelay --> rejecter.in++;
        bucket1.rejectGate --> NoDelay --> rejecter.in++;
}

network laborki_test2
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel
        {
        }
    submodules:
        generator1: Poisson;
        adm1: TailDrop;
        bucket1: TokenBucket;
        scheduler1: RoundRobin2;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> adm1.inGates++;
        adm1.outGate <--> NoDelay <--> bucket1.in;
        bucket1.out <--> NoDelay <--> scheduler1.in++;
        adm1.rejectGate --> NoDelay --> rejecter.in++;
        bucket1.rejectGate --> NoDelay --> rejecter.in++;
}
