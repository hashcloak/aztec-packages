#pragma once
#include <ostream>
#include <string>

/**
 * Write a Sway VerificationKey loader function to the given stream.
 * Uses UltraHonk
 *
 * @param os
 * @param key - verification key object
 **/
inline void output_vk_sway_ultra_honk(std::ostream& os, auto const& key)
{
    const auto print_u256 = [&](const auto& element, const std::string& name) {
        os << "        " << name << ": 0x"
           << std::hex << std::nouppercase << element
           << "u256," << std::dec << "\n";
    };

    const auto print_g1 = [&](const auto& element, const std::string& name) {
        os << "        " << name << ": G1Point {\n"
           << "            x: " << std::hex << std::nouppercase << element.x << "u256,\n"
           << "            y: " << std::hex << std::nouppercase << element.y << "u256,\n"
           << "        },\n" << std::dec;
    };

    os <<
      "contract;\n\n"
      "use std::hash::Hash;\n"
      "use std::hash::keccak256;\n"
      "use std::array_conversions::u256::*;\n"
      "use std::bytes_conversions::u256::*;\n"
      "use std::bytes::Bytes;\n\n"
      "// TODO remove\n"
      "use std::logging::log;\n\n";

    // Constants
    os << "const N: u256 = " << std::dec << key->circuit_size << ";\n";
    os << "const LOG_N: u256 = " << std::dec << key->log_circuit_size << ";\n";
    os << "const NUMBER_OF_PUBLIC_INPUTS: u64 = " << std::dec << key->num_public_inputs << ";\n\n";

    os <<
      "\n"
      "pub fn load_vk() -> VerificationKey {\n"
      "    VerificationKey {\n";

    // VK fields
    print_u256(key->circuit_size, "circuit_size");
    print_u256(key->log_circuit_size, "log_circuit_size");
    print_u256(key->num_public_inputs, "public_inputs_size");

    print_g1(key->q_m, "qm");
    print_g1(key->q_c, "qc");
    print_g1(key->q_l, "ql");
    print_g1(key->q_r, "qr");
    print_g1(key->q_o, "qo");
    print_g1(key->q_4, "q4");
    print_g1(key->q_lookup, "q_lookup");
    print_g1(key->q_arith, "q_arith");
    print_g1(key->q_delta_range, "q_delta_range");
    print_g1(key->q_elliptic, "q_elliptic");
    print_g1(key->q_aux, "q_aux");
    print_g1(key->q_poseidon2_external, "q_poseidon2_external");
    print_g1(key->q_poseidon2_internal, "q_poseidon2_internal");

    print_g1(key->sigma_1, "s1");
    print_g1(key->sigma_2, "s2");
    print_g1(key->sigma_3, "s3");
    print_g1(key->sigma_4, "s4");

    print_g1(key->table_1, "t1");
    print_g1(key->table_2, "t2");
    print_g1(key->table_3, "t3");
    print_g1(key->table_4, "t4");

    print_g1(key->id_1, "id1");
    print_g1(key->id_2, "id2");
    print_g1(key->id_3, "id3");
    print_g1(key->id_4, "id4");

    print_g1(key->lagrange_first, "lagrange_first");
    print_g1(key->lagrange_last, "lagrange_last");

    os <<
      "    }\n"
      "}\n";

    os << std::flush;
}
