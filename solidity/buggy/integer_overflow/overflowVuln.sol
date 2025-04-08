// SPDX-License-Identifier: MIT
pragma solidity ^0.6.0;

contract OverflowVulnerable {
    mapping(address => uint256) public balances;

    function deposit() public payable {
        balances[msg.sender] += msg.value;
    }

    function withdraw(uint256 _amount) public {
        require(balances[msg.sender] >= _amount, "Not enough balance");
        balances[msg.sender] -= _amount;
        msg.sender.transfer(_amount);
    }
}
