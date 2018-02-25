/***************************************************
 *
 * (C) Copyright Eric L. Hernes -- Thursday, October 14, 2013
 * (C) Copyright X-Vue, LLC.; Thursday, October 14, 2013
 *
 *
 */

#ifndef VIDEOEQ_H
#define VIDEOEQ_H

#ifdef RCS_INFO
static const char *VideoEq_h_rcsid[] = {
  "$EricH$",
  "$Id$",
};

static const char *VideoEq_h_copyright[] = {
  "(C) Copyright Eric L. Hernes -- Thursday, October 14, 2013",
  "(C) Copyright X-Vue, LLC.; Thursday, October 14, 2013",
};
#endif

static const unsigned skVEqProfEntrySz=(7*3+1);
static const unsigned skVEqColorspaceSz=(skVEqProfEntrySz*4);
static const unsigned skVEqDispProfileSz=(21*skVEqProfEntrySz)*4;

enum ColorSpace {
  CS_RGB,
  CS_422_601,
  CS_422_709,
  CS_444_601,
  CS_444_709,
};

struct VidInfo {
  unsigned width;
  unsigned height;
  unsigned interlacedP;
  double vFreq;
  double hFreq;
  unsigned pixelClock;
  struct {
    enum ColorSpace color;
    const char *sColor;
    uint8_t bitDepth;
    uint8_t validP;
    uint8_t hdcpP;
  } input;
  struct {
    enum ColorSpace color;
    const char *sColor;
    uint8_t bitDepth;
    uint8_t validP;
    uint8_t hdcpP;
    uint8_t status;
    uint8_t hdcp;
  } output;
  uint8_t aviInfoFrame[20];
  uint8_t vsInfoFrame[30];
};

struct VEqHsv {
  float hue;
  float sat;
  float val;
};

struct VEqRgb {
  float red;
  float green;
  float blue;
};

#ifdef __cplusplus

typedef bool (VEqCb_Method)(void *user, unsigned percentage, unsigned bytes, unsigned total);
struct VEqCb_t {
  VEqCb_Method *method;
  void *pointer;
};

class VideoEq {
public:
  VideoEq();
  ~VideoEq();
  /** Return values for several of the VideoEq methods
   */
  enum VEqError {
    NoError = 0,
    IoError = -1,
    NotConnected = -2,
    InvalidProfile = -3,
  };
  /** Enumeration for the various VideoEq models
   */
  enum Model {
    Model_None,
    Model_Basic,
    Model_CMS,
    Model_Pro,
    Model_Mx,
    Model_Post
  };
  /** The individual features that may be supported by a specific model.
   */
  enum Feature {
    Feature_EDID = 1,
    Feature_Force10Bit,
    Feature_LED,
    Feature_CMS,
    Feature_FastUpdate,
    Feature_HDCP
  };
  /** The VideoEq has two profile types, either a luminance only, or an RGB+CMS profile.
   */
  enum ProfileType {
    Prof_Luma = 0,
    Prof_RgbCms = 1<<4,
  };
  /** The VideoEq indices for colors in the RGB/HSV arrays
   */
  enum Color {
    kRed = 0,
    kGreen = 1,
    kBlue = 2,
    kCyan = 3,
    kMagenta = 4,
    kYellow = 5
  };
  /** Method to connect to the VideoEq.
   */
  VEqError connect(bool readData=true);

  /** Method to disconnect from the VideoEq.
   */
  VEqError disconnect();

  /** Returns the enumerated model of the VideoEq that is connected to the system.
   */
  VideoEq::VEqError getModel(Model &m);

  /** Returns the current firmware version on the VideoEq.
   */
  VideoEq::VEqError getFirmwareVersion(const char *&v);

  /** Returns the current hardware version on the VideoEq.
   */
  VideoEq::VEqError getHardwareVersion(uint8_t &hw);

  /** Returns the serial number of the VideoEq.
   */
  VideoEq::VEqError getSerialNumber(const char *&v);

  /** Returns the manufacturer of the VideoEq.
   */
  VideoEq::VEqError getManufacturer(const char *&mfg);

  /** Predicate method to determine if the attached VideoEq supports certain features.
   */
  bool hasFeature(Feature f);

  /** Returns the number of luminance profiles available on the current VideoEq.
   */
  unsigned getNumLuma();

  /** Returns the number of RGB+CMS profiles available on the VideoEq.
   */
  unsigned getNumRgbCms();

  /** Returns an identifier for the currently active profile.
   */
  VEqError getCurrentProfile(unsigned &profile);

  /** Sets the currently active profile.
   */
  VEqError setCurrentProfile(unsigned profile);

  /** Sets the specified Luma profile lookup table to the given values.
   * 'lut' must be an array of 1024 uint16_t's.  If "profile" refers to an RgbCms profile,
   * all three (r, g, b) tables are set to 'lut'
   */
  VEqError setLumaLut(unsigned profile, uint16_t *lut, VEqCb_t *cbp=0);

  /** Gets the specified Luma profile lookup table to the given values.
   * 'lut' must be an array of 1024 uint16_t's.  If 'profile' refers to an RgbCms profile,
   * an InvalidProfile error is returned.
   */
  VEqError getLumaLut(unsigned profile, uint16_t *lut, VEqCb_t *cbp=0);

  /** Sets the specified RGB profile lookup table to the given values.
   * 'red', 'green', and 'blue' must all be arrays of 1024 uint16_t's.  If 'profile'
   * refers to a LumaOnly profile, only the red table is used.
   */
  VEqError setRgbLut(unsigned profile, uint16_t *red, uint16_t *green, uint16_t *blue,
		     VEqCb_t *cbp=0);

  /** Gets the specified RGB profile lookup table to the given values.
   * 'red', 'green', and 'blue' must all be arrays of 1024 uint16_t's. If 'profile' refers
   * to a LumaOnly profile, table entries for all three tables are set to the same values.
   */
  VEqError getRgbLut(unsigned profile, uint16_t *red, uint16_t *green, uint16_t *blue,
		     VEqCb_t *cbp=0);

  /** Convenience method for setting the current lookup table.
   * If the current table is a 'Luma', only the 'red' array is used. Also forces
   * hardware re-fresh of the current profile.
   */
  VEqError setCurrentLut(uint16_t *red, uint16_t *green, uint16_t *blue,
			 VEqCb_t *cbp=0);

  /** Convenience method for getting the current lookup table.
   * If the current profile a "Luma Only", all three arrays are populated
   * with the same values.
   */
  VEqError getCurrentLut(uint16_t *red, uint16_t *green, uint16_t *blue,
			 VEqCb_t *cbp=0);

  /** size of the CMS table as stored on the VideoEq
   */
  static const unsigned kCmsSize = 224;
  /** Sets the CMS table for the given profile.
   */
  VEqError setCms(unsigned profile, uint8_t *table, VEqCb_t *cbp=0);

  /** Gets the CMS table for the given profile.
   */
  VEqError getCms(unsigned profile, uint8_t *table, VEqCb_t *cbp=0);

  /** Convenience method to set the current CMS table.  This method returns an error if the current table is "Luma Only"
   */
  VEqError setCurrentCms(uint8_t *table, VEqCb_t *cbp=0);

  /** Convenience method to get the current CMS table. This method returns an identity table if current table is "Luma Only"
   */
  VEqError getCurrentCms(uint8_t *table, VEqCb_t *cbp=0);


  /** Methods to convert between internal VideoEq representation and adjustable forms.
   */
  static void veqToHSV(VEqHsv (&hsv)[6], uint8_t *table);
  static void veqToRGB(VEqRgb (&rgb)[6], uint8_t *table);
  static void hsvToVEq(uint8_t *table, VEqHsv (&hsv)[6]);
  static void rgbToVEq(uint8_t *table, VEqRgb (&rgb)[6]);

  /***************************************************
   * Methods for the VideoEq Auto
   ***************************************************/

  VEqError setTargetColorspace(uint8_t (&rgb)[(skVEqProfEntrySz)*4]);
  VEqError getTargetColorspace(uint8_t (&rgb)[(skVEqProfEntrySz)*4]);

  VEqError setDisplayProfile(uint8_t *prof, unsigned n);
  VEqError getDisplayProfile(uint8_t *prof, unsigned n);

  VEqError doCalibration(unsigned state);

  /** Returns true/false depending on the current setting of the VideoEq's Force Deep Color switch.
   */
  bool getDeepColorForce();
  /** Sets or clears the VideoEq's Force Deep Color mode.
   */
  void setDeepColorForce(bool pred);

  /** Gets the state of the LED switch, true if LEDs are on, false if LEDs are off.
   */
  bool getLedsOn();
  /** Sets the state of the LED control.
   */
  void setLedsOn(bool pred);

  enum EdidHandling {
    EDID_Off = 0,
    EDID_Display = 1,
    EDID_VEQ = 2,
  };
  EdidHandling getEdidHandling();
  void setEdidHandling(EdidHandling e);

  VEqError readEdid(uint8_t (&edid)[256]);
  VEqError writeEdid(uint8_t (&edid)[256]);

  bool getHdcpForceOn();
  void setHdcpForceOn(bool pred);

  VEqError writeRegisters();
  VEqError writeHeader();

  void dumpRegisters();

  VEqError getVidInfo(VidInfo &vid);
  VEqError getEdid(uint8_t (&edid)[256]);
  VEqError setEdid(uint8_t (&edid)[256]);

  VEqError refreshIfCurrent(unsigned pid);

  VEqError readEProm(uint8_t (&eprom)[0x10000], VEqCb_t *cbp=0);
  VEqError writeEProm(uint8_t (&eprom)[0x10000], VEqCb_t *cbp=0);

  enum RasterWindow {
    RW_Off,
    RW_Input,
    RW_Output
  };
  VEqError setRasterWindow(RasterWindow rw, unsigned red, unsigned green, unsigned blue);

  void setReg(int dev, uint16_t reg, uint8_t val);
  void getReg(int dev, uint16_t reg, uint8_t &val);

  void bootloadMode();
  void resetMcu();
  VEqError resetFpga(bool pred);

  class VEqLLIO *getLLIO();
  class VeqHeader *getHeaderData();
  class VeqRegisters *getRegisters();
private:
  struct VEqPrivates *m_privates;
};
#endif // __cplusplus

#ifdef __cplusplus
extern "C" {
#endif
  typedef void CVideoEq;
  CVideoEq *newVideoEq();
  void deleteVideoEq(CVideoEq*);
  void VeqConnect(CVideoEq *vp);
  void VeqDisconnect(CVideoEq *vp);
  void VeqSetRaster(CVideoEq *vp, unsigned int, unsigned red, unsigned green, unsigned blue);
#ifdef __cplusplus
};
#endif // __cplusplus


#endif /* VIDEOEQ_H */

/*
 * Local Variables:
 * mode: C++
 * mode: font-lock
 * c-basic-offset: 2
 * tab-width: 8
 * compile-command: "bsdmake"
 * End:
 */

