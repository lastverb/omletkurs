package omletkurs;

@license(LGPL);

simple OmNomNom
{
    parameters:
        @display("i=block/routing");
        @statistic[waitTime](title="Wait Time"; source="packet"; record=vector,stats; interpolationmode=none);
    gates:
        inout in[];
}

simple RoundRobin2
{
    parameters:
        double timeConstant = default(0.8);
        int ilGeneratorow = default(3);
        int maxQueueSize = default(200);
        @display("i=block/routing");
    gates:
        inout in[];
        inout out;
        inout rejectGate;
}

simple WRoundRobin
{
    parameters:
        double timeConstant = default(0.8);
        int ilGeneratorow = default(3);
        int maxQueueSize = default(200);
        @display("i=block/routing");
    gates:
        inout in[];
        inout out;
        inout rejectGate;
}

simple WFQ
{
    parameters:
        double timeConstant = default(0.8);
        int ilGeneratorow = default(3);
        int maxQueueSize = default(200);
        @display("i=block/routing");
    gates:
        inout in[];
        inout out;
        inout rejectGate;
}

simple FQ
{
    parameters:
        double timeConstant = default(0.8);
        int ilGeneratorow = default(3);
        int maxQueueSize = default(200);
        @display("i=block/routing");
    gates:
        inout in[];
        inout out;
        inout rejectGate;
}

simple BaseGenerator
{
    parameters:
        int packetLengthMin = default(5);
        int packetLengthMax = default(20);
        double sessionLength = default(10.0);        
        int packetPriority = default(3);
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
        inout out;
}

simple AdmissionControlModule
{
    parameters:
        int maxQueueSize = default(200);
    gates:
        inout inGates[];
        inout rejectGate;
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
        inout rejectGate;
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
        inout rejectGate;
}


network generator_poisson
{
    types:
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        omNomNom1: OmNomNom;
        poisson1: Poisson;
    connections:
        poisson1.out <--> NoDelay <--> omNomNom1.in++;
}

network generator_wykladniczy
{
    types:
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        omNomNom1: OmNomNom;
        wykladniczy1: Wykladniczy;
    connections:
        wykladniczy1.out <--> NoDelay <--> omNomNom1.in++;
}

network generator_onoff
{
    types:
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        omNomNom1: OmNomNom;
        onOff1: OnOffGenerator;
    connections:
        onOff1.out <--> NoDelay <--> omNomNom1.in++;
}

network generator_mmpp
{
    types:
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        omNomNom1: OmNomNom;
        mmpp1: Mmpp;
    connections:
        mmpp1.out <--> NoDelay <--> omNomNom1.in++;
}

network ac_TailDrop
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        adm1: TailDrop;
        worker1: Worker;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> adm1.inGates++;
        adm1.outGate <--> NoDelay <--> worker1.gate;
        worker1.out <--> NoDelay <--> timer.in++;
        adm1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network ac_FrontDrop
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        adm1: FrontDrop;
        worker1: Worker;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> adm1.inGates++;
        adm1.outGate <--> NoDelay <--> worker1.gate;
        worker1.out <--> NoDelay <--> timer.in++;
        adm1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network ac_RED
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        adm1: RED;
        worker1: Worker;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> adm1.inGates++;
        adm1.outGate <--> NoDelay <--> worker1.gate;
        worker1.out <--> NoDelay <--> timer.in++;
        adm1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network ac_WRED
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        adm1: WRED;
        worker1: Worker;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> adm1.inGates++;
        adm1.outGate <--> NoDelay <--> worker1.gate;
        worker1.out <--> NoDelay <--> timer.in++;
        adm1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network profile_leaky
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        bucket1: LeakyBucket;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> bucket1.in;
        bucket1.out <--> NoDelay <--> timer.in++;
        bucket1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network profile_leaky2
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        bucket1: LeakyBucket;
        bucket2: LeakyBucket;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> bucket1.in;
        bucket1.out <--> NoDelay <--> bucket2.in;
        bucket2.out <--> NoDelay <--> timer.in++;
        bucket1.rejectGate <--> NoDelay <--> rejecter.in++;
        bucket2.rejectGate <--> NoDelay <--> rejecter.in++;
}

network profile_token
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        bucket1: TokenBucket;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> bucket1.in;
        bucket1.out <--> NoDelay <--> timer.in++;
        bucket1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network profile_token2
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        bucket1: TokenBucket;
        bucket2: TokenBucket;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
        generator1.out <--> Channel <--> bucket1.in;
        bucket1.out <--> NoDelay <--> bucket2.in;
        bucket2.out <--> NoDelay <--> timer.in++;
        bucket1.rejectGate <--> NoDelay <--> rejecter.in++;
        bucket2.rejectGate <--> NoDelay <--> rejecter.in++;
}

network scheduler_RR
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        scheduler1: RoundRobin2;
        generator[3]: Poisson;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
      generator[0].out <--> Channel <--> scheduler1.in++;
      generator[1].out <--> Channel <--> scheduler1.in++;
      generator[2].out <--> Channel <--> scheduler1.in++;
      scheduler1.out <--> NoDelay <--> timer.in++;
      scheduler1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network scheduler_WRR
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        scheduler1: WRoundRobin;
        generator[3]: Poisson;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
      generator[0].out <--> Channel <--> scheduler1.in++;
      generator[1].out <--> Channel <--> scheduler1.in++;
      generator[2].out <--> Channel <--> scheduler1.in++;
      scheduler1.out <--> NoDelay <--> timer.in++;
      scheduler1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network scheduler_FQ
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        scheduler1: FQ;
        generator[3]: Poisson;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
      generator[0].out <--> Channel <--> scheduler1.in++;
      generator[1].out <--> Channel <--> scheduler1.in++;
      generator[2].out <--> Channel <--> scheduler1.in++;
      scheduler1.out <--> NoDelay <--> timer.in++;
      scheduler1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network scheduler_WFQ
{
    types:
        channel Channel extends ned.DelayChannel {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        scheduler1: WFQ;
        generator[3]: Poisson;
        timer: OmNomNom;
        rejecter: OmNomNom;
    connections:
      generator[0].out <--> Channel <--> scheduler1.in++;
      generator[1].out <--> Channel <--> scheduler1.in++;
      generator[2].out <--> Channel <--> scheduler1.in++;
      scheduler1.out <--> NoDelay <--> timer.in++;
      scheduler1.rejectGate <--> NoDelay <--> rejecter.in++;
}

network laborki_test1
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        generator2: Poisson;
        generator3: Poisson;
        adm1: TailDrop;
        bucket1: LeakyBucket;
        scheduler1: RoundRobin2;
        rejecter: OmNomNom;
        timer: OmNomNom;
    connections:
        generator1.out <--> Channel <--> adm1.inGates++;
        generator2.out <--> Channel <--> adm1.inGates++;
        generator3.out <--> Channel <--> adm1.inGates++;
        adm1.outGate <--> NoDelay <--> bucket1.in;
        bucket1.out <--> NoDelay <--> scheduler1.in++;
        adm1.rejectGate <--> NoDelay <--> rejecter.in++;
        bucket1.rejectGate <--> NoDelay <--> rejecter.in++;
        scheduler1.rejectGate <--> NoDelay <--> rejecter.in++;
        scheduler1.out <--> NoDelay <--> timer.in++;
}

network laborki_test2
{
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
        channel NoDelay extends ned.IdealChannel{}
    submodules:
        generator1: Poisson;
        generator2: Poisson;
        generator3: Poisson;
        adm1: FrontDrop;
        bucket1: TokenBucket;
        scheduler1: FQ;
        rejecter: OmNomNom;
        timer: OmNomNom;
    connections:
        generator1.out <--> Channel <--> adm1.inGates++;
        generator2.out <--> Channel <--> adm1.inGates++;
        generator3.out <--> Channel <--> adm1.inGates++;
        adm1.outGate <--> NoDelay <--> bucket1.in;
        bucket1.out <--> NoDelay <--> scheduler1.in++;
        adm1.rejectGate <--> NoDelay <--> rejecter.in++;
        bucket1.rejectGate <--> NoDelay <--> rejecter.in++;
        scheduler1.rejectGate <--> NoDelay <--> rejecter.in++;
        scheduler1.out <--> NoDelay <--> timer.in++;
}
