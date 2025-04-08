// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract VulnerableOracle {
    uint public price = 1;

    function setPrice(uint newPrice) external {
        price = newPrice;
    }

    function getPrice() external view returns (uint) {
        return price;
    }
}
