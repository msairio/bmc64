/*
 * videoarch_c128.c
 *
 * Written by
 *  Randy Rossi <randy.rossi@gmail.com>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "videoarch_c128.h"

#include "emux_api.h"
#include "c128/c128.h"
#include "c128/c128mem.h"
#include "vicii.h"
#include "vdc/vdc.h"

static unsigned int default_color_palette[] = {
    0x00, 0x00, 0x00, 0xFD, 0xFE, 0xFC, 0xBE, 0x1A, 0x24, 0x30, 0xE6, 0xC6,
    0xB4, 0x1A, 0xE2, 0x1F, 0xD2, 0x1E, 0x21, 0x1B, 0xAE, 0xDF, 0xF6, 0x0A,
    0xB8, 0x41, 0x04, 0x6A, 0x33, 0x04, 0xFE, 0x4A, 0x57, 0x42, 0x45, 0x40,
    0x70, 0x74, 0x6F, 0x59, 0xFE, 0x59, 0x5F, 0x53, 0xFE, 0xA4, 0xA7, 0xA2,
};

static unsigned int vice_color_palette[] = {
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x68, 0x37, 0x2b, 0x70, 0xa4, 0xb2,
    0x6f, 0x3d, 0x86, 0x58, 0x8d, 0x43, 0x35, 0x28, 0x79, 0xb8, 0xc7, 0x6f,
    0x6f, 0x4f, 0x25, 0x43, 0x39, 0x00, 0x9a, 0x67, 0x59, 0x44, 0x44, 0x44,
    0x6c, 0x6c, 0x6c, 0x9a, 0xd2, 0x84, 0x6c, 0x5e, 0xb5, 0x95, 0x95, 0x95,
};

static unsigned int c64hq_color_palette[] = {
    0x0A, 0x0A, 0x0A, 0xFF, 0xF8, 0xFF, 0x85, 0x1F, 0x02, 0x65, 0xCD, 0xA8,
    0xA7, 0x3B, 0x9F, 0x4D, 0xAB, 0x19, 0x1A, 0x0C, 0x92, 0xEB, 0xE3, 0x53,
    0xA9, 0x4B, 0x02, 0x44, 0x1E, 0x00, 0xD2, 0x80, 0x74, 0x46, 0x46, 0x46,
    0x8B, 0x8B, 0x8B, 0x8E, 0xF6, 0x8E, 0x4D, 0x91, 0xD1, 0xBA, 0xBA, 0xBA,
};

static unsigned int pepto_ntsc_color_palette[] = {
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x67, 0x37, 0x2B, 0x70, 0xA3, 0xB1,
    0x6F, 0x3D, 0x86, 0x58, 0x8C, 0x42, 0x34, 0x28, 0x79, 0xB7, 0xC6, 0x6E,
    0x6F, 0x4E, 0x25, 0x42, 0x38, 0x00, 0x99, 0x66, 0x59, 0x43, 0x43, 0x43,
    0x6B, 0x6B, 0x6B, 0x9A, 0xD1, 0x83, 0x6B, 0x5E, 0xB5, 0x95, 0x95, 0x95,
};

static unsigned int pepto_pal_color_palette[] = {
    0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x68, 0x37, 0x2b, 0x70, 0xa4, 0xb2,
    0x6f, 0x3d, 0x86, 0x58, 0x8d, 0x43, 0x35, 0x28, 0x79, 0xb8, 0xc7, 0x6f,
    0x6f, 0x4f, 0x25, 0x43, 0x39, 0x00, 0x9a, 0x67, 0x59, 0x44, 0x44, 0x44,
    0x6c, 0x6c, 0x6c, 0x9a, 0xd2, 0x84, 0x6c, 0x5e, 0xb5, 0x95, 0x95, 0x95,
};

void set_refresh_rate(int timing, struct video_canvas_s *canvas) {
  if (timing == MACHINE_TIMING_NTSC_HDMI ||
      timing == MACHINE_TIMING_NTSC_COMPOSITE ||
      timing == MACHINE_TIMING_NTSC_CUSTOM) {
    canvas->refreshrate = C128_NTSC_RFSH_PER_SEC;
  } else {
    canvas->refreshrate = C128_PAL_RFSH_PER_SEC;
  }
}

void set_video_font(void) {
  int i;
  video_font = mem_chargen_rom + 0x800;
  raw_video_font = mem_chargen_rom;
  for (i = 0; i < 256; ++i) {
    video_font_translate[i] = 8 * ascii_to_petscii[i];
  }
}

unsigned int *raspi_get_palette(int index) {
  switch (index) {
  case 0:
    return default_color_palette;
    break;
  case 1:
    return vice_color_palette;
    break;
  case 2:
    return c64hq_color_palette;
    break;
  case 3:
    return pepto_ntsc_color_palette;
    break;
  case 4:
    return pepto_pal_color_palette;
    break;
  default:
    return NULL;
  }
}
