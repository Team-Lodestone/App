#!/bin/zsh

mkdir -p Lodestone.iconset

rsvg-convert -h 16 ../assets/icons/icon.svg > Lodestone.iconset/icon_16x16.png
rsvg-convert -h 32 ../assets/icons/icon.svg > Lodestone.iconset/icon_16x16@2x.png
rsvg-convert -h 32 ../assets/icons/icon.svg > Lodestone.iconset/icon_32x32.png
rsvg-convert -h 64 ../assets/icons/icon.svg > Lodestone.iconset/icon_32x32@2x.png
rsvg-convert -h 64 ../assets/icons/icon.svg > Lodestone.iconset/icon_64x64.png
rsvg-convert -h 128 ../assets/icons/icon.svg > Lodestone.iconset/icon_64x64@2x.png
rsvg-convert -h 128 ../assets/icons/icon.svg > Lodestone.iconset/icon_128x128.png
rsvg-convert -h 256 ../assets/icons/icon.svg > Lodestone.iconset/icon_128x128@2x.png
rsvg-convert -h 256 ../assets/icons/icon.svg > Lodestone.iconset/icon_256x256.png
rsvg-convert -h 512 ../assets/icons/icon.svg > Lodestone.iconset/icon_256x256@2x.png
rsvg-convert -h 512 ../assets/icons/icon.svg > Lodestone.iconset/icon_512x512.png
rsvg-convert -h 1024 ../assets/icons/icon.svg > Lodestone.iconset/icon_512x512@2x.png

iconutil -c icns Lodestone.iconset
mv Lodestone.iconset/* ../assets/icons/
rm -rf Lodestone.iconset