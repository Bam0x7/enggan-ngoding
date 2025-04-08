// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

interface IERC20 {
    function transfer(address, uint) external returns (bool);
    function transferFrom(address, address, uint) external returns (bool);
    function balanceOf(address) external view returns (uint);
}

interface AggregatorV3Interface {
    function latestAnswer() external view returns (int256);
}

contract SafeLendingPool {
    IERC20 public collateralToken;
    IERC20 public borrowToken;
    AggregatorV3Interface public oracle;

    mapping(address => uint) public deposits;

    constructor(address _collateral, address _borrow, address _oracle) {
        collateralToken = IERC20(_collateral);
        borrowToken = IERC20(_borrow);
        oracle = AggregatorV3Interface(_oracle);
    }

    function deposit(uint amount) external {
        collateralToken.transferFrom(msg.sender, address(this), amount);
        deposits[msg.sender] += amount;
    }

    function borrow(uint amount) external {
        int256 price = oracle.latestAnswer();
        require(price > 0, "Invalid price");

        // Cek nilai collateral berdasarkan harga aktual (asumsikan 1:1 decimals)
        uint value = deposits[msg.sender] * uint(price);
        require(value >= amount, "Not enough collateral");

        borrowToken.transfer(msg.sender, amount);
    }
}
