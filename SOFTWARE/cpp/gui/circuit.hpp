// M462A: its block of 2030.env/vst/core/CircuitDiagramDefinitions.hpp.

        case 2: // M462A Channel EQ
            d.modelCode = "M462A";
            d.circuitTitle = "Ward-Beck M462A 3-Band Broadcast Channel EQ";
            d.theoreticalExplanation =
                "Broadcast console channel strip EQ. Features selectable 50/150 Hz LF and 3k/10k HF Baxandall shelving filters, "
                "paired with a continuous Kerwin-Huelsman-Newcomb (KHN) state-variable bandpass filter (200 Hz - 7 kHz, Q 0.6 - 2.5).";
            d.nodes = {
                { "IN",  "Active In",   "Diff Amp",       { 20, 20, 90, 48 }, true, Palette::CircuitBorder },
                { "LF",  "Baxandall LF","50 / 150 Hz",    { 130, 20, 100, 48 }, true, Palette::TextGold },
                { "MID", "KHN Swept",   "200Hz-7kHz Q",   { 250, 20, 110, 48 }, true, Palette::CircuitHighlight },
                { "HF",  "Baxandall HF","3k / 10k Hz",    { 380, 20, 100, 48 }, true, Palette::TextGold },
                { "OUT", "Op-Amp Out",  "Discrete Driver",{ 500, 20, 90, 48 }, true, Palette::LedGreen }
            };
            d.wires = {
                { "IN", "LF", "Audio In" },
                { "LF", "MID", "LF Shaped" },
                { "MID", "HF", "Mid Peak" },
                { "HF", "OUT", "Summed" }
            };
            break;
