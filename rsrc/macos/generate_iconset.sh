#!/bin/zsh

mkdir -p Lodestone.iconset

rsvg-convert -h 16 icon.svg > Lodestone.iconset/icon_16x16.png
rsvg-convert -h 32 icon.svg > Lodestone.iconset/icon_16x16@2x.png
rsvg-convert -h 32 icon.svg > Lodestone.iconset/icon_32x32.png
rsvg-convert -h 64 icon.svg > Lodestone.iconset/icon_32x32@2x.png
rsvg-convert -h 128 icon.svg > Lodestone.iconset/icon_128x128.png
rsvg-convert -h 256 icon.svg > Lodestone.iconset/icon_128x128@2x.png
rsvg-convert -h 256 icon.svg > Lodestone.iconset/icon_256x256.png
rsvg-convert -h 512 icon.svg > Lodestone.iconset/icon_256x256@2x.png
rsvg-convert -h 512 icon.svg > Lodestone.iconset/icon_512x512.png
rsvg-convert -h 1024 icon.svg > Lodestone.iconset/icon_512x512@2x.png

iconutil -c icns Lodestone.iconset