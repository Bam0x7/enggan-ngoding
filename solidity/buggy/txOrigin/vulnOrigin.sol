// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract TxOriginBank {
    address public owner;

    constructor() {
        owner = msg.sender;
    }

    function transferTo(address payable _to, uint _amount) public {
        require(tx.origin == owner, "Not owner!");
        (bool sent, ) = _to.call{value: _amount}("");
        require(sent, "Failed to send Ether");
    }

    // fungsi ini boleh dipertahankan
    receive() external payable {}

    // tapi tambahkan ini biar bisa cek saldo
    function getBalance() public view returns (uint) {
        return address(this).balance;
    }
}
