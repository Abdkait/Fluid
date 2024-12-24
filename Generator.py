import sys
import re
import itertools

cpp_template = """
#include "Simulator.h"
#include <cstdlib>
#include <unordered_map>
#include <variant>
#include <string>
#include <iostream>
#include <vector>

#define FLOAT float
#define DOUBLE double

using SimulatorCombinations = std::variant<{{types}}>;

void Str_to_combination(std::string& input) {
    std::string result;
    bool previousWasComma = false;
    for (char& c : input) {
        if (c == '(') {
            result += '<';
        } else if (c == ')') {
            result += '>';
        } else if (c == ' ') {
            if (previousWasComma) {
                result += ' ';
            }
        } else {
            result += c;
            previousWasComma = (c == ',');
        }
    }
    input = result;
}

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, int> combinations = { {{params}} };
    std::vector<SimulatorCombinations> arr = { {{types_vec}} };

    std::string p_type, v_type, v_flow_type, size, save_tick = "-1", input_file = "../fluid.json", num_ticks = "200";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("--p-type=") == 0) p_type = arg.substr(9);
        else if (arg.find("--v-type=") == 0) v_type = arg.substr(9);
        else if (arg.find("--v-flow-type=") == 0) v_flow_type = arg.substr(14);
        else if (arg.find("--size=") == 0) size = arg.substr(7);
        else if (arg.find("--save_tick=") == 0) save_tick = arg.substr(12); 
        else if (arg.find("--input_file=") == 0) input_file = arg.substr(13); 
        else if (arg.find("--num_ticks=") == 0) num_ticks = arg.substr(11); 
    }

    std::string args_str = p_type + " " + v_type + " " + v_flow_type + ", " + size;
    Str_to_combination(args_str);

    auto it = combinations.find(args_str);
    if (it == combinations.end()) {
        std::cout << "Not found combination for\\n" << args_str << std::endl;
        return 1;
    }

    std::visit([&](auto& simulator) { 
        simulator.runSimulation(std::stoi(num_ticks), std::stoi(save_tick), input_file); 
    }, arr[it->second]);
    return 0;
}
"""

def normalize_fast_fixed(input_string):
    """Replace FAST_FIXED(N, M) -> FAST_FIXED<N, M>"""
    return re.sub(r'FAST_FIXED\((\d+),\s*(\d+)\)', r'FAST_FIXED<\1,\2>', input_string)

def parse_types(input_string):
    """Parse and normalize types."""
    input_string = normalize_fast_fixed(input_string)
    input_string = re.sub(r'FIXED\((\d+),\s*(\d+)\)', r'FIXED<\1,\2>', input_string)
    type_strings = re.findall(r'FAST_FIXED<\d+,\d+>|FIXED<\d+,\d+>|DOUBLE|FLOAT', input_string)
    return type_strings

def create_combinations(types, sizes):
    """Create all possible combinations of types and sizes."""
    return [
        f"{', '.join(p)}, {size[0]}, {size[1]}"
        for p in itertools.product(types, repeat=3)
        for size in sizes
    ]

def generate_code(types, sizes):
    """Generate variant, vector, and params."""
    type_combinations = create_combinations(types, sizes)
    types_variant = ", ".join(f"Simulator<{t}>" for t in type_combinations)
    types_vec = ", ".join(f"Simulator<{t}>()" for t in type_combinations)
    params_map = ", ".join(f'{{"{t}", {i}}}' for i, t in enumerate(type_combinations))
    return types_variant, types_vec, params_map

if len(sys.argv) < 3:
    print("Usage: python generate_code.py <TYPES> <SIZES>")
    sys.exit(1)

types_value = sys.argv[1]
sizes_value = sys.argv[2]

def parse_string_to_pairs(input_string):
    pattern = r"S\((\d+),(\d+)\)"
    matches = re.findall(pattern, input_string)
    return [[int(x), int(y)] for x, y in matches]

parsed_types = parse_types(types_value)
sizes = parse_string_to_pairs(sizes_value)

variant, vec, params = generate_code(parsed_types, sizes)
rendered_code = cpp_template.replace("{{types}}", variant).replace("{{types_vec}}", vec).replace("{{params}}", params)

with open("main.cpp", "w") as cpp_file:
    cpp_file.write(rendered_code)

print("Generated main.cpp!")