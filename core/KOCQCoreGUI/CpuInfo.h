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
 * This file defines methods/properties to get CPU usage for        *
 * Windows, Android, Linux                                          *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-04-2020                                               *
 *        Initial version supports CPU measurement                  *
 *******************************************************************/

#ifndef CPUINFO_H
#define CPUINFO_H

#include <QObject>
#include <QFile>

#ifdef Q_OS_WIN
    #include "Windows.h"
#elif (defined(Q_OS_ANDROID) || defined(Q_OS_LINUX))
    #include <sys/types.h>
    #include <sys/sysinfo.h>
#endif

class CpuInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double cpuUsage READ cpuUsage NOTIFY cpuUsageChanged)
public:
    CpuInfo();

    double cpuUsage() const;

public slots:
    void update();

signals:
    void cpuUsageChanged();

private:
    double m_cpuUsage;

#ifdef Q_OS_WIN
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    FILETIME last_idleTime;
    FILETIME last_kernelTime;
    FILETIME last_userTime;

    qulonglong convertFileTime(const FILETIME& filetime) const;
#elif (defined(Q_OS_ANDROID) || defined(Q_OS_LINUX))
    qulonglong totalUser = 0;
    qulonglong totalUserNice = 0;
    qulonglong totalSystem = 0;
    qulonglong totalIdle = 0;

    qulonglong last_totalUser = 0;
    qulonglong last_totalUserNice = 0;
    qulonglong last_totalSystem = 0;
    qulonglong last_totalIdle = 0;
#endif
};

#endif // CPUINFO_H
