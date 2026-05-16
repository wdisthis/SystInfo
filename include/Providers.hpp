#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <pdh.h>

struct SystemMetrics {
    float cpuUsage;
    float ramUsage;
    long long netDownload;
    long long netUpload;
    double diskCFree;
    double diskDFree;
};

class SystemProviders {
public:
    SystemProviders();
    ~SystemProviders();

    void Update();
    const SystemMetrics& GetMetrics() const { return m_metrics; }

private:
    void InitCPU();
    void InitNetwork();
    
    float GetCPUUsage();
    void UpdateRAM();
    void UpdateNetwork();
    void UpdateDisk();

    SystemMetrics m_metrics;

    PDH_HQUERY m_cpuQuery;
    PDH_HCOUNTER m_cpuCounter;

    unsigned long long m_lastInBytes = 0;
    unsigned long long m_lastOutBytes = 0;
    unsigned long long m_lastTime = 0;
};
