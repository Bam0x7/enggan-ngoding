// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract VulnStorage {
    address public owner;

    struct User {
        address addr;
        uint balance;
    }

    User public user;

    constructor() {
        owner = msg.sender;
    }

    function becomeOwner() public {
        User storage u = user[0]; // ❌ Uninitialized storage pointer
        user.addr = msg.sender; // 🧨 Ini menulis ke storage slot 0 (yaitu `owner`)
    }

    function isOwner() public view returns (bool) {
        return msg.sender == owner;
    }
}
