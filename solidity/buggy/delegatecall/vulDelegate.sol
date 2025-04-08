// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract VulnerableBank {
    address public logic;
    mapping(address => uint256) public balances;

    constructor(address _logic) {
        logic = _logic;
    }

    fallback() external payable {
        (bool ok, ) = logic.delegatecall(msg.data);
        require(ok, "delegatecall failed");
    }

    receive() external payable {}
}
