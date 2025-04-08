// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

interface AggregatorV3Interface {
    function latestAnswer() external view returns (int256);
}

contract ChainlinkStyleOracle {
    int256 private _price;

    constructor(int256 initialPrice) {
        _price = initialPrice; // simulasi harga awal
    }

    function updatePrice(int256 newPrice) external {
        // Dalam Chainlink asli, tidak bisa sembarangan update.
        // Di sini hanya simulasi agar bisa diuji
        _price = newPrice;
    }

    function latestAnswer() external view returns (int256) {
        return _price;
    }
}
