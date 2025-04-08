// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract MyContract {
    string value;

    function get() public view returns (string memory) {
        return value;
    }  

    function set(string memory _value) public {
        value = _value;
    }

    constructor() {
        value = "myValue";
    } 
}
