// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract LogicBankVulnerable {
    mapping(address => uint256) public balances;

    function deposit() public payable {
        balances[msg.sender] += msg.value;
    }

    function withdraw() public {
        uint bal = balances[msg.sender];
        require(bal > 0, "No balance");

        // 💥 Kirim ETH dulu sebelum update saldo
        (bool sent, ) = msg.sender.call{value: bal}("");
        require(sent, "Failed to send");

        balances[msg.sender] = 0; // Terlambat!
    }
}
