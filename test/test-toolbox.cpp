//
// test-toolbox.cpp
// by Naomi Peori (naomi@peori.ca)
//
// Test suite for the toolbox modules. Compiles the real cms/lut/profile/parse/info
// sources against a stub VideoEq implementation, so it builds and runs
// without hardware and without the Windows-only SDK libraries.
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../source/SDK/VideoEq.h"
#include "../source/cms.h"
#include "../source/info.h"
#include "../source/lut.h"
#include "../source/parse.h"
#include "../source/profile.h"

//
// Stub VideoEq Implementation
//

VideoEq::VideoEq() : m_privates(0) {}
VideoEq::~VideoEq() {}
VideoEq::VEqError VideoEq::connect(bool readData) {
  (void)readData;
  return NoError;
}
VideoEq::VEqError VideoEq::disconnect() { return NoError; }
void VideoEq::veqToHSV(VEqHsv (&hsv)[6], uint8_t *table) {
  (void)hsv;
  (void)table;
}
void VideoEq::veqToRGB(VEqRgb (&rgb)[6], uint8_t *table) {
  (void)rgb;
  (void)table;
}
void VideoEq::hsvToVEq(uint8_t *table, VEqHsv (&hsv)[6]) {
  (void)table;
  (void)hsv;
}
void VideoEq::rgbToVEq(uint8_t *table, VEqRgb (&rgb)[6]) {
  (void)table;
  (void)rgb;
}
VideoEq::VEqError VideoEq::setCurrentCms(uint8_t *table, VEqCb_t *cbp) {
  (void)table;
  (void)cbp;
  return NoError;
}
VideoEq::VEqError VideoEq::getCurrentCms(uint8_t *table, VEqCb_t *cbp) {
  (void)table;
  (void)cbp;
  return NoError;
}
VideoEq::VEqError VideoEq::setCurrentLut(uint16_t *red, uint16_t *green, uint16_t *blue, VEqCb_t *cbp) {
  (void)red;
  (void)green;
  (void)blue;
  (void)cbp;
  return NoError;
}
VideoEq::VEqError VideoEq::getCurrentLut(uint16_t *red, uint16_t *green, uint16_t *blue, VEqCb_t *cbp) {
  (void)red;
  (void)green;
  (void)blue;
  (void)cbp;
  return NoError;
}
VideoEq::VEqError VideoEq::setCurrentProfile(unsigned profile) { return (profile <= 4) ? NoError : InvalidProfile; }
VideoEq::VEqError VideoEq::getCurrentProfile(unsigned &profile) {
  profile = 17;
  return NoError;
}
VideoEq::VEqError VideoEq::getModel(Model &m) {
  m = Model_Mx;
  return NoError;
}
VideoEq::VEqError VideoEq::getFirmwareVersion(const char *&v) {
  v = "1.2.3";
  return NoError;
}
VideoEq::VEqError VideoEq::getHardwareVersion(uint8_t &hw) {
  hw = 2;
  return NoError;
}
VideoEq::VEqError VideoEq::getSerialNumber(const char *&v) {
  v = "SN12345";
  return NoError;
}
VideoEq::VEqError VideoEq::getManufacturer(const char *&mfg) {
  mfg = "X-Vue";
  return NoError;
}

//
// Test Helpers
//

static int failures = 0;

void check(bool condition, const char *name) {
  if (condition) {
    printf("PASS: %s\n", name);
  } else {
    printf("FAIL: %s\n", name);
    failures++;
  }
}

void writeTestFile(const char *filename, const char *contents) {
  FILE *file = fopen(filename, "w");

  if (file) {
    fputs(contents, file);
    fclose(file);
  }
}

//
// CMS Tests
//

void testCms() {
  const char *validFile = "test_cms_valid.csv";
  const char *truncatedFile = "test_cms_truncated.csv";
  const char *extraFile = "test_cms_extra.csv";
  const char *malformedFile = "test_cms_malformed.csv";
  const char *lfFile = "test_cms_lf.csv";

  writeTestFile(validFile, "0.500000, 0.250000, 0.750000\r\n0.2, 0.3, 0.4\r\n0.3, 0.4, 0.5\r\n0.4, 0.5, 0.6\r\n0.5, 0.6, 0.7\r\n0.100000, 0.9, 0.8\r\n");
  writeTestFile(truncatedFile, "0.5, 0.25, 0.75\r\n0.2, 0.3, 0.4\r\n0.3, 0.4, 0.5\r\n");
  writeTestFile(extraFile, "0.5, 0.25, 0.75\r\n0.2, 0.3, 0.4\r\n0.3, 0.4, 0.5\r\n0.4, 0.5, 0.6\r\n0.5, 0.6, 0.7\r\n0.1, 0.9, 0.8\r\n0.9, 0.9, 0.9\r\n");
  writeTestFile(malformedFile, "0.5, 0.25, 0.75\r\nabc, 0.3, 0.4\r\n0.3, 0.4, 0.5\r\n0.4, 0.5, 0.6\r\n0.5, 0.6, 0.7\r\n0.1, 0.9, 0.8\r\n");
  writeTestFile(lfFile, "0.5, 0.25, 0.75\n0.2, 0.3, 0.4\n0.3, 0.4, 0.5\n0.4, 0.5, 0.6\n0.5, 0.6, 0.7\n0.1, 0.9, 0.8\n");

  {
    CMS_t cms;

    check(cms.load(validFile), "cms: valid CRLF file loads");
    check(cms.cmsTable.raw[0][0] == 0.5f && cms.cmsTable.raw[0][1] == 0.25f && cms.cmsTable.raw[0][2] == 0.75f, "cms: row 0 values parsed correctly");
    check(cms.cmsTable.raw[5][0] == 0.1f && cms.cmsTable.raw[5][1] == 0.9f && cms.cmsTable.raw[5][2] == 0.8f, "cms: row 5 values parsed correctly");
  }

  {
    CMS_t cms;
    check(!cms.load(truncatedFile), "cms: truncated file rejected");
  }

  {
    CMS_t cms;
    check(!cms.load(extraFile), "cms: extra row rejected");
  }

  {
    CMS_t cms;
    check(!cms.load(malformedFile), "cms: malformed row rejected");
  }

  {
    CMS_t cms;
    check(cms.load(lfFile), "cms: LF-only file still loads");
  }

  {
    CMS_t cms;
    check(!cms.load("test_cms_missing.csv"), "cms: missing file rejected");
  }

  {
    CMS_t cms;
    cms.reset();
    check(cms.save(validFile), "cms: save round-trips to CRLF file");

    CMS_t reloaded;
    check(reloaded.load(validFile), "cms: saved file reloads");
    check(reloaded.cmsTable.raw[2][1] == 1.0f, "cms: saved values survive round-trip");
  }

  remove(validFile);
  remove(truncatedFile);
  remove(extraFile);
  remove(malformedFile);
  remove(lfFile);
}

//
// LUT Tests
//

void testLut() {
  char validContents[1024 * 20];
  char truncatedContents[100 * 20];
  char extraContents[1025 * 20];
  int offset;

  offset = 0;
  for (int loop = 0; loop < 1024; loop++) {
    offset += sprintf(validContents + offset, "%d, %d, %d\r\n", loop, (loop * 2) % 1024, (loop * 3) % 1024);
  }

  offset = 0;
  for (int loop = 0; loop < 100; loop++) {
    offset += sprintf(truncatedContents + offset, "%d, %d, %d\r\n", loop, (loop * 2) % 1024, (loop * 3) % 1024);
  }

  strcpy(extraContents, validContents);
  sprintf(extraContents + strlen(extraContents), "1024, 0, 0\r\n");

  writeTestFile("test_lut_valid.csv", validContents);
  writeTestFile("test_lut_truncated.csv", truncatedContents);
  writeTestFile("test_lut_extra.csv", extraContents);

  {
    LUT_t lut;

    check(lut.load("test_lut_valid.csv"), "lut: valid CRLF file loads");
    check(lut.lutTable.r[100] == 100 && lut.lutTable.g[100] == 200 && lut.lutTable.b[100] == 300, "lut: row 100 values parsed correctly");
    check(lut.lutTable.r[1023] == 1023 && lut.lutTable.g[1023] == (1023 * 2) % 1024 && lut.lutTable.b[1023] == (1023 * 3) % 1024, "lut: row 1023 values parsed correctly");
  }

  {
    LUT_t lut;
    check(!lut.load("test_lut_truncated.csv"), "lut: truncated file rejected");
  }

  {
    LUT_t lut;
    check(!lut.load("test_lut_extra.csv"), "lut: extra row rejected");
  }

  {
    LUT_t lut;
    lut.reset();
    check(lut.save("test_lut_valid.csv"), "lut: save round-trips to CRLF file");

    LUT_t reloaded;
    check(reloaded.load("test_lut_valid.csv"), "lut: saved file reloads");
    check(reloaded.lutTable.r[512] == 512 && reloaded.lutTable.g[512] == 512 && reloaded.lutTable.b[512] == 512, "lut: saved values survive round-trip");
  }

  remove("test_lut_valid.csv");
  remove("test_lut_truncated.csv");
  remove("test_lut_extra.csv");
}

//
// Profile Tests
//

void testProfile() {
  VideoEq videoEq;
  PROFILE_t profile;

  check(profile.set(&videoEq, 2), "profile: valid index accepted");
  check(!profile.set(&videoEq, 17), "profile: invalid index rejected with message");
  check(profile.reset(&videoEq), "profile: reset accepted");

  {
    unsigned int index = 0;
    check(profile.get(&videoEq, &index) && index == 17, "profile: get returns current index");
  }
}

//
// Info Tests
//

void testInfo() {
  VideoEq videoEq;
  INFO_t info;

  check(info.print(&videoEq), "info: print succeeds");
}

//
// Parse Tests
//

void testParse() {
  unsigned int value = 0;

  check(parseArgument("5", &value, 22) && value == 5, "parse: '5' -> 5");
  check(parseArgument("22", &value, 22) && value == 22, "parse: '22' -> 22 (max ok)");
  check(!parseArgument("23", &value, 22), "parse: '23' rejected (over max)");
  check(!parseArgument("abc", &value, 22), "parse: 'abc' rejected");
  check(!parseArgument("-1", &value, 22), "parse: '-1' rejected");
  check(!parseArgument("12abc", &value, 22), "parse: '12abc' rejected");
  check(!parseArgument("", &value, 22), "parse: '' rejected");
  check(parseArgument("1023", &value, 1023) && value == 1023, "parse: '1023' -> 1023 (max ok)");
  check(!parseArgument("1024", &value, 1023), "parse: '1024' rejected (over max)");
}

//
// Main
//

int main() {
  testCms();
  testLut();
  testProfile();
  testParse();
  testInfo();

  printf("\n%s (%d failures)\n", failures ? "FAILED" : "ALL TESTS PASSED", failures);
  return failures ? 1 : 0;
}