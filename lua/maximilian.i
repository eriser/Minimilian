
%module lmaximilian 
%include "std_string.i" 

#define final
%{
    #include "maximilian.h"
    #include "core.h"
    #include "chorus.h"
    #include "delayline.h"
    #include "dynamic.h"
    #include "env.h"
    #include "envelope.h"
    #include "envelopefollower.h"
    #include "filter.h"
    #include "flanger.h"
    #include "lagexp.h"
    #include "mix.h"
    #include "oscillator.h"
    #include "sample.h"
%}

%include "maximilian.h"
%include "core.h"
%include "chorus.h"
%include "delayline.h"
%include "dynamic.h"
%include "env.h"
%include "envelope.h"
%include "envelopefollower.h"
%include "filter.h"
%include "flanger.h"
%include "lagexp.h"
%include "mix.h"
%include "oscillator.h"
%include "sample.h"