tmr.alarm(3,30000,1,function() dofile('init.lua') end)

red = 8
blue = 7
green = 6


gpio.mode(red,gpio.OUTPUT)
gpio.mode(green,gpio.OUTPUT)
gpio.mode(blue,gpio.OUTPUT)
gpio.write(red,gpio.HIGH)
gpio.write(green,gpio.LOW)
gpio.write(blue,gpio.LOW)

tmr.alarm(0,1000,0,function() dofile('autoconnect.lua') end)

