// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract MalleableContract {
    mapping(bytes32 => bool) public usedHash;

    function claimReward(uint256 amount, bytes memory signature) external {
        bytes32 messageHash = keccak256(abi.encodePacked(msg.sender, amount));
        require(!usedHash[messageHash], "Already claimed");

        address signer = recover(messageHash, signature);
        require(signer == msg.sender, "Invalid signer");

        usedHash[messageHash] = true;

        // Simulasi pemberian reward (bisa berupa transfer token)
    }

    function recover(bytes32 messageHash, bytes memory sig) internal pure returns (address) {
        bytes32 ethSignedMessageHash = 
            keccak256(abi.encodePacked("\x19Ethereum Signed Message:\n32", messageHash));
        (bytes32 r, bytes32 s, uint8 v) = split(sig);

        return ecrecover(ethSignedMessageHash, v, r, s);
    }

    function split(bytes memory sig) internal pure returns (bytes32 r, bytes32 s, uint8 v) {
        require(sig.length == 65, "invalid sig");

        assembly {
            r := mload(add(sig, 32))
            s := mload(add(sig, 64))
            v := byte(0, mload(add(sig, 96)))
        }
    }
}
