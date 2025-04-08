// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract hotelRoom {
    enum Status { Vacant, Occupied }
    Status public currentStatus;

    event Occupy(address _occupant, uint256 _value);

    address payable public owner;

    constructor() {
        owner = payable(msg.sender);
        currentStatus = Status.Vacant;
    }

    modifier onlyVacant{
        require(currentStatus == Status.Vacant, "Room is occupied");
        _;
    }

    modifier costs(uint _amount) {
        require(msg.value >= _amount, "Not enough ether sent");
        _;
    }

    // Perhatikan: modifier tidak pakai argumen
    receive() external payable onlyVacant costs(2 ether) {
        currentStatus = Status.Occupied;
        owner.transfer(msg.value);
        emit Occupy(msg.sender, msg.value);
    }
}
