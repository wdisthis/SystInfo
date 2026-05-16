#include "Providers.hpp"
#include <iostream>

#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "iphlpapi.lib")

SystemProviders::SystemProviders() {
    InitCPU();
    InitNetwork();
}

SystemProviders::~SystemProviders() {
    if (m_cpuQuery) PdhCloseQuery(m_cpuQuery);
}

void SystemProviders::InitCPU() {
    PdhOpenQuery(NULL, 0, &m_cpuQuery);
    PdhAddEnglishCounterW(m_cpuQuery, L"\\Processor(_Total)\\% Processor Time", 0, &m_cpuCounter);
    PdhCollectQueryData(m_cpuQuery);
}

void SystemProviders::InitNetwork() {
    m_lastTime = GetTickCount64();
    UpdateNetwork();
}

void SystemProviders::Update() {
    m_metrics.cpuUsage = GetCPUUsage();
    UpdateRAM();
    UpdateNetwork();
    UpdateDisk();
}

float SystemProviders::GetCPUUsage() {
    PDH_FMT_COUNTERVALUE counterValue;
    PdhCollectQueryData(m_cpuQuery);
    PdhGetFormattedCounterValue(m_cpuCounter, PDH_FMT_DOUBLE, NULL, &counterValue);
    return (float)counterValue.doubleValue;
}

void SystemProviders::UpdateRAM() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    m_metrics.ramUsage = (float)memInfo.dwMemoryLoad;
}

void SystemProviders::UpdateNetwork() {
    PMIB_IF_TABLE2 table = nullptr;
    if (GetIfTable2(&table) == NO_ERROR) {
        unsigned long long currentIn = 0;
        unsigned long long currentOut = 0;

        for (unsigned long i = 0; i < table->NumEntries; i++) {
            if (table->Table[i].Type == IF_TYPE_ETHERNET_CSMACD || table->Table[i].Type == IF_TYPE_IEEE80211) {
                currentIn += table->Table[i].InOctets;
                currentOut += table->Table[i].OutOctets;
            }
        }

        unsigned long long currentTime = GetTickCount64();
        unsigned long long timeDiff = currentTime - m_lastTime;

        if (timeDiff > 0 && m_lastTime > 0) {
            m_metrics.netDownload = (currentIn - m_lastInBytes) * 1000 / timeDiff;
            m_metrics.netUpload = (currentOut - m_lastOutBytes) * 1000 / timeDiff;
        }

        m_lastInBytes = currentIn;
        m_lastOutBytes = currentOut;
        m_lastTime = currentTime;

        FreeMibTable(table);
    }
}

void SystemProviders::UpdateDisk() {
    ULARGE_INTEGER freeBytes, totalBytes, totalFreeBytes;
    
    if (GetDiskFreeSpaceExW(L"C:\\", &freeBytes, &totalBytes, &totalFreeBytes)) {
        m_metrics.diskCFree = (double)freeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
    } else {
        m_metrics.diskCFree = -1;
    }

    if (GetDiskFreeSpaceExW(L"D:\\", &freeBytes, &totalBytes, &totalFreeBytes)) {
        m_metrics.diskDFree = (double)freeBytes.QuadPart / (1024.0 * 1024.0 * 1024.0);
    } else {
        m_metrics.diskDFree = -1;
    }
}
