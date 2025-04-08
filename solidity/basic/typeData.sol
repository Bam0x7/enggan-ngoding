// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract myData{
    uint public myUint = 25;
    uint256[] public myArr = [1,4];

    struct myStruct{
        uint myInt;
        string myString;
    }
    myStruct public myStr = myStruct(20, "ibnu Ruslan");

    function retVal() public pure returns(string memory){
        string memory value = "hello solidity";
        return value;
    }
}