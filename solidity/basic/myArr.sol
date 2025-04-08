// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract myArr{
    uint[] public myUint = [1,4];
    uint8[] public myUint8 = [1,2,3];
    uint[][] public my2DArr = [[4,5,6],[7,8,9]];
    string[] public values;

    function addVal(string memory _value) public{
        values.push(_value);
    }

    function valueCount() public view returns(uint){
        return values.length;
    }
}