// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract MyContract {
    mapping(address => uint256) public balances;
    address payable public wallet;

    event Purchase(
        address indexed _buyer,
        uint256 _amount
    );

    constructor(address payable _wallet) {
        wallet = _wallet;
    }

    receive() external payable {
        buyToken();
    }

    function buyToken() public payable {
        require(msg.value > 0, "Must send ETH to buy tokens");
        balances[msg.sender] += 1;
        wallet.transfer(msg.value);
        emit Purchase(msg.sender, 1);
    }
}
