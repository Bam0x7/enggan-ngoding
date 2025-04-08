// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract GriefingVictim {
    mapping(address => uint) public balances;

    function deposit() public payable {
        balances[msg.sender] += msg.value;
    }

    function withdraw() public {
        uint amount = balances[msg.sender];
        require(amount > 0, "Nothing to withdraw");

        // Reset balance dulu
        balances[msg.sender] = 0;

        // Kirim ETH, hanya 2300 gas diberikan
        payable(msg.sender).transfer(amount); // Rentan griefing
    }
}
