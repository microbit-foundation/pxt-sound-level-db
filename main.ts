let maxSound = 0
let soundLevelDb = 0
let soundLevel8bit = 0
basic.forever(function () {
    soundLevelDb = input.soundLevelDb()
    soundLevel8bit = input.soundLevel()
    serial.writeLine("" + soundLevelDb + "; " + soundLevel8bit)
    led.plotBarGraph(
    Math.map(soundLevelDb, 35, 100, 0, 25),
    25
    )
    if (soundLevelDb > maxSound) {
        maxSound = soundLevelDb
    }
})

input.onButtonPressed(Button.A, function () {
    basic.showNumber(maxSound)
})
input.onButtonPressed(Button.B, function () {
    basic.showNumber(input.soundLevelDb())
})
