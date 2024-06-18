/*
 * This file manage the differences between several OS.
 * Copyright (C) 2020  Myrrhe <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "OsManager.hpp"
#include <istream>
#include <iostream>
#ifdef __linux__
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctime>
#elif _WIN32
#include <bit>
#include <direct.h>
#include <wtypes.h> // Need to be put before psapi.h
#include <psapi.h>
#include <Windows.h>
#include <winnt.h>
#elif _OSX

#endif // __linux__

long unsigned int OsManager::maxRAM;

#ifdef __linux__
const char OsManager::SlashC = '/';
const std::string OsManager::StrIcon = "iconl64.png";
const unsigned int OsManager::WidthIcon = 64;
const unsigned int OsManager::HeightIcon = 64;
#elif _WIN32
const char OsManager::SlashC = '\\';
const std::string OsManager::StrIcon = "iconw128.png";
const unsigned int OsManager::WidthIcon = 128;
const unsigned int OsManager::HeightIcon = 128;
#elif _OSX

#endif // __linux__

const std::string OsManager::Slash = std::string(1, OsManager::SlashC);

sf::Vector2<unsigned int> OsManager::getMonitorSize()
{
#ifdef __linux__
    Display *disp = XOpenDisplay(nullptr);
    Screen *scrn = DefaultScreenOfDisplay(disp);
    return sf::Vector2<unsigned int>(static_cast<unsigned int>(scrn->width, static_cast<unsigned int>(scrn->height)));
#elif _WIN32
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    return sf::Vector2<unsigned int>(static_cast<unsigned int>(desktop.bottom), static_cast<unsigned int>(desktop.right));
#elif _OSX

#endif // __linux__
}

double OsManager::getWallTime()
{
#ifdef __linux__
    timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return static_cast<double>(time.tv_sec) + static_cast<double>(time.tv_nsec) * 0.000000001;
#elif _WIN32
    LARGE_INTEGER time;
    LARGE_INTEGER freq;
    if (!QueryPerformanceFrequency(&freq))
    {
        //  Handle error
        return 0;
    }
    if (!QueryPerformanceCounter(&time))
    {
        //  Handle error
        return 0;
    }
    return static_cast<double>(time.QuadPart) / static_cast<double>(freq.QuadPart);
#elif _OSX

#endif // __linux__
}

double OsManager::getCpuTime()
{
#ifdef __linux__
    return static_cast<double>(std::clock()) / CLOCKS_PER_SEC;
#elif _WIN32
    FILETIME a;
    FILETIME b;
    FILETIME c;
    FILETIME d;
    if (GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0)
    {
        //  Returns total user time.
        //  Can be tweaked to include kernel times as well.
        return static_cast<double>(d.dwLowDateTime | (static_cast<uint64_t>(d.dwHighDateTime) << 32)) * 0.0000001;
    }
    else
    {
        //  Handle error
        return 0;
    }
#elif _OSX

#endif // __linux__
}

void OsManager::createDir(const std::string &str)
{
#ifdef __linux__
    mkdir(str.c_str(), 01777);
#elif _WIN32
    _mkdir(str.c_str());
#elif _OSX

#endif // __linux__
}

void OsManager::sleep(double nbUsec)
{
#ifdef __linux__
    usleep(static_cast<__useconds_t>(nbUsec));
#elif _WIN32
    HANDLE timer;
    LARGE_INTEGER ft;
    ft.QuadPart = -(10 * static_cast<long int>(nbUsec)); // Convert to 100 nanosecond interval, negative value indicates relative time
    timer = CreateWaitableTimer(nullptr, TRUE, nullptr);
    SetWaitableTimer(timer, &ft, 0, nullptr, nullptr, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
#elif _OSX

#endif // __linux__
}

void OsManager::initiateCoreFile()
{
#ifdef __linux__
    struct rlimit core_limits;
    core_limits.rlim_cur = core_limits.rlim_max = RLIM_INFINITY;
    setrlimit(RLIMIT_CORE, &core_limits);
#elif _WIN32

#elif _OSX

#endif // __linux__
}

long unsigned int OsManager::getPhysicalMemoryUsed()
{
#ifdef __linux__
    struct sysinfo memInfo;
    sysinfo(&memInfo);
    long unsigned int physMemUsed = memInfo.totalram - memInfo.freeram;
    // Multiply in next statement to avoid int overflow on right hand side...
    physMemUsed *= memInfo.mem_unit;
    return physMemUsed;
#elif _WIN32
    MEMORYSTATUSEX memInfo; //'MEMORYSTATUEX' was not declared in this scope
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return static_cast<long unsigned int>(memInfo.ullTotalPhys - memInfo.ullAvailPhys);
#elif _OSX

#endif // __linux__
}

long unsigned int OsManager::getPhysicalMemoryUsedProcess()
{
#ifdef __linux__
    // Note: this value is in kB !
    std::FILE *file = std::fopen("/proc/self/status", "r");
    long unsigned int result = 0ul;
    char line[128];
    while (std::fgets(line, 128, file) != NULL)
    {
        if (std::strncmp(line, "VmRSS:", 6) == 0)
        {
            // This assumes that a digit will be found and the line ends in " Kb".
            long unsigned int i = std::strlen(line);
            const char *p = line;
            while (*p < '0' || *p > '9')
            {
                p++;
            }
            line[i - 3] = '\0';
            result = std::strtoul(p, nullptr, 10);
            break;
        }
    }
    std::fclose(file);
    maxRAM = std::max(maxRAM, result); // Update the maximum RAM measured
    return result;
#elif _WIN32
    // Note: this value is in bits !
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS *>(&pmc), sizeof(pmc));
    maxRAM = std::max(maxRAM, static_cast<long unsigned int>(pmc.WorkingSetSize)); // Update the maximum RAM measured
    return static_cast<long unsigned int>(pmc.WorkingSetSize);
#elif _OSX

#endif // __linux__
}

long unsigned int OsManager::getMaxRAM()
{
    return maxRAM;
}
