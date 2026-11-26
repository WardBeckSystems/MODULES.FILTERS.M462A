// M462A: its block of 2030.env/vst/core/ModuleGuiLayouts.hpp (176 x 770 = the faceplate).

        case 2: { // M462A Channel EQ (176 x 770, matching M462A.jpg & M436L recall.dxf)
            m.title = "M462A Channel EQ";
            m.subtitle = "4-Band Broadcast ZDF State-Variable Console EQ";
            m.modelCode = "M462A";

            // Band 1: High Frequency (HF) - Top is Red
            m.knobs.push_back({ 6, "HF GAIN", "dB", 50.0f, 95.0f, 22.0f, -14.0, 14.0, 0.0, false, KnobStyle::WbsElmaWing, Palette::ElmaRed });
            m.buttons.push_back({ 7, "HF SHELF", { 98.0f, 83.0f, 64.0f, 24.0f }, false, ButtonStyle::LatchingPush, Palette::LedAmber });

            // Band 2: Mid Frequency (MID ZDF Parametric) - Mid is Yellow
            m.knobs.push_back({ 2, "MID FREQ", "Hz", 50.0f, 185.0f, 22.0f, 200.0, 7000.0, 1200.0, false, KnobStyle::WbsElmaPointer, Palette::ElmaYellow });
            m.knobs.push_back({ 4, "MID GAIN", "dB", 126.0f, 185.0f, 22.0f, -14.0, 14.0, 0.0, false, KnobStyle::WbsElmaWing, Palette::ElmaYellow });
            m.knobs.push_back({ 3, "MID Q", "", 88.0f, 260.0f, 18.0f, 0.6, 2.5, 1.2, false, KnobStyle::WbsElmaRegular, Palette::ElmaSlate });

            // Band 3: Low Frequency (LF) - Low is Green
            m.knobs.push_back({ 1, "LF GAIN", "dB", 50.0f, 345.0f, 22.0f, -14.0, 14.0, 0.0, false, KnobStyle::WbsElmaWing, Palette::ElmaGreen });
            m.buttons.push_back({ 0, "50/150", { 98.0f, 333.0f, 64.0f, 24.0f }, false, ButtonStyle::LatchingPush, Palette::LedAmber });
            m.buttons.push_back({ 5, "LF SHELF", { 43.0f, 395.0f, 90.0f, 24.0f }, false, ButtonStyle::LatchingPush, Palette::LedAmber });

            // Drive & Saturation
            m.knobs.push_back({ 8, "OPAMP SAT", "%", 88.0f, 480.0f, 22.0f, 0.0, 100.0, 20.0, false, KnobStyle::WbsElmaPointer, Palette::ElmaAmber });

            // Master EQ In / Bypass Switch - RED button is eq ON
            m.buttons.push_back({ 9, "EQ IN", { 43.0f, 560.0f, 90.0f, 28.0f }, true, ButtonStyle::LatchingPush, Palette::LedRed });

            m.themeToggleRect = { 25.0f, 726.0f, 126.0f, 22.0f };
            break;
        }
