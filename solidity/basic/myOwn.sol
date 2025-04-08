// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract Ownable {
    address public owner;

    constructor() {
        owner = msg.sender;
    }

    modifier onlyOwner() {
        require(msg.sender == owner, "must be owner");
        _;
    }
}

contract SecVault {
    string private secret;

    constructor(string memory _secret) {
        secret = _secret;
    }

    function getSecret() public view returns (string memory) {
        return secret;
    }
}

contract myContract is Ownable {
    address public secretVault;

    constructor(string memory _secret) Ownable() {
        SecVault _secVault = new SecVault(_secret);
        secretVault = address(_secVault);
        super;
    }

    function getSecret() public view onlyOwner returns (string memory) {
        SecVault _secVault = SecVault(secretVault);
        return _secVault.getSecret();
    }
}
