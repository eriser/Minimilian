require "lmaximilian"

local context = lmaximilian.Context()
local osc1 = lmaximilian.Oscillator(context)
local osc2 = lmaximilian.Oscillator(context)

for i = 1, 100 do
    print( osc1:sawwave(440) + osc2:sawwave(880) )
end 