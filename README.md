# sound level (dB) block

## Block Usage

This extension adds one block to the "Input ... more" section.

The ``||input.soundLevelDb||`` block returns the level of sound detected by the microphone in decibel (dB) units.

```blocks
basic.showNumber(input.soundLevelDb())
```

This block is compatible with micr:bit V2 only, if the block is used with a micro:bit V1 board the 927 error will scroll on the screen.

## Use as Extension

This repository can be added as an **extension** in MakeCode.

* open [https://makecode.microbit.org](https://makecode.microbit.org)
* click on **New Project**
* click on **Extensions** under the gearwheel menu
* search for **Sound Level in decibels** and import

#### Metadata (used for search, rendering)

* for PXT/
<script src="https://makecode.com/gh-pages-embed.js"></script><script>makeCodeRender("{{ site.makecode.home_url }}", "{{ site.github.owner_name }}/{{ site.github.repository_name }}");</script>
