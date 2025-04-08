// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract MyContract {
    uint256 public peopleCount = 0;
    mapping(uint => Person) public people;
    
    address owner;

    modifier onlyOwner() {
        require(msg.sender == owner, "Only owner can call this function");
        _;
    }

    struct Person {
        uint _id;
        string _firstName;
        string _lastName;
    }

    constructor() {
        owner = msg.sender;
    }

    function addPerson(
        string memory _firstName,
        string memory _lastName
    )
        public onlyOwner
    {
        incrementCount();  
        people[peopleCount] = Person(peopleCount, _firstName, _lastName);
    }

    function incrementCount() internal {
        peopleCount += 1;
    }
}
