basic.forever(function () {
    let dbOriginal = input.soundLevelDbOriginal()
    let dbFinal = input.soundLevelDb()
    serial.writeLine("" + dbOriginal + ", " + dbFinal)
    basic.pause(100)
})
