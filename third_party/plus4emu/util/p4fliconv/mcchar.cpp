
// p4fliconv: high resolution interlaced FLI converter utility
// Copyright (C) 2007-2008 Istvan Varga <istvanv@users.sourceforge.net>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Plus/4 program files generated by this utility are not covered by the
// GNU General Public License, and can be used, modified, and distributed
// without any restrictions.

#include "p4fliconv.hpp"
#include "dither.hpp"
#include "imageconv.hpp"
#include "prgdata.hpp"
#include "mcchar.hpp"

namespace Plus4FLIConv {

  P4FLI_MultiColorChar::Line128::Line128()
  {
    buf = new float[128];
    for (size_t i = 0; i < 128; i++)
      buf[i] = 0.0f;
  }

  P4FLI_MultiColorChar::Line128::Line128(const Line128& r)
  {
    buf = new float[128];
    for (size_t i = 0; i < 128; i++)
      buf[i] = r.buf[i];
  }

  P4FLI_MultiColorChar::Line128::~Line128()
  {
    delete[] buf;
  }

  P4FLI_MultiColorChar::Line128&
      P4FLI_MultiColorChar::Line128::operator=(const Line128& r)
  {
    for (size_t i = 0; i < 128; i++)
      buf[i] = r.buf[i];
    return (*this);
  }

  void P4FLI_MultiColorChar::Line128::clear()
  {
    for (size_t i = 0; i < 128; i++)
      buf[i] = 0.0f;
  }

  // --------------------------------------------------------------------------

  P4FLI_MultiColorChar::Image128x64::Image128x64()
  {
    buf = new Line128[64];
  }

  P4FLI_MultiColorChar::Image128x64::Image128x64(const Image128x64& r)
  {
    buf = new Line128[64];
    for (size_t i = 0; i < 64; i++)
      buf[i] = r.buf[i];
  }

  P4FLI_MultiColorChar::Image128x64&
      P4FLI_MultiColorChar::Image128x64::operator=(const Image128x64& r)
  {
    for (size_t i = 0; i < 64; i++)
      buf[i] = r.buf[i];
    return (*this);
  }

  P4FLI_MultiColorChar::Image128x64::~Image128x64()
  {
    delete[] buf;
  }

  // --------------------------------------------------------------------------

  P4FLI_MultiColorChar::P4FLI_MultiColorChar()
    : monitorGamma(2.2),
      ditherLimit(0.25),
      ditherScale(0.95),
      ditherMode(1),
      luminance1BitMode(false),
      ditheredImage((int *) 0)
  {
    try {
      ditheredImage = new int[128 * 64];
      for (int i = 0; i < (128 * 64); i++)
        ditheredImage[i] = 0;
    }
    catch (...) {
      if (ditheredImage)
        delete[] ditheredImage;
      throw;
    }
  }

  P4FLI_MultiColorChar::~P4FLI_MultiColorChar()
  {
    delete[] ditheredImage;
  }

  void P4FLI_MultiColorChar::pixelStoreCallback(void *userData, int xc, int yc,
                                                float y, float u, float v)
  {
    (void) u;
    (void) v;
    P4FLI_MultiColorChar&  this_ =
        *(reinterpret_cast<P4FLI_MultiColorChar *>(userData));
    this_.resizedImage[yc >> 1][xc >> 2] += (y * 0.125f);
  }

  void P4FLI_MultiColorChar::checkParameters()
  {
    limitValue(monitorGamma, 1.0, 4.0);
    limitValue(ditherLimit, 0.0, 2.0);
    limitValue(ditherScale, 0.0, 1.0);
    limitValue(ditherMode, -1, 5);
  }

  void P4FLI_MultiColorChar::ditherLine(long yc)
  {
    if (ditherMode < 0) {
      // no dithering
      for (long xc = 0L; xc < 128L; xc++) {
        // find the palette color nearest the original pixel
        float   y0_ = resizedImage[yc].getPixel(xc);
        int     c0 = 0;
        double  minErr = 1000000.0;
        for (int i = 0; i < 4; i++) {
          double  err = calculateErrorSqr(errorYTable[colorTable[i]], y0_);
          if (err < minErr) {
            c0 = i;
            minErr = err;
          }
        }
        ditheredImage[yc * 128L + xc] = c0;
      }
      return;
    }
    if (ditherMode < 2) {
      // ordered dithering
      const int *ditherTable_ = &(ditherTable[0]);
      if (ditherMode == 0)
        ditherTable_ = &(ditherTable_Bayer[0]);
      for (long xc = 0L; xc < 128L; xc++) {
        float   y_ = resizedImage[yc].getPixel(xc);
        float   y = float(std::pow(double(y_), (1.0 / 0.704)));
        int     li0 = 0;
        while (y > ditherYTable[colorTable[li0 + 1]] && li0 < 3)
          li0++;
        int     li1 = li0 + 1;
        if (colorTable[li0] != colorTable[li1]) {
          float   l0 = ditherYTable[colorTable[li0]];
          float   l1 = ditherYTable[colorTable[li1]];
          float   l0_ = errorYTable[colorTable[li0]];
          float   l1_ = errorYTable[colorTable[li1]];
          if (calculateError(calculateError(y_, l0_), calculateError(y_, l1_))
              >= ditherLimit) {
            if (calculateError(y_, l0_) > calculateError(y_, l1_))
              li0 = li1;
          }
          else {
            float   f = (y - l0) / (l1 - l0);
            if (ditherPixelValue(xc, yc, f, ditherTable_))
              li0 = li1;
          }
        }
        ditheredImage[yc * 128L + xc] = li0;
      }
      return;
    }
    // error diffusion dithering
    for (long xc = 0L; xc < 128L; xc++) {
      if (yc & 1L)
        xc = 127L - xc;
      // find the palette color nearest the original pixel
      float   y0_ = resizedImage[yc].getPixel(xc);
      float   y0 = float(std::pow(double(y0_), (1.0 / 0.704)));
      int     c0 = 0;
      double  minErr = 1000000.0;
      for (int i = 0; i < 4; i++) {
        double  err = calculateErrorSqr(errorYTable[colorTable[i]], y0_);
        if (err < minErr) {
          c0 = i;
          minErr = err;
        }
      }
      // find the palette color nearest the original pixel with error added
      float   y = y0 + ditherErrorImage[yc].getPixel(xc);
      y = (y > ditherYTable[colorTable[0]] ?
           (y < ditherYTable[colorTable[3]] ? y : ditherYTable[colorTable[3]])
           : ditherYTable[colorTable[0]]);
      int     c = 0;
      minErr = 1000000.0;
      for (int i = 0; i < 4; i++) {
        double  err = calculateErrorSqr(ditherYTable[colorTable[i]], y);
        if (err < minErr) {
          c = i;
          minErr = err;
        }
      }
      if (calculateError(
              std::sqrt(calculateErrorSqr(errorYTable[colorTable[c]], y0_)),
              std::sqrt(calculateErrorSqr(errorYTable[colorTable[c0]], y0_)))
          < ditherLimit) {
        ditheredImage[yc * 128L + xc] = c;
      }
      else {
        ditheredImage[yc * 128L + xc] = c0;
      }
      y = y0 + ((y - y0) * float(ditherScale));
      float   errY = y - ditherYTable[colorTable[c]];
      const int *errMultTbl = &(ditherTable_FloydSteinberg[0]);
      switch (ditherMode) {
      case 3:
        errMultTbl = &(ditherTable_Jarvis[0]);
        break;
      case 4:
        errMultTbl = &(ditherTable_Stucki[0]);
        break;
      case 5:
        errMultTbl = &(ditherTable_Sierra2[0]);
        break;
      }
      for (int i = 0; i < 12; i++) {
        if (errMultTbl[i + 1] == 0)
          continue;
        long    yc_ = yc + ((i + 3) / 5);
        long    xc_ = ((i + 3) % 5) - 2;
        xc_ = ((yc & 1L) == 0L ? (xc + xc_) : (xc - xc_));
        if (yc_ >= 0L && yc_ < 64L && xc_ >= 0L && xc_ < 128L) {
          float   errMult = float(errMultTbl[i + 1]) / float(errMultTbl[0]);
          ditherErrorImage[yc_].setPixel(
              xc_, ditherErrorImage[yc_].getPixel(xc_) + (errY * errMult));
        }
      }
      if (yc & 1L)
        xc = 127L - xc;
    }
  }

  bool P4FLI_MultiColorChar::processImage(PRGData& prgData,
                                          unsigned int& prgEndAddr,
                                          const char *infileName,
                                          YUVImageConverter& imgConv,
                                          Plus4Emu::ConfigurationDB& config)
  {
    try {
      monitorGamma = config["monitorGamma"];
      ditherLimit = config["ditherLimit"];
      ditherScale = config["ditherDiffusion"];
      ditherMode = config["ditherMode"];
      luminance1BitMode = config["luminance1BitMode"];
      checkParameters();
      for (int i = 0; i < 9; i++) {
        float   u = 0.0f;
        float   v = 0.0f;
        FLIConverter::convertPlus4Color((i > 0 ? (((i - 1) << 4) | 1) : 0),
                                        ditherYTable[i], u, v,
                                        monitorGamma * 0.625);
        FLIConverter::convertPlus4Color((i > 0 ? (((i - 1) << 4) | 1) : 0),
                                        errorYTable[i], u, v,
                                        monitorGamma * 0.44);
      }
      prgData.setConversionType(8);
      prgData.clear();
      for (int yc = 0; yc < 64; yc++) {
        resizedImage[yc].clear();
        ditherErrorImage[yc].clear();
      }
      imgConv.setImageSize(512, 128);
      imgConv.setPixelAspectRatio(1.0f);
      imgConv.setPixelStoreCallback(&pixelStoreCallback, (void *) this);
      imgConv.convertImageFile(infileName);
      progressMessage("Calculating FLI data");
      setProgressPercentage(0);
      for (int yc = 0; yc < 64; yc++) {
        for (int xc = 0; xc < 128; xc++) {
          resizedImage[yc].setPixel(
              xc, float(std::pow(double(resizedImage[yc].getPixel(xc)),
                                 0.704)));
        }
      }
      // find optimal palette
      int     l0 = 8;
      int     l1 = 0;
      int     l2 = 0;
      int     l3 = 0;
      if (luminance1BitMode) {
        l0 = 0;
        l1 = 8;
        l2 = 8;
        l3 = 8;
      }
      else if (ditherMode >= 0) {
        // dithering enabled
        for (int yc = 0; yc < 64; yc++) {
          for (int xc = 0; xc < 128; xc++) {
            float   y = resizedImage[yc].getPixel(xc);
            while (y < errorYTable[l0] && l0 > 0)
              l0--;
            while (y > errorYTable[l3] && l3 < 8)
              l3++;
          }
        }
        double  bestErr = 1000000.0;
        int     bestL1 = (l0 < l3 ? (l0 + 1) : l0);
        int     bestL2 = (bestL1 < l3 ? (bestL1 + 1) : bestL1);
        for (l1 = l0 + 1; l1 < l3; l1++) {
          for (l2 = l1 + 1; l2 < l3; l2++) {
            float   yTable_1[4];
            float   yTable_2[13];
            yTable_1[0] = errorYTable[l0];
            yTable_1[1] = errorYTable[l1];
            yTable_1[2] = errorYTable[l2];
            yTable_1[3] = errorYTable[l3];
            for (int i = 0; i < 12; i++) {
              float   f = float(i & 3) * 0.25f;
              yTable_2[i] = yTable_1[i >> 2]
                            + ((yTable_1[(i >> 2) + 1] - yTable_1[i >> 2]) * f);
            }
            yTable_2[12] = yTable_1[3];
            double  err = 0.0;
            for (int yc = 0; yc < 64; yc++) {
              for (int xc = 0; xc < 128; xc++) {
                float   y = resizedImage[yc].getPixel(xc);
                double  minErr2 = 1000000.0;
                for (int i = 0; i < 4; i++) {
                  double  err2 = calculateErrorSqr(yTable_1[i], y);
                  if (err2 < minErr2)
                    minErr2 = err2;
                }
                err += minErr2;
              }
            }
            for (int yc = 0; yc < 64; yc += 2) {
              for (int xc = 0; xc < 128; xc += 2) {
                float   y = resizedImage[yc].getPixel(xc);
                y = y + resizedImage[yc].getPixel(xc + 1);
                y = y + resizedImage[yc + 1].getPixel(xc);
                y = y + resizedImage[yc + 1].getPixel(xc + 1);
                y = y * 0.25f;
                double  minErr2 = 1000000.0;
                for (int i = 0; i < 13; i++) {
                  double  err2 = calculateErrorSqr(yTable_2[i], y);
                  if (err2 < minErr2)
                    minErr2 = err2;
                }
                err += (minErr2 * 2.0);
              }
            }
            if (err < bestErr) {
              bestL1 = l1;
              bestL2 = l2;
              bestErr = err;
            }
          }
        }
        l1 = bestL1;
        l2 = bestL2;
      }
      else {
        // dithering disabled
        double  bestErr = 1000000.0;
        int     bestL0 = 0;
        int     bestL1 = 0;
        int     bestL2 = 0;
        int     bestL3 = 0;
        float   yTable_1[4];
        for (l0 = 0; l0 <= 5; l0++) {
          yTable_1[0] = errorYTable[l0];
          for (l1 = l0 + 1; l1 <= 6; l1++) {
            yTable_1[1] = errorYTable[l1];
            for (l2 = l1 + 1; l2 <= 7; l2++) {
              yTable_1[2] = errorYTable[l2];
              for (l3 = l2 + 1; l3 <= 8; l3++) {
                yTable_1[3] = errorYTable[l3];
                double  err = 0.0;
                for (int yc = 0; yc < 64; yc++) {
                  for (int xc = 0; xc < 128; xc++) {
                    float   y = resizedImage[yc].getPixel(xc);
                    double  minErr2 = 1000000.0;
                    for (int i = 0; i < 4; i++) {
                      double  err2 = calculateErrorSqr(yTable_1[i], y);
                      if (err2 < minErr2)
                        minErr2 = err2;
                    }
                    err += minErr2;
                  }
                }
                if (err < bestErr) {
                  bestL0 = l0;
                  bestL1 = l1;
                  bestL2 = l2;
                  bestL3 = l3;
                  bestErr = err;
                }
              }
            }
          }
        }
        l0 = bestL0;
        l1 = bestL1;
        l2 = bestL2;
        l3 = bestL3;
      }
      colorTable[0] = l0;
      colorTable[1] = l1;
      colorTable[2] = l2;
      colorTable[3] = l3;
      // dither image to 4 colors
      for (int yc = 0; yc < 64; yc++)
        ditherLine(yc);
      colorTable[0] =
          (colorTable[0] > 0 ? (((colorTable[0] - 1) << 4) | 1) : 0);
      colorTable[1] =
          (colorTable[1] > 0 ? (((colorTable[1] - 1) << 4) | 1) : 0);
      colorTable[2] =
          (colorTable[2] > 0 ? (((colorTable[2] - 1) << 4) | 1) : 0);
      colorTable[3] =
          (colorTable[3] > 0 ? (((colorTable[3] - 1) << 4) | 1) : 0);
      setProgressPercentage(100);
      progressMessage("");
      {
        char    tmpBuf[64];
        std::sprintf(&(tmpBuf[0]), "Done, palette: %02X %02X %02X %02X",
                     (unsigned int) colorTable[0],
                     (unsigned int) colorTable[1],
                     (unsigned int) colorTable[2],
                     (unsigned int) colorTable[3]);
        progressMessage(&(tmpBuf[0]));
      }
      // write PRG output
      for (int yc = 0; yc < 64; yc++) {
        for (int xc = 0; xc < 128; xc++) {
          int     addr = ((xc >> 2) << 6) + yc + (0x6000 - 0x0FFF);
          unsigned char tmp = (unsigned char) (ditheredImage[(yc * 128) + xc]
                                               << ((3 - (xc & 3)) << 1));
          prgData[addr] = prgData[addr] | tmp;
        }
      }
      prgData[0x1100 - 0x0FFF] = (unsigned char) colorTable[0];
      prgData[0x1101 - 0x0FFF] = (unsigned char) colorTable[1];
      prgData[0x1102 - 0x0FFF] = (unsigned char) colorTable[2];
      prgData[0x1103 - 0x0FFF] = (unsigned char) colorTable[3];
      prgEndAddr = prgData.getImageDataEndAddress();
    }
    catch (...) {
      prgData[0] = 0x01;
      prgData[1] = 0x10;
      prgData[2] = 0x00;
      prgData[3] = 0x00;
      prgEndAddr = 0x1003U;
      progressMessage("");
      throw;
    }
    return true;
  }

}       // namespace Plus4FLIConv

