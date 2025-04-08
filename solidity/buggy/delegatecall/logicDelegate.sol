// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Logic {
    // Storage layoutnya **tidak cocok**!
    uint public someNumber;  // slot 0 (⚠️ akan nabrak slot `implementation`)
    address public owner;    // slot 1 (masih cocok)

    function setNumber(uint _num) public {
        someNumber = _num;
    }

    function takeOwnership() public {
        owner = msg.sender;
    }
}
