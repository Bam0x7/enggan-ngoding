// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract myState{
    enum State {Activate, Waiting, Ready}
    State public state;

    constructor(){
        state = State.Activate;
    }

    function activate() public{
        state = State.Activate;
    }

    function isActivate() public view returns(bool){
        return state == State.Activate;
    }
    
}