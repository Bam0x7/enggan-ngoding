// SPDX-License-Identifier: GPL-3.0
pragma solidity >=0.8.2 <0.9.0;

contract myMapping{
    mapping (uint => string) public names;
    mapping (uint => myBook) public books;

    constructor(){
        names[1] = "bam";
        names[2] = "pekkaz";
        names[3] = "mazino";
        names[4] = "ruslan";
    }

    struct myBook{
        string title;
        string author;
    }

    function addBook(uint _id, string memory _title, string memory _author) public{
        books[_id] = myBook(_title, _author);
    }
}