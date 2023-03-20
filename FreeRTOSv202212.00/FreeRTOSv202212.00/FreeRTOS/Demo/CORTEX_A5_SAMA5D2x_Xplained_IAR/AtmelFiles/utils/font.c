/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#include "font.h"

/*----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/

struct _font_parameters font_param[NB_FONT] = {
  {10, 14, 2, pCharset10x14},
  {10, 8, 1, pCharset10x8},
  {8, 8, 1, pCharset8x8},
  {6, 8, 0, pCharset6x8},
} ;

/*----------------------------------------------------------------------------
 *        Char set of font 10x14
 *----------------------------------------------------------------------------*/

const uint8_t pCharset10x14[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xCC,
    0xFF, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0C, 0xC0, 0x0C, 0xC0, 0xFF, 0xFC, 0xFF, 0xFC, 0x0C, 0xC0,
    0x0C, 0xC0, 0xFF, 0xFC, 0xFF, 0xFC, 0x0C, 0xC0, 0x0C, 0xC0,
    0x0C, 0x60, 0x1E, 0x70, 0x3F, 0x30, 0x33, 0x30, 0xFF, 0xFC,
    0xFF, 0xFC, 0x33, 0x30, 0x33, 0xF0, 0x39, 0xE0, 0x18, 0xC0,
    0x60, 0x00, 0xF0, 0x0C, 0xF0, 0x3C, 0x60, 0xF0, 0x03, 0xC0,
    0x0F, 0x00, 0x3C, 0x18, 0xF0, 0x3C, 0xC0, 0x3C, 0x00, 0x18,
    0x3C, 0xF0, 0x7F, 0xF8, 0xC3, 0x1C, 0xC7, 0x8C, 0xCF, 0xCC,
    0xDC, 0xEC, 0x78, 0x78, 0x30, 0x30, 0x00, 0xFC, 0x00, 0xCC,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0xEC, 0x00,
    0xF8, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x3F, 0xF0, 0x78, 0x78,
    0x60, 0x18, 0xC0, 0x0C, 0xC0, 0x0C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0x60, 0x18,
    0x78, 0x78, 0x3F, 0xF0, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x0C, 0x60, 0x0E, 0xE0, 0x07, 0xC0, 0x03, 0x80, 0x3F, 0xF8,
    0x3F, 0xF8, 0x03, 0x80, 0x07, 0xC0, 0x0E, 0xE0, 0x0C, 0x60,
    0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x3F, 0xF0,
    0x3F, 0xF0, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
    0x00, 0x44, 0x00, 0xEC, 0x00, 0xF8, 0x00, 0x70, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
    0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
    0x00, 0x18, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x18, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0C, 0x00, 0x3C, 0x00, 0xF0, 0x03, 0xC0,
    0x0F, 0x00, 0x3C, 0x00, 0xF0, 0x00, 0xC0, 0x00, 0x00, 0x00,
    0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0xFC, 0xC1, 0xCC, 0xC3, 0x8C,
    0xC7, 0x0C, 0xCE, 0x0C, 0xFC, 0x1C, 0x7F, 0xF8, 0x3F, 0xF0,
    0x00, 0x00, 0x00, 0x00, 0x30, 0x0C, 0x70, 0x0C, 0xFF, 0xFC,
    0xFF, 0xFC, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x0C, 0x70, 0x1C, 0xE0, 0x3C, 0xC0, 0x7C, 0xC0, 0xEC,
    0xC1, 0xCC, 0xC3, 0x8C, 0xE7, 0x0C, 0x7E, 0x0C, 0x3C, 0x0C,
    0x30, 0x30, 0x70, 0x38, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
    0xC3, 0x0C, 0xC3, 0x0C, 0xE3, 0x1C, 0x7F, 0xF8, 0x3C, 0xF0,
    0x03, 0xC0, 0x07, 0xC0, 0x0E, 0xC0, 0x1C, 0xC0, 0x38, 0xC0,
    0x70, 0xC0, 0xFF, 0xFC, 0xFF, 0xFC, 0x00, 0xC0, 0x00, 0xC0,
    0xFC, 0x30, 0xFC, 0x38, 0xCC, 0x1C, 0xCC, 0x0C, 0xCC, 0x0C,
    0xCC, 0x0C, 0xCC, 0x0C, 0xCE, 0x1C, 0xC7, 0xF8, 0xC3, 0xF0,
    0x3F, 0xF0, 0x7F, 0xF8, 0xE3, 0x1C, 0xC3, 0x0C, 0xC3, 0x0C,
    0xC3, 0x0C, 0xC3, 0x0C, 0xE3, 0x9C, 0x71, 0xF8, 0x30, 0xF0,
    0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC3, 0xFC,
    0xC7, 0xFC, 0xCE, 0x00, 0xDC, 0x00, 0xF8, 0x00, 0xF0, 0x00,
    0x3C, 0xF0, 0x7F, 0xF8, 0xE7, 0x9C, 0xC3, 0x0C, 0xC3, 0x0C,
    0xC3, 0x0C, 0xC3, 0x0C, 0xE7, 0x9C, 0x7F, 0xF8, 0x3C, 0xF0,
    0x3C, 0x00, 0x7E, 0x00, 0xE7, 0x0C, 0xC3, 0x0C, 0xC3, 0x1C,
    0xC3, 0x38, 0xC3, 0x70, 0xE7, 0xE0, 0x7F, 0xC0, 0x3F, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x3C, 0xF0,
    0x3C, 0xF0, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x44, 0x3C, 0xEC,
    0x3C, 0xF8, 0x18, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x00, 0x07, 0x80, 0x0F, 0xC0, 0x1C, 0xE0,
    0x38, 0x70, 0x70, 0x38, 0xE0, 0x1C, 0xC0, 0x0C, 0x00, 0x00,
    0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0,
    0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0,
    0x00, 0x00, 0xC0, 0x0C, 0xE0, 0x1C, 0x70, 0x38, 0x38, 0x70,
    0x1C, 0xE0, 0x0F, 0xC0, 0x07, 0x80, 0x03, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x70, 0x00, 0xE0, 0x00, 0xC0, 0x00, 0xC1, 0xEC,
    0xC3, 0xEC, 0xC3, 0x00, 0xE6, 0x00, 0x7E, 0x00, 0x3C, 0x00,
    0x30, 0xF0, 0x71, 0xF8, 0xE3, 0x9C, 0xC3, 0x0C, 0xC3, 0xFC,
    0xC3, 0xFC, 0xC0, 0x0C, 0xE0, 0x1C, 0x7F, 0xF8, 0x3F, 0xF0,
    0x3F, 0xFC, 0x7F, 0xFC, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
    0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xC0, 0x7F, 0xFC, 0x3F, 0xFC,
    0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x0C, 0xC3, 0x0C, 0xC3, 0x0C,
    0xC3, 0x0C, 0xC3, 0x0C, 0xE7, 0x9C, 0x7F, 0xF8, 0x3C, 0xF0,
    0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
    0xC0, 0x0C, 0xC0, 0x0C, 0xE0, 0x1C, 0x70, 0x38, 0x30, 0x30,
    0xFF, 0xFC, 0xFF, 0xFC, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C,
    0xC0, 0x0C, 0xC0, 0x0C, 0xE0, 0x1C, 0x7F, 0xF8, 0x3F, 0xF0,
    0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x0C, 0xC3, 0x0C, 0xC3, 0x0C,
    0xC3, 0x0C, 0xC3, 0x0C, 0xC3, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C,
    0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00,
    0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC0, 0x00, 0xC0, 0x00,
    0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
    0xC3, 0x0C, 0xC3, 0x0C, 0xE3, 0x1C, 0x73, 0xF8, 0x33, 0xF0,
    0xFF, 0xFC, 0xFF, 0xFC, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
    0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0xFF, 0xFC, 0xFF, 0xFC,
    0x00, 0x00, 0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0xFF, 0xFC,
    0xFF, 0xFC, 0xC0, 0x0C, 0xC0, 0x0C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x30, 0x00, 0x38, 0xC0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
    0xC0, 0x1C, 0xFF, 0xF8, 0xFF, 0xF0, 0xC0, 0x00, 0xC0, 0x00,
    0xFF, 0xFC, 0xFF, 0xFC, 0x07, 0x80, 0x07, 0x80, 0x0F, 0xC0,
    0x1C, 0xE0, 0x38, 0x70, 0x70, 0x38, 0xE0, 0x1C, 0xC0, 0x0C,
    0xFF, 0xFC, 0xFF, 0xFC, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C,
    0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C,
    0xFF, 0xFC, 0xFF, 0xFC, 0x70, 0x00, 0x38, 0x00, 0x1F, 0x00,
    0x1F, 0x00, 0x38, 0x00, 0x70, 0x00, 0xFF, 0xFC, 0xFF, 0xFC,
    0xFF, 0xFC, 0xFF, 0xFC, 0x1C, 0x00, 0x0E, 0x00, 0x07, 0x00,
    0x03, 0x80, 0x01, 0xC0, 0x00, 0xE0, 0xFF, 0xFC, 0xFF, 0xFC,
    0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
    0xC0, 0x0C, 0xC0, 0x0C, 0xE0, 0x1C, 0x7F, 0xF8, 0x3F, 0xF0,
    0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00,
    0xC3, 0x00, 0xC3, 0x00, 0xE7, 0x00, 0x7E, 0x00, 0x3C, 0x00,
    0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0xCC,
    0xC0, 0xEC, 0xC0, 0x7C, 0xE0, 0x38, 0x7F, 0xFC, 0x3F, 0xEC,
    0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x00, 0xC3, 0x80, 0xC3, 0x80,
    0xC3, 0xC0, 0xC3, 0xC0, 0xE7, 0x70, 0x7E, 0x3C, 0x3C, 0x1C,
    0x3C, 0x18, 0x7E, 0x1C, 0xE7, 0x0C, 0xC3, 0x0C, 0xC3, 0x0C,
    0xC3, 0x0C, 0xC3, 0x0C, 0xC3, 0x9C, 0xE1, 0xF8, 0x60, 0xF0,
    0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xFF, 0xFC,
    0xFF, 0xFC, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00,
    0xFF, 0xF0, 0xFF, 0xF8, 0x00, 0x1C, 0x00, 0x0C, 0x00, 0x0C,
    0x00, 0x0C, 0x00, 0x0C, 0x00, 0x1C, 0xFF, 0xF8, 0xFF, 0xF0,
    0xFF, 0xC0, 0xFF, 0xE0, 0x00, 0x70, 0x00, 0x38, 0x00, 0x1C,
    0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0xFF, 0xE0, 0xFF, 0xC0,
    0xFF, 0xF0, 0xFF, 0xF8, 0x00, 0x1C, 0x00, 0x3C, 0x00, 0xF8,
    0x00, 0xF8, 0x00, 0x3C, 0x00, 0x1C, 0xFF, 0xF8, 0xFF, 0xF0,
    0xF0, 0x3C, 0xF8, 0x7C, 0x1C, 0xE0, 0x0F, 0xC0, 0x07, 0x80,
    0x07, 0x80, 0x0F, 0xC0, 0x1C, 0xE0, 0xF8, 0x7C, 0xF0, 0x3C,
    0xFC, 0x00, 0xFE, 0x00, 0x07, 0x00, 0x03, 0x80, 0x01, 0xFC,
    0x01, 0xFC, 0x03, 0x80, 0x07, 0x00, 0xFE, 0x00, 0xFC, 0x00,
    0xC0, 0x3C, 0xC0, 0x7C, 0xC0, 0xEC, 0xC1, 0xCC, 0xC3, 0x8C,
    0xC7, 0x0C, 0xCE, 0x0C, 0xDC, 0x0C, 0xF8, 0x0C, 0xF0, 0x0C,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0xFF, 0xFC, 0xC0, 0x0C,
    0xC0, 0x0C, 0xC0, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x30, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x03, 0x00,
    0x03, 0x00, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x30, 0x00, 0x30,
    0x00, 0x00, 0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C,
    0xFF, 0xFC, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0C, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x00, 0xE0, 0x00,
    0xE0, 0x00, 0x70, 0x00, 0x38, 0x00, 0x1C, 0x00, 0x0C, 0x00,
    0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C,
    0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C,
    0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0xE0, 0x00, 0x70, 0x00,
    0x38, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x30, 0x06, 0x78, 0x0E, 0xFC, 0x0C, 0xCC, 0x0C, 0xCC,
    0x0C, 0xCC, 0x0C, 0xCC, 0x0E, 0xCC, 0x07, 0xFC, 0x03, 0xF8,
    0xFF, 0xFC, 0xFF, 0xFC, 0x03, 0x0C, 0x03, 0x0C, 0x03, 0x0C,
    0x03, 0x0C, 0x03, 0x0C, 0x03, 0x9C, 0x01, 0xF8, 0x00, 0xF0,
    0x03, 0xF0, 0x07, 0xF8, 0x0E, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C,
    0x0C, 0x0C, 0x0C, 0x0C, 0x0E, 0x1C, 0x07, 0x38, 0x03, 0x30,
    0x00, 0xF0, 0x01, 0xF8, 0x03, 0x9C, 0x03, 0x0C, 0x03, 0x0C,
    0x03, 0x0C, 0x03, 0x0C, 0x03, 0x0C, 0xFF, 0xFC, 0xFF, 0xFC,
    0x03, 0xF0, 0x07, 0xF8, 0x0E, 0xDC, 0x0C, 0xCC, 0x0C, 0xCC,
    0x0C, 0xCC, 0x0C, 0xCC, 0x0E, 0xDC, 0x07, 0xD8, 0x03, 0x90,
    0x00, 0x00, 0x03, 0x00, 0x3F, 0xFC, 0x7F, 0xFC, 0xE3, 0x00,
    0xE3, 0x00, 0x70, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x18, 0x07, 0x9C, 0x0F, 0xCC, 0x0C, 0xCC, 0x0C, 0xCC,
    0x0C, 0xCC, 0x0C, 0xCC, 0x0C, 0xDC, 0x0F, 0xF8, 0x07, 0xF0,
    0xFF, 0xFC, 0xFF, 0xFC, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
    0x03, 0x00, 0x03, 0x80, 0x01, 0xFC, 0x00, 0xFC, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0xFC,
    0x1B, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x00, 0x38, 0x00, 0x1C, 0x00, 0x0C,
    0x00, 0x0C, 0x00, 0x1C, 0xCF, 0xF8, 0xCF, 0xF0, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFC, 0xFF, 0xFC, 0x00, 0xE0, 0x01, 0xE0,
    0x03, 0xF0, 0x07, 0x38, 0x0E, 0x1C, 0x0C, 0x0C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0xFF, 0xFC,
    0xFF, 0xFC, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0xFC, 0x0F, 0xFC, 0x0E, 0x00, 0x07, 0x00, 0x03, 0xC0,
    0x03, 0xC0, 0x07, 0x00, 0x0E, 0x00, 0x0F, 0xFC, 0x0F, 0xFC,
    0x0F, 0xFC, 0x0F, 0xFC, 0x03, 0x00, 0x07, 0x00, 0x0E, 0x00,
    0x0C, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0x07, 0xFC, 0x03, 0xFC,
    0x03, 0xF0, 0x07, 0xF8, 0x0E, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C,
    0x0C, 0x0C, 0x0C, 0x0C, 0x0E, 0x1C, 0x07, 0xF8, 0x03, 0xF0,
    0x0F, 0xFC, 0x0F, 0xFC, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0,
    0x0C, 0xC0, 0x0C, 0xC0, 0x0F, 0xC0, 0x07, 0x80, 0x03, 0x00,
    0x03, 0x00, 0x07, 0x80, 0x0F, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0,
    0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0F, 0xFC, 0x0F, 0xFC,
    0x0F, 0xFC, 0x0F, 0xFC, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00,
    0x0C, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0x07, 0x00, 0x03, 0x00,
    0x03, 0x18, 0x07, 0x9C, 0x0F, 0xCC, 0x0C, 0xCC, 0x0C, 0xCC,
    0x0C, 0xCC, 0x0C, 0xCC, 0x0C, 0xFC, 0x0E, 0x78, 0x06, 0x30,
    0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0xFF, 0xF0, 0xFF, 0xF8,
    0x0C, 0x1C, 0x0C, 0x1C, 0x0C, 0x38, 0x0C, 0x30, 0x00, 0x00,
    0x0F, 0xF0, 0x0F, 0xF8, 0x00, 0x1C, 0x00, 0x0C, 0x00, 0x0C,
    0x00, 0x0C, 0x00, 0x0C, 0x00, 0x1C, 0x0F, 0xF8, 0x0F, 0xF0,
    0x0F, 0xC0, 0x0F, 0xE0, 0x00, 0x70, 0x00, 0x38, 0x00, 0x1C,
    0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x0F, 0xE0, 0x0F, 0xC0,
    0x0F, 0xF0, 0x0F, 0xF8, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0xF8,
    0x00, 0xF8, 0x00, 0x1C, 0x00, 0x1C, 0x0F, 0xF8, 0x0F, 0xF0,
    0x0C, 0x0C, 0x0E, 0x1C, 0x07, 0x38, 0x03, 0xF0, 0x01, 0xE0,
    0x01, 0xE0, 0x03, 0xF0, 0x07, 0x38, 0x0E, 0x1C, 0x0C, 0x0C,
    0x0C, 0x00, 0x0E, 0x00, 0x07, 0x0C, 0x03, 0x9C, 0x01, 0xF8,
    0x01, 0xF0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x0C, 0x00,
    0x0C, 0x0C, 0x0C, 0x1C, 0x0C, 0x3C, 0x0C, 0x7C, 0x0C, 0xEC,
    0x0D, 0xCC, 0x0F, 0x8C, 0x0F, 0x0C, 0x0E, 0x0C, 0x0C, 0x0C,
    0x00, 0x00, 0x03, 0x00, 0x07, 0x80, 0x3F, 0xF0, 0x7C, 0xF8,
    0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0x00, 0x00,
    0x03, 0x0C, 0x03, 0x0C, 0x3F, 0xFC, 0x7F, 0xFC, 0xE3, 0x0C,
    0xC3, 0x0C, 0xC0, 0x0C, 0xE0, 0x0C, 0x70, 0x0C, 0x30, 0x0C,
    0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xE0, 0x1C,
    0x7C, 0xF8, 0x3F, 0xF0, 0x07, 0x80, 0x03, 0x00, 0x00, 0x00,
    0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00,
    0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00,
    0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC,
    0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC
} ;

/*----------------------------------------------------------------------------
 *        Char set of font 10x8
 *----------------------------------------------------------------------------*/
const uint8_t pCharset10x8[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // space 0x20
0x18,0x3C,0x3C,0x3C,0x18,0x18,0x18,0x00,0x18,0x18, // !
0x63,0x63,0x63,0x22,0x00,0x00,0x00,0x00,0x00,0x00, // "
0x00,0x36,0x36,0x7F,0x36,0x36,0x36,0x7F,0x36,0x36, // #
0x3E,0x63,0x61,0x60,0x3E,0x03,0x03,0x43,0x63,0x3E, // $
0x00,0x00,0x00,0x61,0x63,0x06,0x0C,0x18,0x33,0x63, // %
0x00,0x1C,0x36,0x36,0x1C,0x3B,0x6E,0x66,0x66,0x3B, // &
0x30,0x30,0x30,0x60,0x00,0x00,0x00,0x00,0x00,0x00, // '
0x0C,0x18,0x18,0x30,0x30,0x30,0x30,0x18,0x18,0x0C, // (
0x18,0x0C,0x0C,0x06,0x06,0x06,0x06,0x0C,0x0C,0x18, // )
0x00,0x00,0x42,0x66,0x3C,0xFF,0x3C,0x66,0x42,0x00, // *
0x00,0x00,0x18,0x18,0x18,0xFF,0x18,0x18,0x18,0x00, // +
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18, // ,
0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00, // -
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18, // .
0x01,0x03,0x07,0x0E,0x1C,0x38,0x70,0xE0,0xC0,0x80, // / (forward slash)
0x3E,0x63,0x63,0x63,0x6B,0x6B,0x63,0x63,0x63,0x3E, // 0 0x30
0x0C,0x1C,0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3F, // 1
0x3E,0x63,0x03,0x06,0x0C,0x18,0x30,0x61,0x63,0x7F, // 2
0x3E,0x63,0x03,0x03,0x1E,0x03,0x03,0x03,0x63,0x3E, // 3
0x06,0x0E,0x1E,0x36,0x66,0x66,0x7F,0x06,0x06,0x0F, // 4
0x7F,0x60,0x60,0x60,0x7E,0x03,0x03,0x63,0x73,0x3E, // 5
0x1C,0x30,0x60,0x60,0x7E,0x63,0x63,0x63,0x63,0x3E, // 6
0x7F,0x63,0x03,0x06,0x06,0x0C,0x0C,0x18,0x18,0x18, // 7
0x3E,0x63,0x63,0x63,0x3E,0x63,0x63,0x63,0x63,0x3E, // 8
0x3E,0x63,0x63,0x63,0x63,0x3F,0x03,0x03,0x06,0x3C, // 9
0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x18,0x18, // :
0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x18,0x18, // ;
0x00,0x06,0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x06, // <
0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00, // =
0x00,0x60,0x30,0x18,0x0C,0x06,0x0C,0x18,0x30,0x60, // >
0x3E,0x63,0x63,0x06,0x0C,0x0C,0x0C,0x00,0x0C,0x0C, // ?
0x3E,0x63,0x63,0x6F,0x6B,0x6B,0x6E,0x60,0x60,0x3E, // @ 0x40
0x08,0x1C,0x36,0x63,0x63,0x63,0x7F,0x63,0x63,0x63, // A
0x7E,0x33,0x33,0x33,0x3E,0x33,0x33,0x33,0x33,0x7E, // B
0x1E,0x33,0x61,0x60,0x60,0x60,0x60,0x61,0x33,0x1E, // C
0x7C,0x36,0x33,0x33,0x33,0x33,0x33,0x33,0x36,0x7C, // D
0x7F,0x33,0x31,0x34,0x3C,0x34,0x30,0x31,0x33,0x7F, // E
0x7F,0x33,0x31,0x34,0x3C,0x34,0x30,0x30,0x30,0x78, // F
0x1E,0x33,0x61,0x60,0x60,0x6F,0x63,0x63,0x37,0x1D, // G
0x63,0x63,0x63,0x63,0x7F,0x63,0x63,0x63,0x63,0x63, // H
0x3C,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x3C, // I
0x0F,0x06,0x06,0x06,0x06,0x06,0x06,0x66,0x66,0x3C, // J
0x73,0x33,0x36,0x36,0x3C,0x36,0x36,0x33,0x33,0x73, // K
0x78,0x30,0x30,0x30,0x30,0x30,0x30,0x31,0x33,0x7F, // L
0x63,0x77,0x7F,0x6B,0x63,0x63,0x63,0x63,0x63,0x63, // M
0x63,0x63,0x73,0x7B,0x7F,0x6F,0x67,0x63,0x63,0x63, // N
0x1C,0x36,0x63,0x63,0x63,0x63,0x63,0x63,0x36,0x1C, // O
0x7E,0x33,0x33,0x33,0x3E,0x30,0x30,0x30,0x30,0x78, // P 0x50
0x3E,0x63,0x63,0x63,0x63,0x6B,0x6F,0x3E,0x06,0x07, // Q
0x7E,0x33,0x33,0x33,0x3E,0x36,0x36,0x33,0x33,0x73, // R
0x3E,0x63,0x63,0x30,0x1C,0x06,0x03,0x63,0x63,0x3E, // S
0xFF,0xDB,0x99,0x18,0x18,0x18,0x18,0x18,0x18,0x3C, // T
0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x3E, // U
0x63,0x63,0x63,0x63,0x63,0x63,0x63,0x36,0x1C,0x08, // V
0x63,0x63,0x63,0x63,0x63,0x6B,0x6B,0x7F,0x36,0x36, // W
0xC3,0xC3,0x66,0x3C,0x18,0x18,0x3C,0x66,0xC3,0xC3, // X
0xC3,0xC3,0xC3,0x66,0x3C,0x18,0x18,0x18,0x18,0x3C, // Y
0x7F,0x63,0x43,0x06,0x0C,0x18,0x30,0x61,0x63,0x7F, // Z
0x3C,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3C, // [
0x80,0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03,0x01, // \ (back slash)
0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C, // ]
0x08,0x1C,0x36,0x63,0x00,0x00,0x00,0x00,0x00,0x00, // ^
0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00, // _
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ` 0x60
0x00,0x00,0x00,0x3C,0x46,0x06,0x3E,0x66,0x66,0x3B, // a
0x70,0x30,0x30,0x3C,0x36,0x33,0x33,0x33,0x33,0x6E, // b
0x00,0x00,0x00,0x3E,0x63,0x60,0x60,0x60,0x63,0x3E, // c
0x0E,0x06,0x06,0x1E,0x36,0x66,0x66,0x66,0x66,0x3B, // d
0x00,0x00,0x00,0x3E,0x63,0x63,0x7E,0x60,0x63,0x3E, // e
0x1C,0x36,0x32,0x30,0x7C,0x30,0x30,0x30,0x30,0x78, // f
0x00,0x00,0x00,0x3B,0x66,0x66,0x3E,0x06,0x66,0x3C, // g
0x70,0x30,0x30,0x36,0x3B,0x33,0x33,0x33,0x33,0x73, // h
0x0C,0x0C,0x00,0x1C,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E, // i
0x06,0x06,0x00,0x0E,0x06,0x06,0x06,0x66,0x66,0x3C, // j
0x70,0x30,0x30,0x33,0x33,0x36,0x3C,0x36,0x33,0x73, // k
0x1C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E, // l
0x00,0x00,0x00,0x6E,0x7F,0x6B,0x6B,0x6B,0x6B,0x6B, // m
0x00,0x00,0x00,0x6E,0x33,0x33,0x33,0x33,0x33,0x33, // n
0x00,0x00,0x00,0x3E,0x63,0x63,0x63,0x63,0x63,0x3E, // o
0x00,0x00,0x00,0x6E,0x33,0x33,0x3E,0x30,0x30,0x78, // p
0x00,0x00,0x00,0x3B,0x66,0x66,0x3E,0x06,0x06,0x0F, // q
0x00,0x00,0x00,0x6E,0x3B,0x33,0x30,0x30,0x30,0x78, // r
0x00,0x00,0x00,0x3E,0x63,0x38,0x0E,0x03,0x63,0x3E, // s
0x08,0x18,0x18,0x7E,0x18,0x18,0x18,0x18,0x1B,0x0E, // t
0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x66,0x3B, // u
0x00,0x00,0x00,0x63,0x63,0x36,0x36,0x1C,0x1C,0x08, // v
0x00,0x00,0x00,0x63,0x63,0x63,0x6B,0x6B,0x7F,0x36, // w
0x00,0x00,0x00,0x63,0x36,0x1C,0x1C,0x1C,0x36,0x63, // x
0x00,0x00,0x63,0x63,0x63,0x63,0x3F,0x03,0x06,0x3C, // y
0x00,0x00,0x00,0x7F,0x66,0x0C,0x18,0x30,0x63,0x7F, // z
0x0E,0x18,0x18,0x18,0x70,0x18,0x18,0x18,0x18,0x0E, // {
0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x18, // |
0x70,0x18,0x18,0x18,0x0E,0x18,0x18,0x18,0x18,0x70, // }
0x3B,0x6E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ~
0x70,0xD8,0xD8,0x70,0x00,0x00,0x00,0x00,0x00,0x00, // DEL
};

/*----------------------------------------------------------------------------
 *        Char set of font 8x8
 *----------------------------------------------------------------------------*/
const uint8_t pCharset8x8[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // U+0020 (space)
  0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00,   // U+0021 (!)
  0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // U+0022 (")
  0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00,   // U+0023 (#)
  0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00,   // U+0024 ($)
  0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00,   // U+0025 (%)
  0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00,   // U+0026 (&)
  0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,   // U+0027 (')
  0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00,   // U+0028 (()
  0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00,   // U+0029 ())
  0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00,   // U+002A (*)
  0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00,   // U+002B (+)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06,   // U+002C (,)
  0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00,   // U+002D (-)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00,   // U+002E (.)
  0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00,   // U+002F (/)
  0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00,   // U+0030 (0)
  0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00,   // U+0031 (1)
  0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00,   // U+0032 (2)
  0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00,   // U+0033 (3)
  0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00,   // U+0034 (4)
  0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00,   // U+0035 (5)
  0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00,   // U+0036 (6)
  0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00,   // U+0037 (7)
  0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00,   // U+0038 (8)
  0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00,   // U+0039 (9)
  0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00,   // U+003A (:)
  0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06,   // U+003B (//)
  0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00,   // U+003C (<)
  0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00,   // U+003D (=)
  0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00,   // U+003E (>)
  0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00,   // U+003F (?)
  0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00,   // U+0040 (@)
  0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00,   // U+0041 (A)
  0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00,   // U+0042 (B)
  0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00,   // U+0043 (C)
  0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00,   // U+0044 (D)
  0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00,   // U+0045 (E)
  0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00,   // U+0046 (F)
  0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00,   // U+0047 (G)
  0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00,   // U+0048 (H)
  0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00,   // U+0049 (I)
  0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00,   // U+004A (J)
  0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00,   // U+004B (K)
  0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00,   // U+004C (L)
  0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00,   // U+004D (M)
  0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00,   // U+004E (N)
  0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00,   // U+004F (O)
  0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00,   // U+0050 (P)
  0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00,   // U+0051 (Q)
  0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00,   // U+0052 (R)
  0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00,   // U+0053 (S)
  0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00,   // U+0054 (T)
  0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00,   // U+0055 (U)
  0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00,   // U+0056 (V)
  0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00,   // U+0057 (W)
  0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00,   // U+0058 (X)
  0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00,   // U+0059 (Y)
  0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00,   // U+005A (Z)
  0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00,   // U+005B ([)
  0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00,   // U+005C (\)
  0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00,   // U+005D (])
  0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00,   // U+005E (^)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,   // U+005F (_)
  0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,   // U+0060 (`)
  0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00,   // U+0061 (a)
  0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00,   // U+0062 (b)
  0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00,   // U+0063 (c)
  0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00,   // U+0064 (d)
  0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00,   // U+0065 (e)
  0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00,   // U+0066 (f)
  0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F,   // U+0067 (g)
  0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00,   // U+0068 (h)
  0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00,   // U+0069 (i)
  0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E,   // U+006A (j)
  0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00,   // U+006B (k)
  0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00,   // U+006C (l)
  0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00,   // U+006D (m)
  0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00,   // U+006E (n)
  0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00,   // U+006F (o)
  0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F,   // U+0070 (p)
  0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78,   // U+0071 (q)
  0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00,   // U+0072 (r)
  0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00,   // U+0073 (s)
  0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00,   // U+0074 (t)
  0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00,   // U+0075 (u)
  0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00,   // U+0076 (v)
  0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00,   // U+0077 (w)
  0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00,   // U+0078 (x)
  0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F,   // U+0079 (y)
  0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00,   // U+007A (z)
  0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00,   // U+007B ()
  0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00,   // U+007C (|)
  0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00,   // U+007D ()
  0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // U+007E (~)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    // U+007F
} ;

/*----------------------------------------------------------------------------
 *        Char set of font 6x8
 *----------------------------------------------------------------------------*/
const uint8_t pCharset6x8[] =
{
0x00,0x00,0x00,0x00,0x00,0x00, // Symbol 20
0x00,0x00,0x00,0x5F,0x00,0x00, // Symbol 21
0x00,0x00,0x03,0x00,0x03,0x00, // Symbol 22
0x22,0x7F,0x22,0x22,0x7F,0x22, // Symbol 23
0x00,0x24,0x2A,0x6B,0x2A,0x12, // Symbol 24
0x00,0x23,0x13,0x08,0x64,0x62, // Symbol 25
0x00,0x3A,0x45,0x45,0x3A,0x28, // Symbol 26
0x00,0x00,0x00,0x02,0x01,0x00, // Symbol 27
0x00,0x00,0x3E,0x41,0x00,0x00, // Symbol 28
0x00,0x00,0x41,0x3E,0x00,0x00, // Symbol 29
0x00,0x2A,0x1C,0x1C,0x2A,0x00, // Symbol 2A
0x00,0x08,0x08,0x3E,0x08,0x08, // Symbol 2B
0x00,0x00,0x80,0x40,0x00,0x00, // Symbol 2C
0x00,0x08,0x08,0x08,0x08,0x00, // Symbol 2D
0x00,0x00,0x00,0x40,0x00,0x00, // Symbol 2E
0x00,0x20,0x10,0x08,0x04,0x02, // Symbol 2F
0x00,0x3E,0x51,0x49,0x45,0x3E, // Symbol 30
0x00,0x00,0x42,0x7F,0x40,0x00, // Symbol 31
0x00,0x62,0x51,0x51,0x51,0x4E, // Symbol 32
0x00,0x21,0x41,0x45,0x45,0x3B, // Symbol 33
0x00,0x18,0x16,0x11,0x7F,0x10, // Symbol 34
0x00,0x27,0x45,0x45,0x45,0x39, // Symbol 35
0x00,0x3E,0x49,0x49,0x49,0x32, // Symbol 36
0x00,0x01,0x61,0x11,0x09,0x07, // Symbol 37
0x00,0x36,0x49,0x49,0x49,0x36, // Symbol 38
0x00,0x26,0x49,0x49,0x49,0x3E, // Symbol 39
0x00,0x00,0x00,0x12,0x00,0x00, // Symbol 3A
0x00,0x00,0x20,0x12,0x00,0x00, // Symbol 3B
0x00,0x08,0x14,0x22,0x41,0x00, // Symbol 3C
0x00,0x14,0x14,0x14,0x14,0x14, // Symbol 3D
0x00,0x41,0x22,0x14,0x08,0x00, // Symbol 3E
0x00,0x06,0x01,0x51,0x09,0x06, // Symbol 3F
0x00,0x3E,0x41,0x4D,0x4D,0x2E, // Symbol 40
0x00,0x78,0x16,0x11,0x16,0x78, // Symbol 41
0x00,0x7F,0x49,0x49,0x49,0x36, // Symbol 42
0x00,0x3E,0x41,0x41,0x41,0x22, // Symbol 43
0x00,0x7F,0x41,0x41,0x41,0x3E, // Symbol 44
0x00,0x7F,0x49,0x49,0x49,0x41, // Symbol 45
0x00,0x7F,0x09,0x09,0x09,0x01, // Symbol 46
0x00,0x3E,0x41,0x41,0x51,0x32, // Symbol 47
0x00,0x7F,0x08,0x08,0x08,0x7F, // Symbol 48
0x00,0x00,0x41,0x7F,0x41,0x00, // Symbol 49
0x00,0x30,0x40,0x41,0x41,0x3F, // Symbol 4A
0x00,0x7F,0x08,0x08,0x14,0x63, // Symbol 4B
0x00,0x7F,0x40,0x40,0x40,0x60, // Symbol 4C
0x00,0x7F,0x04,0x18,0x04,0x7F, // Symbol 4D
0x00,0x7F,0x04,0x08,0x10,0x7F, // Symbol 4E
0x00,0x3E,0x41,0x41,0x41,0x3E, // Symbol 4F
0x00,0x7F,0x09,0x09,0x09,0x06, // Symbol 50
0x00,0x3E,0x41,0x61,0x21,0x5E, // Symbol 51
0x00,0x7F,0x09,0x09,0x19,0x66, // Symbol 52
0x00,0x26,0x49,0x49,0x49,0x32, // Symbol 53
0x00,0x01,0x01,0x7F,0x01,0x01, // Symbol 54
0x00,0x3F,0x40,0x40,0x40,0x3F, // Symbol 55
0x00,0x07,0x18,0x60,0x18,0x07, // Symbol 56
0x00,0x1F,0x60,0x18,0x60,0x1F, // Symbol 57
0x00,0x63,0x14,0x08,0x14,0x63, // Symbol 58
0x00,0x03,0x04,0x78,0x04,0x03, // Symbol 59
0x00,0x61,0x51,0x49,0x45,0x43, // Symbol 5A
0x00,0x00,0x7F,0x41,0x00,0x00, // Symbol 5B
0x00,0x02,0x04,0x08,0x10,0x20, // Symbol 5C
0x00,0x00,0x41,0x7F,0x00,0x00, // Symbol 5D
0x00,0x00,0x00,0x00,0x00,0x00, // Symbol 5E
0x40,0x40,0x40,0x40,0x40,0x40, // Symbol 5F
0x00,0x00,0x00,0x01,0x02,0x00, // Symbol 60
0x00,0x20,0x54,0x54,0x54,0x78, // Symbol 61
0x00,0x7E,0x48,0x48,0x48,0x30, // Symbol 62
0x00,0x38,0x44,0x44,0x44,0x28, // Symbol 63
0x00,0x30,0x48,0x48,0x48,0x7E, // Symbol 64
0x00,0x38,0x54,0x54,0x54,0x18, // Symbol 65
0x00,0x10,0x7C,0x12,0x02,0x04, // Symbol 66
0x00,0x0C,0x52,0x52,0x3C,0x02, // Symbol 67
0x00,0x7E,0x08,0x08,0x08,0x70, // Symbol 68
0x00,0x00,0x00,0x74,0x00,0x00, // Symbol 69
0x00,0x40,0x80,0x80,0x74,0x00, // Symbol 6A
0x00,0x7E,0x10,0x10,0x10,0x6C, // Symbol 6B
0x00,0x00,0x02,0x7E,0x00,0x00, // Symbol 6C
0x00,0x7C,0x04,0x78,0x04,0x78, // Symbol 6D
0x00,0x7C,0x04,0x04,0x04,0x78, // Symbol 6E
0x00,0x38,0x44,0x44,0x44,0x38, // Symbol 6F
0x00,0xFC,0x24,0x24,0x24,0x18, // Symbol 70
0x00,0x18,0x24,0x24,0x24,0xFC, // Symbol 71
0x00,0x7C,0x08,0x04,0x04,0x08, // Symbol 72
0x00,0x48,0x54,0x54,0x54,0x20, // Symbol 73
0x00,0x08,0x3E,0x48,0x40,0x00, // Symbol 74
0x00,0x3C,0x40,0x40,0x40,0x3C, // Symbol 75
0x00,0x1C,0x20,0x40,0x20,0x1C, // Symbol 76
0x00,0x3C,0x40,0x30,0x40,0x3C, // Symbol 77
0x00,0x44,0x28,0x10,0x28,0x44, // Symbol 78
0x00,0x1C,0x20,0xA0,0xA0,0x7C, // Symbol 79
0x00,0x44,0x64,0x54,0x4C,0x44, // Symbol 7A
0x00,0x08,0x36,0x41,0x00,0x00, // Symbol 7B
0x00,0x00,0x00,0x7F,0x00,0x00, // Symbol 7C
0x00,0x00,0x41,0x36,0x08,0x00, // Symbol 7D
0x02,0x01,0x01,0x02,0x02,0x01, // Symbol 7E
0x00,0x7F,0x7F,0x7F,0x7F,0x7F  // Symbol 7F
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// End of file
