// SPDX-License-Identifier: MIT
pragma solidity ^0.6.0;

contract OverflowDemo {
    uint8 public count = 255;

    function add() public {
        count += 1; // Boom! Overflow ke 0
    }
}
