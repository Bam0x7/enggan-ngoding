// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract AccessControlVault {
    address public owner;
    string private secret;

    constructor(string memory _secret) {
        owner = msg.sender;
        secret = _secret;
    }

    // ❌ Tidak ada access control!
    function updateSecret(string memory _newSecret) public {
        secret = _newSecret;
    }

    function getSecret() public view returns (string memory) {
        require(msg.sender == owner, "Not owner!");
        return secret;
    }
}
