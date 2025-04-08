// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

import "@openzeppelin/contracts/token/ERC20/ERC20.sol";

contract CollateralToken is ERC20 {
    constructor() ERC20("CollateralToken", "COL") {
        _mint(msg.sender, 1000 ether);
    }
}

contract BorrowToken is ERC20 {
    constructor() ERC20("BorrowToken", "BOR") {
        _mint(msg.sender, 1000 ether);
    }
}
