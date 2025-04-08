// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Proxy {
    address public implementation; // slot 0
    address public owner;          // slot 1

    constructor(address _impl) {
        implementation = _impl;
        owner = msg.sender;
    }

    fallback() external payable {
        (bool ok, ) = implementation.delegatecall(msg.data);
        require(ok, "delegatecall failed");
    }
}
