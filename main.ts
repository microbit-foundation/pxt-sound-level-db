basic.forever(function () {
    let dbOriginal = input.soundLevelDbOriginal()
    let dbFinal = input.soundLevelDb()
    serial.writeLine("" + dbOriginal + ", " + dbFinal)
    basic.pause(100)
})
input.onButtonPressed(Button.A, function () {
    basic.showNumber(input.soundLevelDb())
})
