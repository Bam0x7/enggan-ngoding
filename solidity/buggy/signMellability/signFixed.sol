// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

import "@openzeppelin/contracts/utils/cryptography/ECDSA.sol";

contract FixedMalleable {
    using ECDSA for bytes32;

    mapping(bytes32 => bool) public usedSig;

    function claimReward(uint256 amount, bytes memory signature) external {
        bytes32 hash = keccak256(abi.encodePacked(msg.sender, amount));
        bytes32 ethSignedHash = hash.toEthSignedMessageHash();

        address signer = ethSignedHash.recover(signature);
        require(signer == msg.sender, "Invalid signature");

        require(!usedSig[ethSignedHash], "Already used");
        usedSig[ethSignedHash] = true;

        // reward logic
    }
}