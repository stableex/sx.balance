
// calculations
const fee = 30;
const amount_in = 10000;
const reserve_in = 100000000;
const reserve_out = 400000000;

const amount_in_with_fee = amount_in * (10000 - fee);
const numerator = amount_in_with_fee * reserve_out;
const denominator = (reserve_in * 10000) + amount_in_with_fee;
const amount_out = numerator / denominator;
console.log(amount_out);
