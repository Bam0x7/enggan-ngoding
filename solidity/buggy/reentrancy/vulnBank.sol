// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract vulnBank {
    mapping(address => uint256) public balances;

    function deposit() public payable {
        require(msg.value > 0, "Need to send ETH");
        balances[msg.sender] += msg.value;
    }

    function withdraw() public {
        uint256 amount = balances[msg.sender];
        require(amount > 0, "no funds");

        (bool success, ) = msg.sender.call{value: amount}("");
        require(success, "transfer failed");

        balances[msg.sender] = 0;
    }

    function getBalances() public view returns (uint256) {
        return address(this).balance;
    }
}
