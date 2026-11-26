// Copyright (c) 2026 Ward-Beck Systems (Ward-Beck.com - Ward-Beck.ca). All rights reserved.
// M462A: its part of 2030.env/vst/clap_wrapper/ClapModuleRegistry.cpp (suite index 2).

// --- descriptor ---
static const clap_plugin_descriptor_t s_desc_m462a = {
    CLAP_VERSION,
    "ca.wbsps.m462a_channel_eq",
    "Ward-Beck M462A Channel Equalizer",
    "Ward-Beck Systems Preservation Society",
    "https://wbsps.ca",
    "",
    "https://wbsps.ca/contact",
    "1.0.0",
    "3-band channel strip equalizer with switchable shelving and sweepable mid",
    kEqFeatures
};

// --- parameters ---
std::vector<ParameterInfo> buildM462AParams() {
    std::vector<ParameterInfo> p;
    p.push_back({
        0, "LF Frequency Select", "Low Band", 0.0, 1.0, 1.0,
        CLAP_PARAM_IS_AUTOMATABLE | CLAP_PARAM_IS_STEPPED,
        [](engine::SharedPluginFrame* f, double val) { static_cast<m462a::M462APluginProcessor*>(f)->setLfFrequencyToggle(val >= 0.5); },
        nullptr,
        [](double v) { return v >= 0.5 ? "150 Hz" : "50 Hz"; },
        nullptr
    });
    p.push_back({
        1, "LF Gain", "Low Band", -14.0, 14.0, 0.0,
        CLAP_PARAM_IS_AUTOMATABLE,
        [](engine::SharedPluginFrame* f, double val) { static_cast<m462a::M462APluginProcessor*>(f)->setLfGainDb(static_cast<float>(val)); },
        nullptr,
        [](double v) { char buf[32]; std::snprintf(buf, sizeof(buf), "%+.1f dB", v); return std::string(buf); },
        nullptr
    });
    p.push_back({
        2, "Mid Frequency", "Mid Band", 200.0, 7000.0, 1200.0,
        CLAP_PARAM_IS_AUTOMATABLE,
        [](engine::SharedPluginFrame* f, double val) { static_cast<m462a::M462APluginProcessor*>(f)->setMidFrequency(static_cast<float>(val)); },
        nullptr,
        [](double v) { char buf[32]; std::snprintf(buf, sizeof(buf), "%.0f Hz", v); return std::string(buf); },
        nullptr
    });
    p.push_back({
        3, "Mid Q", "Mid Band", 0.6, 2.5, 1.2,
        CLAP_PARAM_IS_AUTOMATABLE,
        [](engine::SharedPluginFrame* f, double val) { static_cast<m462a::M462APluginProcessor*>(f)->setMidQ(static_cast<float>(val)); },
        nullptr,
        [](double v) { char buf[32]; std::snprintf(buf, sizeof(buf), "%.2f", v); return std::string(buf); },
        nullptr
    });
    p.push_back({
        4, "Mid Gain", "Mid Band", -14.0, 14.0, 0.0,
        CLAP_PARAM_IS_AUTOMATABLE,
        [](engine::SharedPluginFrame* f, double val) { static_cast<m462a::M462APluginProcessor*>(f)->setMidGainDb(static_cast<float>(val)); },
        nullptr,
        [](double v) { char buf[32]; std::snprintf(buf, sizeof(buf), "%+.1f dB", v); return std::string(buf); },
        nullptr
    });
    p.push_back({
        5, "HF Frequency Select", "High Band", 0.0, 1.0, 1.0,
        CLAP_PARAM_IS_AUTOMATABLE | CLAP_PARAM_IS_STEPPED,
        [](engine::SharedPluginFrame* f, double val) { static_cast<m462a::M462APluginProcessor*>(f)->setHfFrequencyToggle(val >= 0.5); },
        nullptr,
        [](double v) { return v >= 0.5 ? "10 kHz" : "3 kHz"; },
        nullptr
    });
    p.push_back({
        6, "HF Gain", "High Band", -14.0, 14.0, 0.0,
        CLAP_PARAM_IS_AUTOMATABLE,
        [](engine::SharedPluginFrame* f, double val) { static_cast<m462a::M462APluginProcessor*>(f)->setHfGainDb(static_cast<float>(val)); },
        nullptr,
        [](double v) { char buf[32]; std::snprintf(buf, sizeof(buf), "%+.1f dB", v); return std::string(buf); },
        nullptr
    });
    p.push_back({
        7, "EQ Bypass", "Master", 0.0, 1.0, 0.0,
        CLAP_PARAM_IS_AUTOMATABLE | CLAP_PARAM_IS_STEPPED | CLAP_PARAM_IS_BYPASS,
        [](engine::SharedPluginFrame* f, double val) { static_cast<m462a::M462APluginProcessor*>(f)->setEqBypass(val >= 0.5); },
        nullptr,
        [](double v) { return v >= 0.5 ? "Bypassed" : "Active"; },
        nullptr
    });
    p.push_back({
        8, "OpAmp Drive", "Saturation", 0.0, 100.0, 20.0,
        CLAP_PARAM_IS_AUTOMATABLE,
        [](engine::SharedPluginFrame* f, double val) { static_cast<m462a::M462APluginProcessor*>(f)->setOpAmpDrive(static_cast<float>(val)); },
        nullptr,
        [](double v) { char buf[32]; std::snprintf(buf, sizeof(buf), "%.1f %%", v); return std::string(buf); },
        nullptr
    });
    return p;
}

// --- instance ---
        case 2:
            inst = new ClapPluginInstance(
                &s_desc_m462a, host,
                []() { return std::make_unique<m462a::M462APluginProcessor>(); },
                buildM462AParams(),
                2
            );
            break;

