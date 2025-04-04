let maxSound = 0
let soundLevel = 0
basic.forever(function () {
    soundLevel = input.soundLevelDb()
    serial.writeLine("" + (soundLevel))
    led.plotBarGraph(
    Math.map(soundLevel, 30, 120, 0, 25),
    25
    )
    if (soundLevel > maxSound) {
        maxSound = soundLevel
    }
})

input.onButtonPressed(Button.A, function () {
    basic.showNumber(maxSound)
})
input.onButtonPressed(Button.B, function () {
    basic.showNumber(input.soundLevelDb())
})
