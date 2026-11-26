# Ward-Beck Systems M462A Channel Equalizer - VST/AU Plugin Build Plan

**Module Name:** WBS M462A 3-Band Channel Strip Equalizer  
**Hardware Reference:** Ward-Beck Systems M462A Console Channel EQ (Drawing `462-04-006`, ca. 1974–1978)  
**Target Architecture:** VST3 / AU / AAX (JUCE 7 / C++20)  
**Shared Engine Dependency:** [`wbs::SharedPluginFrame`](file:///home/anthony/Documents/GitProjects/WBSps.ca/2030.env/engine/SharedPluginFrame.hpp), [`wbs::StateVariableCore`](file:///home/anthony/Documents/GitProjects/WBSps.ca/2030.env/engine/StateVariableCore.hpp), [`wbs::NonLinearCore`](file:///home/anthony/Documents/GitProjects/WBSps.ca/2030.env/engine/NonLinearCore.hpp)

---

## 1. Hardware Architecture & Circuit Analysis

The M462A was the primary channel equalizer installed in Ward-Beck 80-series broadcast consoles (e.g., standard M460 channel strips). Based on the proprietary **4-126 active sub-board**, it replaced bulky inductors with high-reliability state-variable op-amp circuits utilizing low-noise discrete front-ends and selected dual op-amps (Signetics NE5534 / Harris HA-911).

### Section Breakdown
1. **Low Frequency (LF) Section:**
   - Active shelving filter with selectable turnover frequencies: **$50\text{ Hz}$** and **$150\text{ Hz}$**.
   - Boost/Cut: $\pm14\text{ dB}$ via continuous conductive plastic potentiometer.
2. **Mid Frequency (MF) Section:**
   - Continuously sweepable center frequency: **$200\text{ Hz}$ to $7.0\text{ kHz}$** (35:1 tuning ratio via dual-gang reverse-log potentiometer).
   - Continuously variable bandwidth control ($Q$): **$0.6$ to $2.5$**.
   - Boost/Cut: $\pm14\text{ dB}$ reciprocal bell curve.
3. **High Frequency (HF) Section:**
   - Active shelving filter with selectable turnover: **$3.0\text{ kHz}$** and **$10.0\text{ kHz}$**.
   - Boost/Cut: $\pm14\text{ dB}$ continuous.
4. **Active EQ In/Out Bypass Switch:**
   - Relay-driven hardware bypass routing around the active filter stages to avoid phase shift when disengaged.

---

## 2. DSP Architecture & Mathematical Model

The M462A utilizes our shared zero-delay feedback (ZDF) state-variable core [`wbs::StateVariableCore`](file:///home/anthony/Documents/GitProjects/WBSps.ca/2030.env/engine/StateVariableCore.hpp).

### 2.1 Mid-Band State-Variable Calculation
The continuous-time transfer function of the Kerwin-Huelsman-Newcomb (KHN) band-pass state variable filter is:
$$H_{BP}(s) = \frac{\frac{\omega_0}{Q}s}{s^2 + \frac{\omega_0}{Q}s + \omega_0^2}$$
For equalized bell boost/cut with gain $G = 10^{\frac{\text{Gain}_{dB}}{20}}$:
$$y[n] = x[n] + (G - 1.0) \cdot y_{BP}[n]$$

In our ZDF trapezoidal integration, the tuning coefficient $g$ and damping $R$ are calculated as:
$$g = \tan\left(\frac{\pi f_0}{f_s}\right), \quad R = \frac{1}{Q}$$
The state update equations are evaluated per sample with zero latency.

### 2.2 Shelving Bands
The LF and HF shelves are modeled as 1st-order active feedback Shelving filters with smooth phase transitions matching the 4-126 analog daughtercard:
$$H_{shelf}(s) = \frac{s + \sqrt{G}\omega_c}{\sqrt{G}s + \omega_c} \quad (\text{for boost})$$

---

## 3. Parameter Mapping & State Architecture

| ID | Parameter Name | Range | Steps / Type | Default | Unit |
|---|---|---|---|---|---|
| `m462a_lf_freq_sel` | LF Turnover | 50, 150 | 2-way toggle | 150 | Hz |
| `m462a_lf_gain` | LF Shelf Gain | $-14.0$ to $+14.0$ | Continuous | 0.0 | dB |
| `m462a_mid_freq` | Mid Center Freq | $200.0$ to $7000.0$ | Continuous (Log) | 1200.0 | Hz |
| `m462a_mid_q` | Mid Bandwidth Q | $0.6$ to $2.5$ | Continuous | 1.2 | Q |
| `m462a_mid_gain` | Mid Bell Gain | $-14.0$ to $+14.0$ | Continuous | 0.0 | dB |
| `m462a_hf_freq_sel` | HF Turnover | 3000, 10000 | 2-way toggle | 10000 | Hz |
| `m462a_hf_gain` | HF Shelf Gain | $-14.0$ to $+14.0$ | Continuous | 0.0 | dB |
| `m462a_eq_in` | EQ Engage Switch | Off / On | Toggle | On | Bool |
| `m462a_opamp_drive`| 4-126 Op-Amp Sat | $0.0$ to $100.0$ | Continuous | 15.0 | % |

---

## 4. C++ Plugin Scaffolding

```cpp
// M462AEqualizerProcessor.hpp
#pragma once
#include "SharedPluginFrame.hpp"
#include "StateVariableCore.hpp"
#include "NonLinearCore.hpp"

namespace wbs {

class M462AEqualizerProcessor : public SharedPluginFrame {
public:
    M462AEqualizerProcessor();
    ~M462AEqualizerProcessor() override = default;

    const char* getPluginIdentifier() const noexcept override { return "WBS_M462A_Channel_EQ"; }
    uint32_t getPluginVersion() const noexcept override { return 0x010000; }

    void prepareHardwareState(double sampleRate, uint32_t maxBlockSize) override;
    void resetHardwareState() override;
    void processAudioCore(AudioBlock<float>& block) override;

private:
    StateVariableCore midZdf_[2];
    
    // First-order shelving states
    float lfState_[2] = { 0.0f, 0.0f };
    float hfState_[2] = { 0.0f, 0.0f };

    NonLinearCore opAmpStage_;
};

} // namespace wbs
```

---

## 5. UI/UX Specification

- **Module Format:** Vertical 1.5" console strip layout mirroring the physical M460 channel strip.
- **Colorway:** Charcoal matte faceplate `#2B2D31`, silk-screened frequency indicators in cream `#E6E1D5`.
- **Potentiometers:** Fluted concentric dials with colored indicator rings: Blue (LF), Yellow (Mid), Red (HF).
- **Toggle Switches:** Chrome bat switches with satisfying click physics.

---

## 6. Verification & Test Plan

1. **Mid Sweep Linearity:** Sweep mid frequency from $200\text{ Hz}$ to $7.0\text{ kHz}$ at $+10\text{ dB}$; ensure filter peak frequency matches parameter within $1.0\%$.
2. **Q-Bandwidth Stability:** Set $Q = 2.5$ and sweep through Nyquist boundary ($0.45 f_s$); verify zero ringing, zero explosive poles, and stable ZDF convergence.
3. **Pass-Through Phase Coherence:** In disengaged state (`EQ IN` = false), verify total cancellation ($< -120\text{ dB}$) against a bit-exact inverted dry signal.
