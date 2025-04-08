// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

interface IERC20 {
    function transfer(address, uint) external returns (bool);
    function transferFrom(address, address, uint) external returns (bool);
    function balanceOf(address) external view returns (uint);
}

interface IDex {
    function getPrice() external view returns (uint);
}

contract LendingPool {
    IERC20 public collateralToken;
    IERC20 public borrowToken;
    IDex public oracle;

    mapping(address => uint) public deposits;

    constructor(address _collateral, address _borrow, address _oracle) {
        collateralToken = IERC20(_collateral);
        borrowToken = IERC20(_borrow);
        oracle = IDex(_oracle);
    }

    function deposit(uint amount) external {
        collateralToken.transferFrom(msg.sender, address(this), amount);
        deposits[msg.sender] += amount;
    }

    function borrow(uint amount) external {
        uint price = oracle.getPrice();
        uint value = deposits[msg.sender] * price;
        require(value >= amount, "Not enough collateral");
        borrowToken.transfer(msg.sender, amount);
    }
}
