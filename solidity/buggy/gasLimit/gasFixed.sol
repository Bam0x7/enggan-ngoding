// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract DoSVictimFixed {
    address[] public recipients;
    mapping(address => uint) public balances;
    address public owner;

    constructor() {
        owner = msg.sender;
    }

    function addRecipient(address _addr) public {
        recipients.push(_addr);
    }

    function distribute(uint _amount) public {
        require(msg.sender == owner, "Not authorized");

        for (uint i = 0; i < recipients.length; i++) {
            balances[recipients[i]] += _amount;
        }
    }

    function withdraw() public {
        uint amount = balances[msg.sender];
        require(amount > 0, "No funds");
        balances[msg.sender] = 0;

        (bool success, ) = payable(msg.sender).call{value: amount}("");
        require(success, "Transfer failed");
    }

    receive() external payable {}
}
