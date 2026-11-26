#pragma once
#include "../core/SharedPluginFrame.hpp"
#include "../core/StateVariableCore.hpp"
#include "../core/NonLinearCore.hpp"

namespace wbs::m462a {

class M462APluginProcessor : public engine::SharedPluginFrame {
public:
    M462APluginProcessor();
    ~M462APluginProcessor() override = default;

    void prepareModule(double hostRate, double oversampledRate, size_t maxBlockSize, size_t numChannels) override;
    void releaseModule() override;
    void updateParametersFromHost() noexcept override;
    void processModuleSlice(engine::AudioBlock& slice) noexcept override;
    void updateMeters(const engine::AudioBlock& audioBlock) noexcept override;

    // Parameter setters
    void setLfFrequencyToggle(bool highFreq) noexcept; // false: 50 Hz, true: 150 Hz
    void setLfGainDb(float gainDb) noexcept;
    void setMidFrequency(float freqHz) noexcept;       // 200 Hz - 7000 Hz
    void setMidQ(float q) noexcept;                    // 0.6 - 2.5
    void setMidGainDb(float gainDb) noexcept;          // -14 to +14 dB
    void setHfFrequencyToggle(bool highFreq) noexcept; // false: 3 kHz, true: 10 kHz
    void setHfGainDb(float gainDb) noexcept;
    void setEqBypass(bool bypassed) noexcept;
    void setOpAmpDrive(float drivePercent) noexcept;

private:
    engine::StateVariableFilterCore lfFilter_[engine::kMaxChannels];
    engine::StateVariableFilterCore midFilter_[engine::kMaxChannels];
    engine::StateVariableFilterCore hfFilter_[engine::kMaxChannels];
    engine::NonLinearTransformerCore opAmpStage_[engine::kMaxChannels];

    float lfFreq_{ 150.0f };
    float lfGain_{ 0.0f };
    float midFreq_{ 1200.0f };
    float midQ_{ 1.2f };
    float midGain_{ 0.0f };
    float hfFreq_{ 10000.0f };
    float hfGain_{ 0.0f };
    bool eqBypass_{ false };
    float drive_{ 1.0f };

    float peakMeter_[engine::kMaxChannels]{ 0.0f };
};

} // namespace wbs::m462a
