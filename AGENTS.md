# AGENTS.md

CLI tool for controlling VideoEq external video colour processors (e.g. VideoEq MX). Single C++ program; all code lives in `source/`.

## Build

- Windows only (MinGW). The vendor SDK in `source/SDK/` is precompiled binaries that only link with G++ 4.6.2 — see `README.md` for setup.
- `make clean && make` in `source/` → `videoeq-toolbox.exe`. `clean` removes the `.exe` and all `.o` files.
- The Makefile compiles every `*.cpp` under `source/` (via `find`), so a new `.cpp` placed there is picked up automatically.
- No CI or typecheck configured. Code style is enforced with `clang-format` (see Style).

## Testing

- `make -C test` → `test/test-toolbox.exe`; run it, exit code 0 = all pass.
- Tests compile the real `cms`/`lut`/`profile`/`parse`/`info` sources against a stub `VideoEq` (`test/test-toolbox.cpp`), so they need no hardware and no SDK libraries — they build on Linux as well as Windows.
- When changing `source/*.cpp` file-IO or argument-parsing logic, add/extend cases in `test/test-toolbox.cpp` and run the suite.

## Structure

- `source/videoeq-toolbox.cpp` — `main()`; parses `videoeq-toolbox.exe <module> <command> [args]` and dispatches to one struct per module.
- One `.cpp`/`.h` pair per module: `config`, `cms`, `lut`, `profile`, `raster`, `info`; `parse` holds shared argument-parsing helpers (used by the app and the tests).
- `source/SDK/` — vendor SDK (`VideoEq.h`, `libVideoEq.a`, `SiUSBXp.lib`). Do not modify.
- A physical VideoEq connected via USB is required at runtime. If `connect()` fails, the program prints a connection error plus usage and exits non-zero; there is no offline/dry-run mode.

## CSV file formats (parsed in `cms.cpp` / `lut.cpp`)

- Files use CRLF endings (the tool writes literal `\r\n`); the parser also tolerates LF-only files.
- Separator is `, ` (comma + space).
- CMS: 6 rows (red, green, blue, cyan, magenta, yellow) × 3 float columns, 0.0–1.0 (HSV or RGB).
- LUT: 1024 rows × 3 uint16 columns, 0–1023.

## Gotchas

- Profile indices: 1–4 are luminance-only, 17–22 are RGB/CMS (17 recommended). `profile reset` sets profile 0.
- Exit code: 0 on success, -1 (255) on failure or usage.

## Style

- C++98: no C++11 features, `#pragma once` in headers.
- K&R style enforced by `clang-format` (`.clang-format` at repo root): attached braces, no spaces inside parentheses or brackets, 2-space indent, right-aligned pointers, LF line endings.
- Format with `make -C source fmt` / `make -C test fmt`; check with `make -C source lint` / `make -C test lint` (`--dry-run -Werror`). `source/SDK/` is excluded from both.