// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract DoSVictim {
    address[] public recipients;
    address public owner;

    constructor() {
        owner = msg.sender;
    }

    function addRecipient(address _addr) public {
        recipients.push(_addr);
    }

    function distribute() public {
        require(msg.sender == owner, "Not authorized");
        for (uint i = 0; i < recipients.length; i++) {
            // Bisa gagal jika salah satu address menolak transfer atau gas limit terlampaui
            payable(recipients[i]).call{value: 1 wei}("");
        }
    }

    receive() external payable {}
}
