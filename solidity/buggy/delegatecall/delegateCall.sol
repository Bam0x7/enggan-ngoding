// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract DelegateLogic {
    address public owner;

    function takeOwnership() public {
        owner = msg.sender; // <-- akan mengubah storage kontrak yang delegatecall
    }
}

contract DelegateVulnerable {
    address public owner;
    address public lib;

    constructor(address _lib) {
        owner = msg.sender;
        lib = _lib;
    }

    function changeOwner() public {
        // 🐞 Tidak aman! Memanggil kode eksternal pakai delegatecall
        (bool success, ) = lib.delegatecall(
            abi.encodeWithSignature("takeOwnership()")
        );
        require(success, "Delegatecall failed");
    }
} //serangan reentrancy + delegatecall
