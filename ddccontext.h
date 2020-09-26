#ifndef DDCCONTEXT_H
#define DDCCONTEXT_H
#include <mutex>
#include <map>
#include <random>
#include <vector>
#include "Biquad.h"

class DDCContext
{
public:
    DDCContext();
    bool AddFilter(uint32_t id, Biquad::Type type,int nFreq, double dGain, double dBandwidth, double dSRate, bool isBWorS);
    bool AddFilter(uint32_t id, customFilter_t c441, customFilter_t c48);
    bool ModifyFilter(uint32_t id, Biquad::Type type,int nFreq, double dGain, double dBandwidth, double dSRate, bool isBWorS);
    bool ModifyFilter(uint32_t id, customFilter_t c441, customFilter_t c48);
    void ClearFilters();
    bool RemoveFilter(uint32_t id);
    bool Exists(uint32_t id);
    uint32_t GenerateId();
    const Biquad* GetFilter(uint32_t id);
    std::vector<float> GetMagnitudeResponseTable(int nBandCount, double dSRate);
    std::vector<float> GetPhaseResponseTable(int nBandCount, double dSRate);
    std::vector<float> GetGroupDelayTable(int nBandCount, double dSRate);
    std::list<double> ExportCoeffs(double dSamplingRate);

    std::map<int, Biquad*> GetFilterBank() const{
        return m_lstFilterBank;
    };

private:
    std::mutex mtx;
    std::map<int,Biquad*> m_lstFilterBank;
    std::mt19937 mt;
    std::uniform_int_distribution<uint32_t> rnd;
    void LockFilter();
    void UnlockFilter();
};

#endif // DDCCONTEXT_H
