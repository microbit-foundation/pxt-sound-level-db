basic.forever(function () {
    serial.writeLine("" + (input.soundLevel()))
    serial.writeLine("" + (input.soundLevelDb()) + " dB\n")
})
