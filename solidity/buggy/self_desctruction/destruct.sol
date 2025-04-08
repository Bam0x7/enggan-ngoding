// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract VulnerableKill {
    address public owner;

    constructor() payable {
        owner = msg.sender;
    }

    function deposit() public payable {}

    function getBalance() public view returns (uint) {
        return address(this).balance;
    }

    // VULNERABLE FUNCTION
    function destroy() public {
        selfdestruct(payable(msg.sender)); // <-- Tidak ada validasi
    }
}
