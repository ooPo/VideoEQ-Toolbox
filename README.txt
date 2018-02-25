=================
 VIDEOEQ TOOLBOX
=================

  VideoEq Toolbox is a simple command-line program for controlling VideoEq
  external video colour processors, including the VideoEq MX.

  X-Vue, LLC provides a free SDK on their website (http://videoeq.com/).
  Unfortunately, this SDK is in binary form only and will only link with
  a very specific version of MinGW G++ (4.6.2).

=======
 USAGE
=======

  videoeq-toolbox.exe <module> <command> [arguments]

  CONFIG:

    config reset
    config deepColourForce [enable|disable]
    config hdcpForce [enable|disable]

  CMS:

    cms reset
    cms load <hsv|rgb> <filename.csv>
    cms save <hsv|rgb> <filename.csv>

  LUT:

    lut reset
    lut load <filename.csv>
    lut save <filename.csv>

  PROFILE:

    profile get
    profile set <index>

  RASTER:

    raster reset
    raster set <input|output> <red> <green> <blue>

=======
 NOTES
=======

- CMS files:
  - Cols: hue, saturation, value
  - Rows: red, green, blue, cyan, magenta, yellow
  - Floating point values. (0.0 - 1.0)

- LUT files:
  - Cols: red, green, blue
  - Rows: 1024
  - Integer values. (0 - 1023)

- Profile
  - 4x Luminance-only: 1, 2, 3, 4
  - 6x RGB/CMS: 17, 18, 19, 20, 21, 22
    - Recommend using #17.

- Raster:
  - Colors: red, green, blue.
  - Integer values. (0 - 1023)
