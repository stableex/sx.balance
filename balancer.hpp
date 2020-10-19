#pragma once

#include "safemath.hpp"

namespace balancer {
    /**
     * ## STATIC `get_amount_out`
     *
     * Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset
     *
     * ### params
     *
     * - `{uint64_t} amount_in` - amount input
     * - `{uint64_t} reserve_in` - reserve input
     * - `{uint64_t} reserve_out` - reserve output
     * - `{uint8_t} [fee=30]` - (optional) trading fee (pips 1/100 of 1%)
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const uint64_t amount_in = 10000;
     * const uint64_t reserve_in = 45851931234;
     * const uint64_t reserve_out = 125682033533;
     * const uint8_t fee = 30;
     *
     * // Calculation
     * const uint64_t amount_out = balancer::get_amount_out( amount_in, reserve_in, reserve_out );
     * // => 27328
     * ```
     */
    static uint64_t get_amount_out( const uint64_t amount_in, const uint64_t reserve_in, const uint64_t reserve_out, const uint8_t fee = 30 )
    {
        // checks
        eosio::check(amount_in > 0, "SX.Balancer: INSUFFICIENT_INPUT_AMOUNT");
        eosio::check(reserve_in > 0 && reserve_out > 0, "SX.Balancer: INSUFFICIENT_LIQUIDITY");

        // calculations
        const uint128_t amount_in_with_fee = safemath::mul( static_cast<uint128_t>(amount_in), (10000 - fee));
        const uint128_t numerator = safemath::mul( amount_in_with_fee, reserve_out );
        const uint128_t denominator = safemath::add( safemath::mul(reserve_in, 10000), amount_in_with_fee);
        const uint64_t amount_out = numerator / denominator;

        return amount_out;
    }

    /**
     * ## STATIC `get_amount_in`
     *
     * Given an output amount of an asset and pair reserves, returns a required input amount of the other asset.
     *
     * ### params
     *
     * - `{uint64_t} amount_out` - amount input
     * - `{uint64_t} reserve_in` - reserve input
     * - `{uint64_t} reserveOut` - reserve output
     * - `{uint8_t} [fee=30]` - (optional) trading fee (pips 1/100 of 1%)
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const uint64_t amount_out = 27328;
     * const uint64_t reserve_in = 45851931234;
     * const uint64_t reserve_out = 125682033533;
     * const uint8_t fee = 30;
     *
     * // Calculation
     * const uint64_t amount_in = balancer::get_amount_in( amount_out, reserve_in, reserve_out, fee );
     * // => 10000
     * ```
     */
    static uint64_t get_amount_in( const uint64_t amount_out, const uint64_t reserve_in, const uint64_t reserve_out, const uint8_t fee = 30 )
    {
        // checks
        eosio::check(amount_out > 0, "SX.Balancer: INSUFFICIENT_OUTPUT_AMOUNT");
        eosio::check(reserve_in > 0 && reserve_out > 0, "SX.Balancer: INSUFFICIENT_LIQUIDITY");

        const uint128_t numerator = safemath::mul( safemath::mul( static_cast<uint128_t>(reserve_in), amount_out), 10000);
        const uint128_t denominator = safemath::mul( safemath::sub(reserve_out, amount_out), (10000 - fee));
        const uint64_t amount_in = safemath::add(numerator / denominator, 1);

        return amount_in;
    }

    /**
     * ## STATIC `quote`
     *
     * Given some amount of an asset and pair reserves, returns an equivalent amount of the other asset
     *
     * ### params
     *
     * - `{uint64_t} amount_a` - amount A
     * - `{uint64_t} reserve_a` - reserve A
     * - `{uint64_t} reserve_b` - reserve B
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const uint64_t amount_a = 10000;
     * const uint64_t reserve_a = 45851931234;
     * const uint64_t reserve_b = 125682033533;
     *
     * // Calculation
     * const uint64_t amount_b = balancer::quote( amount_a, reserve_a, reserve_b );
     * // => 27410
     * ```
     */
    static uint64_t quote( const uint64_t amount_a, const uint64_t reserve_a, const uint64_t reserve_b )
    {
        eosio::check(amount_a > 0, "SX.Balancer: INSUFFICIENT_AMOUNT");
        eosio::check(reserve_a > 0 && reserve_b > 0, "SX.Balancer: INSUFFICIENT_LIQUIDITY");
        const uint64_t amount_b = safemath::mul(amount_a, reserve_b) / reserve_a;
        return amount_b;
    }
}