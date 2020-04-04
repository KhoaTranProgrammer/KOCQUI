/*
 * MIT License
 * 
 * Copyright (c) 2020 KhoaTran Programmer
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/******************
 * VERSION: 1.0.0 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This class exports QML Types for C++ class                       *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-04-2020                                               *
 *        Initial version exports CpuInfo and KOCQMatImage          *
 *******************************************************************/

#include "kocqcoregui_plugin.h"
#include "CpuInfo.h"
#include "KOCQMatImage.h"

#include <qqml.h>

void KOCQCoreGUIPlugin::registerTypes(const char *uri)
{
    // @uri com.kocqui.kocqcoregui

    // CpuInfo
    qmlRegisterType<CpuInfo>(uri, 1, 0, "CpuInfo");

    // KOCQMatImage
    qmlRegisterType<KOCQMatImage>(uri, 1, 0, "KOCQMatImage");

    // The minor version of plugin
    qmlRegisterModule(uri, 1, 0);
}
