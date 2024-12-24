
#include "Simulator.h"
#include <cstdlib>
#include <unordered_map>
#include <variant>
#include <string>
#include <iostream>
#include <vector>

#define FLOAT float
#define DOUBLE double

void replaceBrackets(std::string& input) {
    for (char& c : input) {
        if (c == '(') c = '<';
        else if (c == ')') c = '>';
    }
}

using FluidSimulatorVariant = std::variant<Simulator<FLOAT, FLOAT, FLOAT, 17, 84>, Simulator<FLOAT, FLOAT, FLOAT, 14, 5>, Simulator<FLOAT, FLOAT, FAST_FIXED<13,7>, 17, 84>, Simulator<FLOAT, FLOAT, FAST_FIXED<13,7>, 14, 5>, Simulator<FLOAT, FLOAT, FIXED<64,15>, 17, 84>, Simulator<FLOAT, FLOAT, FIXED<64,15>, 14, 5>, Simulator<FLOAT, FAST_FIXED<13,7>, FLOAT, 17, 84>, Simulator<FLOAT, FAST_FIXED<13,7>, FLOAT, 14, 5>, Simulator<FLOAT, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 17, 84>, Simulator<FLOAT, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 14, 5>, Simulator<FLOAT, FAST_FIXED<13,7>, FIXED<64,15>, 17, 84>, Simulator<FLOAT, FAST_FIXED<13,7>, FIXED<64,15>, 14, 5>, Simulator<FLOAT, FIXED<64,15>, FLOAT, 17, 84>, Simulator<FLOAT, FIXED<64,15>, FLOAT, 14, 5>, Simulator<FLOAT, FIXED<64,15>, FAST_FIXED<13,7>, 17, 84>, Simulator<FLOAT, FIXED<64,15>, FAST_FIXED<13,7>, 14, 5>, Simulator<FLOAT, FIXED<64,15>, FIXED<64,15>, 17, 84>, Simulator<FLOAT, FIXED<64,15>, FIXED<64,15>, 14, 5>, Simulator<FAST_FIXED<13,7>, FLOAT, FLOAT, 17, 84>, Simulator<FAST_FIXED<13,7>, FLOAT, FLOAT, 14, 5>, Simulator<FAST_FIXED<13,7>, FLOAT, FAST_FIXED<13,7>, 17, 84>, Simulator<FAST_FIXED<13,7>, FLOAT, FAST_FIXED<13,7>, 14, 5>, Simulator<FAST_FIXED<13,7>, FLOAT, FIXED<64,15>, 17, 84>, Simulator<FAST_FIXED<13,7>, FLOAT, FIXED<64,15>, 14, 5>, Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FLOAT, 17, 84>, Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FLOAT, 14, 5>, Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 17, 84>, Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 14, 5>, Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FIXED<64,15>, 17, 84>, Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FIXED<64,15>, 14, 5>, Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FLOAT, 17, 84>, Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FLOAT, 14, 5>, Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FAST_FIXED<13,7>, 17, 84>, Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FAST_FIXED<13,7>, 14, 5>, Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FIXED<64,15>, 17, 84>, Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FIXED<64,15>, 14, 5>, Simulator<FIXED<64,15>, FLOAT, FLOAT, 17, 84>, Simulator<FIXED<64,15>, FLOAT, FLOAT, 14, 5>, Simulator<FIXED<64,15>, FLOAT, FAST_FIXED<13,7>, 17, 84>, Simulator<FIXED<64,15>, FLOAT, FAST_FIXED<13,7>, 14, 5>, Simulator<FIXED<64,15>, FLOAT, FIXED<64,15>, 17, 84>, Simulator<FIXED<64,15>, FLOAT, FIXED<64,15>, 14, 5>, Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FLOAT, 17, 84>, Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FLOAT, 14, 5>, Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 17, 84>, Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 14, 5>, Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FIXED<64,15>, 17, 84>, Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FIXED<64,15>, 14, 5>, Simulator<FIXED<64,15>, FIXED<64,15>, FLOAT, 17, 84>, Simulator<FIXED<64,15>, FIXED<64,15>, FLOAT, 14, 5>, Simulator<FIXED<64,15>, FIXED<64,15>, FAST_FIXED<13,7>, 17, 84>, Simulator<FIXED<64,15>, FIXED<64,15>, FAST_FIXED<13,7>, 14, 5>, Simulator<FIXED<64,15>, FIXED<64,15>, FIXED<64,15>, 17, 84>, Simulator<FIXED<64,15>, FIXED<64,15>, FIXED<64,15>, 14, 5>>;

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, int> params = { {"FLOAT, FLOAT, FLOAT, 17, 84", 0}, {"FLOAT, FLOAT, FLOAT, 14, 5", 1}, {"FLOAT, FLOAT, FAST_FIXED<13,7>, 17, 84", 2}, {"FLOAT, FLOAT, FAST_FIXED<13,7>, 14, 5", 3}, {"FLOAT, FLOAT, FIXED<64,15>, 17, 84", 4}, {"FLOAT, FLOAT, FIXED<64,15>, 14, 5", 5}, {"FLOAT, FAST_FIXED<13,7>, FLOAT, 17, 84", 6}, {"FLOAT, FAST_FIXED<13,7>, FLOAT, 14, 5", 7}, {"FLOAT, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 17, 84", 8}, {"FLOAT, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 14, 5", 9}, {"FLOAT, FAST_FIXED<13,7>, FIXED<64,15>, 17, 84", 10}, {"FLOAT, FAST_FIXED<13,7>, FIXED<64,15>, 14, 5", 11}, {"FLOAT, FIXED<64,15>, FLOAT, 17, 84", 12}, {"FLOAT, FIXED<64,15>, FLOAT, 14, 5", 13}, {"FLOAT, FIXED<64,15>, FAST_FIXED<13,7>, 17, 84", 14}, {"FLOAT, FIXED<64,15>, FAST_FIXED<13,7>, 14, 5", 15}, {"FLOAT, FIXED<64,15>, FIXED<64,15>, 17, 84", 16}, {"FLOAT, FIXED<64,15>, FIXED<64,15>, 14, 5", 17}, {"FAST_FIXED<13,7>, FLOAT, FLOAT, 17, 84", 18}, {"FAST_FIXED<13,7>, FLOAT, FLOAT, 14, 5", 19}, {"FAST_FIXED<13,7>, FLOAT, FAST_FIXED<13,7>, 17, 84", 20}, {"FAST_FIXED<13,7>, FLOAT, FAST_FIXED<13,7>, 14, 5", 21}, {"FAST_FIXED<13,7>, FLOAT, FIXED<64,15>, 17, 84", 22}, {"FAST_FIXED<13,7>, FLOAT, FIXED<64,15>, 14, 5", 23}, {"FAST_FIXED<13,7>, FAST_FIXED<13,7>, FLOAT, 17, 84", 24}, {"FAST_FIXED<13,7>, FAST_FIXED<13,7>, FLOAT, 14, 5", 25}, {"FAST_FIXED<13,7>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 17, 84", 26}, {"FAST_FIXED<13,7>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 14, 5", 27}, {"FAST_FIXED<13,7>, FAST_FIXED<13,7>, FIXED<64,15>, 17, 84", 28}, {"FAST_FIXED<13,7>, FAST_FIXED<13,7>, FIXED<64,15>, 14, 5", 29}, {"FAST_FIXED<13,7>, FIXED<64,15>, FLOAT, 17, 84", 30}, {"FAST_FIXED<13,7>, FIXED<64,15>, FLOAT, 14, 5", 31}, {"FAST_FIXED<13,7>, FIXED<64,15>, FAST_FIXED<13,7>, 17, 84", 32}, {"FAST_FIXED<13,7>, FIXED<64,15>, FAST_FIXED<13,7>, 14, 5", 33}, {"FAST_FIXED<13,7>, FIXED<64,15>, FIXED<64,15>, 17, 84", 34}, {"FAST_FIXED<13,7>, FIXED<64,15>, FIXED<64,15>, 14, 5", 35}, {"FIXED<64,15>, FLOAT, FLOAT, 17, 84", 36}, {"FIXED<64,15>, FLOAT, FLOAT, 14, 5", 37}, {"FIXED<64,15>, FLOAT, FAST_FIXED<13,7>, 17, 84", 38}, {"FIXED<64,15>, FLOAT, FAST_FIXED<13,7>, 14, 5", 39}, {"FIXED<64,15>, FLOAT, FIXED<64,15>, 17, 84", 40}, {"FIXED<64,15>, FLOAT, FIXED<64,15>, 14, 5", 41}, {"FIXED<64,15>, FAST_FIXED<13,7>, FLOAT, 17, 84", 42}, {"FIXED<64,15>, FAST_FIXED<13,7>, FLOAT, 14, 5", 43}, {"FIXED<64,15>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 17, 84", 44}, {"FIXED<64,15>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 14, 5", 45}, {"FIXED<64,15>, FAST_FIXED<13,7>, FIXED<64,15>, 17, 84", 46}, {"FIXED<64,15>, FAST_FIXED<13,7>, FIXED<64,15>, 14, 5", 47}, {"FIXED<64,15>, FIXED<64,15>, FLOAT, 17, 84", 48}, {"FIXED<64,15>, FIXED<64,15>, FLOAT, 14, 5", 49}, {"FIXED<64,15>, FIXED<64,15>, FAST_FIXED<13,7>, 17, 84", 50}, {"FIXED<64,15>, FIXED<64,15>, FAST_FIXED<13,7>, 14, 5", 51}, {"FIXED<64,15>, FIXED<64,15>, FIXED<64,15>, 17, 84", 52}, {"FIXED<64,15>, FIXED<64,15>, FIXED<64,15>, 14, 5", 53} };
    std::vector<FluidSimulatorVariant> arr = { Simulator<FLOAT, FLOAT, FLOAT, 17, 84>(), Simulator<FLOAT, FLOAT, FLOAT, 14, 5>(), Simulator<FLOAT, FLOAT, FAST_FIXED<13,7>, 17, 84>(), Simulator<FLOAT, FLOAT, FAST_FIXED<13,7>, 14, 5>(), Simulator<FLOAT, FLOAT, FIXED<64,15>, 17, 84>(), Simulator<FLOAT, FLOAT, FIXED<64,15>, 14, 5>(), Simulator<FLOAT, FAST_FIXED<13,7>, FLOAT, 17, 84>(), Simulator<FLOAT, FAST_FIXED<13,7>, FLOAT, 14, 5>(), Simulator<FLOAT, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 17, 84>(), Simulator<FLOAT, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 14, 5>(), Simulator<FLOAT, FAST_FIXED<13,7>, FIXED<64,15>, 17, 84>(), Simulator<FLOAT, FAST_FIXED<13,7>, FIXED<64,15>, 14, 5>(), Simulator<FLOAT, FIXED<64,15>, FLOAT, 17, 84>(), Simulator<FLOAT, FIXED<64,15>, FLOAT, 14, 5>(), Simulator<FLOAT, FIXED<64,15>, FAST_FIXED<13,7>, 17, 84>(), Simulator<FLOAT, FIXED<64,15>, FAST_FIXED<13,7>, 14, 5>(), Simulator<FLOAT, FIXED<64,15>, FIXED<64,15>, 17, 84>(), Simulator<FLOAT, FIXED<64,15>, FIXED<64,15>, 14, 5>(), Simulator<FAST_FIXED<13,7>, FLOAT, FLOAT, 17, 84>(), Simulator<FAST_FIXED<13,7>, FLOAT, FLOAT, 14, 5>(), Simulator<FAST_FIXED<13,7>, FLOAT, FAST_FIXED<13,7>, 17, 84>(), Simulator<FAST_FIXED<13,7>, FLOAT, FAST_FIXED<13,7>, 14, 5>(), Simulator<FAST_FIXED<13,7>, FLOAT, FIXED<64,15>, 17, 84>(), Simulator<FAST_FIXED<13,7>, FLOAT, FIXED<64,15>, 14, 5>(), Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FLOAT, 17, 84>(), Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FLOAT, 14, 5>(), Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 17, 84>(), Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 14, 5>(), Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FIXED<64,15>, 17, 84>(), Simulator<FAST_FIXED<13,7>, FAST_FIXED<13,7>, FIXED<64,15>, 14, 5>(), Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FLOAT, 17, 84>(), Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FLOAT, 14, 5>(), Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FAST_FIXED<13,7>, 17, 84>(), Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FAST_FIXED<13,7>, 14, 5>(), Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FIXED<64,15>, 17, 84>(), Simulator<FAST_FIXED<13,7>, FIXED<64,15>, FIXED<64,15>, 14, 5>(), Simulator<FIXED<64,15>, FLOAT, FLOAT, 17, 84>(), Simulator<FIXED<64,15>, FLOAT, FLOAT, 14, 5>(), Simulator<FIXED<64,15>, FLOAT, FAST_FIXED<13,7>, 17, 84>(), Simulator<FIXED<64,15>, FLOAT, FAST_FIXED<13,7>, 14, 5>(), Simulator<FIXED<64,15>, FLOAT, FIXED<64,15>, 17, 84>(), Simulator<FIXED<64,15>, FLOAT, FIXED<64,15>, 14, 5>(), Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FLOAT, 17, 84>(), Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FLOAT, 14, 5>(), Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 17, 84>(), Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FAST_FIXED<13,7>, 14, 5>(), Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FIXED<64,15>, 17, 84>(), Simulator<FIXED<64,15>, FAST_FIXED<13,7>, FIXED<64,15>, 14, 5>(), Simulator<FIXED<64,15>, FIXED<64,15>, FLOAT, 17, 84>(), Simulator<FIXED<64,15>, FIXED<64,15>, FLOAT, 14, 5>(), Simulator<FIXED<64,15>, FIXED<64,15>, FAST_FIXED<13,7>, 17, 84>(), Simulator<FIXED<64,15>, FIXED<64,15>, FAST_FIXED<13,7>, 14, 5>(), Simulator<FIXED<64,15>, FIXED<64,15>, FIXED<64,15>, 17, 84>(), Simulator<FIXED<64,15>, FIXED<64,15>, FIXED<64,15>, 14, 5>() };

    std::string p_type, v_type, v_flow_type, size;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("--p-type=") == 0) p_type = arg.substr(9);
        else if (arg.find("--v-type=") == 0) v_type = arg.substr(9);
        else if (arg.find("--v-flow-type=") == 0) v_flow_type = arg.substr(14);
        else if (arg.find("--size=") == 0) size = arg.substr(7);
    }

    std::string args_str = p_type + " " + v_type + " " + v_flow_type + ", " + size;
    replaceBrackets(args_str);

    auto it = params.find(args_str);
    if (it == params.end()) {
        std::cout << "No suitable params for " << args_str << std::endl;
        return 1;
    }

    size_t T = 100;
    size_t tick_for_save = 50;
    std::string input_file = "../fluid.json";
    std::visit([&](auto& simulator) { 
        simulator.runSimulation(T, tick_for_save, input_file); 
    }, arr[it->second]);
    return 0;
}
