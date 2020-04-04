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
 * This file implements methods to get CPU usage for Windows,       *
 * Android, Linux                                                   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-04-2020                                               *
 *        Initial version supports CPU measurement                  *
 *******************************************************************/

#include "CpuInfo.h"

CpuInfo::CpuInfo()
{
    m_cpuUsage = 0;

#ifdef Q_OS_WIN
    //get the last systemtime
    GetSystemTimes(&last_idleTime, &last_kernelTime, &last_userTime);
#elif (defined(Q_OS_ANDROID) || defined(Q_OS_LINUX))
    //get cpu first time running
    QFile file2("/proc/stat");
    file2.open(QIODevice::ReadOnly);
    QByteArray line2 = file2.readLine();
    file2.close();
    sscanf(line2.data(), "cpu %llu %llu %llu %llu", &last_totalUser, &last_totalUserNice, &last_totalSystem, &last_totalIdle);
#endif
}

double CpuInfo::cpuUsage() const
{
    return m_cpuUsage;
}

void CpuInfo::update()
{
#ifdef Q_OS_WIN
    //update cpu
    GetSystemTimes( &this->idleTime, &this->kernelTime, &this->userTime);
    qulonglong usr, ker, idl, sys;
    usr = convertFileTime(userTime)   - convertFileTime(last_userTime);
    ker = convertFileTime(kernelTime) - convertFileTime(last_kernelTime);
    idl = convertFileTime(idleTime)   - convertFileTime(last_idleTime);
    sys = ker + usr;
    last_userTime = userTime;
    last_kernelTime = kernelTime;
    last_idleTime = idleTime;
    m_cpuUsage = (sys - idl) * 100 / sys;
#elif (defined(Q_OS_ANDROID) || defined(Q_OS_LINUX))
    //update cpu
    QFile file2("/proc/stat");
    file2.open(QIODevice::ReadOnly);
    QByteArray line2 = file2.readLine();
    file2.close();
    sscanf(line2.data(), "cpu %llu %llu %llu %llu", &totalUser, &totalUserNice, &totalSystem, &totalIdle);

    double overall = totalUser - last_totalUser;
    overall += totalUserNice - last_totalUserNice;
    overall += totalSystem - last_totalSystem;

    double total = overall + totalIdle - last_totalIdle;
    last_totalUser = totalUser;
    last_totalUserNice = totalUserNice;
    last_totalSystem = totalSystem;
    last_totalIdle = totalIdle;

    m_cpuUsage = (overall / total) * 100.0;
#endif

    emit cpuUsageChanged();
}

#ifdef Q_OS_WIN
qulonglong CpuInfo::convertFileTime(const FILETIME& filetime) const
{
    ULARGE_INTEGER largeInteger;
    largeInteger.LowPart = filetime.dwLowDateTime;
    largeInteger.HighPart = filetime.dwHighDateTime;
    return largeInteger.QuadPart;
}
#endif
