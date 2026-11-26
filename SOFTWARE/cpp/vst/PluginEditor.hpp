#pragma once
#include "PluginProcessor.hpp"

namespace wbs::m462a {

class M462APluginEditor {
public:
    explicit M462APluginEditor(M462APluginProcessor& processor)
        : processor_(processor) {}

    void paint() const noexcept;
    void resized() noexcept;

    int getWidth() const noexcept { return 300; }
    int getHeight() const noexcept { return 650; }

private:
    M462APluginProcessor& processor_;
};

} // namespace wbs::m462a
