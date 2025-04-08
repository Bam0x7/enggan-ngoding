// SPDX-License-Identifier: MIT
pragma solidity ^0.8.29; // Versi Solidity

contract HelloWorld {
    string public message;

    constructor() {
        message = "Hello, Web3!";
    }

    function setMessage(string memory _newMessage) public {
        message = _newMessage;
    }
}
