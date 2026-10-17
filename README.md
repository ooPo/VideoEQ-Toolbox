# VideoEq Toolbox

VideoEq Toolbox is a simple command-line program for controlling VideoEq
external video colour processors, including the VideoEq MX.

VideoEq devices (made by X-Vue, LLC) sit between a video source and a display
and apply colour correction in hardware: a colour management system (CMS)
table and a 10-bit 3D lookup table (LUT). This tool lets you read, write, and
reset those tables, switch profiles, adjust device settings, and query device
information from the command line.

The tool is a single C++ program that talks to the device over USB through
X-Vue's vendor SDK.

## Requirements

- Windows
- A VideoEq device connected via USB
- MinGW with G++ 4.6.2 (see [Building](#building))

X-Vue, LLC provides a free SDK on their website (http://videoeq.com/). The
SDK is distributed as precompiled binaries only, and will only link with
MinGW G++ 4.6.2 — no other toolchain works. A copy of the SDK is bundled in
`source/SDK/`.

## Building

1. Install MinGW as normal.

2. Pin the compiler to G++ 4.6.2:

   ```
   mingw-get upgrade --recursive "gcc<4.7.*" "g++<4.7.*"
   ```

3. Build from the `source/` directory:

   ```
   make clean && make
   ```

   This produces `source/videoeq-toolbox.exe`.

## Usage

```
videoeq-toolbox.exe <module> <command> [arguments]
```

A connected VideoEq is required at runtime. If the tool cannot connect, it
prints an error and the usage text and exits with a non-zero status. On
success it exits with 0; on any failure or unrecognized command it exits with
255.

### CONFIG

- `config reset` — disable deep color force and HDCP force
- `config deepColorForce <enable|disable>` — force deep color on or off
- `config hdcpForce <enable|disable>` — force HDCP on or off

### CMS

- `cms reset` — reset the CMS table to neutral (all 1.0) and push it to the device
- `cms load <hsv|rgb> <filename.csv>` — load a CMS file and push it to the device
- `cms save <hsv|rgb> <filename.csv>` — pull the current CMS from the device and save it to a file

### LUT

- `lut reset` — reset the LUT to identity and push it to the device
- `lut load <filename.csv>` — load a LUT file and push it to the device
- `lut save <filename.csv>` — pull the current LUT from the device and save it to a file

### PROFILE

- `profile get` — print the active profile index
- `profile reset` — set profile 0
- `profile set <index>` — set the active profile (0–22)

### RASTER

- `raster reset` — turn off the raster window
- `raster set <input|output> <red> <green> <blue>` — set the colour of the input or output raster window (0–1023 per channel)

### INFO

- `info` — print device information (model, manufacturer, firmware, hardware, serial number)

## File formats

Both file types are CSV with CRLF line endings and a `, ` (comma + space)
separator.

- **CMS files**: 6 rows (red, green, blue, cyan, magenta, yellow) × 3 columns.
  Columns are hue, saturation, value (HSV) or red, green, blue (RGB).
  Floating point values, 0.0–1.0.
- **LUT files**: 1024 rows × 3 columns (red, green, blue). Integer values,
  0–1023.

## Notes

- Profile indices: 1–4 are luminance-only, 17–22 are RGB/CMS. 17 is
  recommended.
- `cms save` / `lut save` write files with CRLF endings; the loaders also
  accept LF-only files.

## Testing

The test suite builds and runs without hardware, without the SDK libraries,
and on any platform (including Linux):

```
make -C test
./test/test-toolbox.exe
```

Exit code 0 means all tests pass. The suite compiles the real `cms`, `lut`,
`profile`, `parse`, and `info` sources against a stub `VideoEq`
implementation (`test/test-toolbox.cpp`), so file-loading, parsing, and
argument-handling logic is exercised without a device.

## Project layout

```
source/            tool sources (one .cpp/.h pair per module)
source/SDK/        vendor SDK (precompiled binaries — do not modify)
test/              test suite
```

## License

BSD-3-Clause — see `LICENSE.txt`.