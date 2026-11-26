# Ward-Beck Systems M462A Channel Equalizer VST/AU Plugin

**Hardware Unit:** Ward-Beck Systems M462A Channel Strip Equalizer (Drawing `462-04-006`, ca. 1974)  
**Format:** VST3, AU, AAX (C++20 / JUCE 7)  
**Core Shared Engine:** [`wbs_core`](file:///home/anthony/Documents/GitProjects/WBSps.ca/2030.env/vst/core/README.md)

---

## Technical Specifications
- **Mid Band:** Continuous sweep $200\text{ Hz}$ to $7.0\text{ kHz}$ (35:1 reverse-log tuning), variable $Q$ ($0.6$ to $2.5$), $\pm14\text{ dB}$ gain.
- **Low Shelf:** Selectable turnover $50\text{ Hz}$ / $150\text{ Hz}$, $\pm14\text{ dB}$.
- **High Shelf:** Selectable turnover $3.0\text{ kHz}$ / $10.0\text{ kHz}$, $\pm14\text{ dB}$.
- **Sub-Board Emulation:** 4-126 state-variable filter daughtercard with discrete front-end op-amp saturation.
