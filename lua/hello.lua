require "lmaximilian"

local context = lmaximilian.Context()
local osc1 = lmaximilian.Oscillator(context)
local osc2 = lmaximilian.Oscillator(context)
local filter = lmaximilian.Filter(context)

for i = 1, 100 do
    print( 
        filter:lores(
            800, 
            1, 
            osc1:saw(440) + osc2:saw(880) 
        )
    )
end 