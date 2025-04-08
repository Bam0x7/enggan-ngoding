// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract myCondition{
    uint[] public myArr = [1,2,20,4,18,6,7,8,9,10];

    address public owner;

    constructor(){
        owner = msg.sender;
    }

    function evenNumber() public view returns (uint){
        uint count = 0;
        for(uint i = 0; i < myArr.length;i++){
            if(isEven(myArr[i])){
                count += 1;
            }
        }

        return count;
    }

    function isEven(uint _num) public pure returns (bool){
        if(_num%2 == 0){
            return true;
        }else{
            return false;
        }
    }

    function isOwner() public view returns(bool){
        return owner == msg.sender;
    }
}