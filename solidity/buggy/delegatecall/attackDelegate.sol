// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract FakeLogic {
    address public dummy;

    function pwn() public {
        selfdestruct(payable(msg.sender)); // Bisa juga: change state / transfer fund
    }
}
