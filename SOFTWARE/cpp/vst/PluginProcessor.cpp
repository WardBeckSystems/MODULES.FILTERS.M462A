#include "PluginProcessor.hpp"
#include <cmath>

namespace wbs::m462a {

M462APluginProcessor::M462APluginProcessor()
    : engine::SharedPluginFrame("Ward-Beck M462A Channel Equalizer", "M462A") {
    defaultOversampling_ = engine::OversamplingRate::TwoX;
}

void M462APluginProcessor::prepareModule(double hostRate, double oversampledRate, size_t maxBlockSize, size_t numChannels) {
    for (size_t ch = 0; ch < numChannels; ++ch) {
        opAmpStage_[ch].prepare(hostRate);
        lfFilter_[ch].prepare(oversampledRate);
        midFilter_[ch].prepare(oversampledRate);
        hfFilter_[ch].prepare(oversampledRate);
    }
    updateParametersFromHost();
}

void M462APluginProcessor::releaseModule() {
    for (size_t ch = 0; ch < numChannels_; ++ch) {
        opAmpStage_[ch].reset();
        lfFilter_[ch].reset();
        midFilter_[ch].reset();
        hfFilter_[ch].reset();
    }
}

void M462APluginProcessor::updateParametersFromHost() noexcept {
    for (size_t ch = 0; ch < numChannels_; ++ch) {
        lfFilter_[ch].update(lfFreq_, 0.707, lfGain_, engine::FilterType::LowShelf);
        midFilter_[ch].update(midFreq_, midQ_, midGain_, engine::FilterType::PeakingBell);
        hfFilter_[ch].update(hfFreq_, 0.707, hfGain_, engine::FilterType::HighShelf);
    }
}

void M462APluginProcessor::processModuleSlice(engine::AudioBlock& slice) noexcept {
    if (eqBypass_) return;

    for (size_t ch = 0; ch < slice.numChannels; ++ch) {
        float* channelData = slice.getChannelPointer(ch);

        for (size_t i = 0; i < slice.numSamples; ++i) {
            float s = channelData[i];

            // 1. 4-126 Op-Amp Discrete Front-End Saturation
            s = opAmpStage_[ch].processSample(s, drive_, 0.10f);

            // 2. LF Shelf
            s = lfFilter_[ch].processSample(s);

            // 3. Sweepable Mid Parametric Bell
            s = midFilter_[ch].processSample(s);

            // 4. HF Shelf
            s = hfFilter_[ch].processSample(s);

            channelData[i] = s;
        }
    }
}

void M462APluginProcessor::updateMeters(const engine::AudioBlock& audioBlock) noexcept {
    for (size_t ch = 0; ch < audioBlock.numChannels; ++ch) {
        const float* data = audioBlock.getChannelPointer(ch);
        float peak = 0.0f;
        for (size_t i = 0; i < audioBlock.numSamples; ++i) {
            peak = std::max(peak, std::abs(data[i]));
        }
        peakMeter_[ch] = (peakMeter_[ch] * 0.90f) + (peak * 0.10f);
    }
}

void M462APluginProcessor::setLfFrequencyToggle(bool highFreq) noexcept {
    lfFreq_ = highFreq ? 150.0f : 50.0f;
}

void M462APluginProcessor::setLfGainDb(float gainDb) noexcept {
    lfGain_ = std::clamp(gainDb, -14.0f, 14.0f);
}

void M462APluginProcessor::setMidFrequency(float freqHz) noexcept {
    midFreq_ = std::clamp(freqHz, 200.0f, 7000.0f);
}

void M462APluginProcessor::setMidQ(float q) noexcept {
    midQ_ = std::clamp(q, 0.6f, 2.5f);
}

void M462APluginProcessor::setMidGainDb(float gainDb) noexcept {
    midGain_ = std::clamp(gainDb, -14.0f, 14.0f);
}

void M462APluginProcessor::setHfFrequencyToggle(bool highFreq) noexcept {
    hfFreq_ = highFreq ? 10000.0f : 3000.0f;
}

void M462APluginProcessor::setHfGainDb(float gainDb) noexcept {
    hfGain_ = std::clamp(gainDb, -14.0f, 14.0f);
}

void M462APluginProcessor::setEqBypass(bool bypassed) noexcept {
    eqBypass_ = bypassed;
}

void M462APluginProcessor::setOpAmpDrive(float drivePercent) noexcept {
    drive_ = 1.0f + std::clamp(drivePercent / 100.0f, 0.0f, 2.0f);
}

} // namespace wbs::m462a
