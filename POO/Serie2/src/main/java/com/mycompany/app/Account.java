package main.java.com.mycompany.app;

public class Account {
    private int amount;
    private String owner;
    private int minimum_amount = -2000;

    public Account(String owner, int amount) {
        if (amount < minimum_amount) {
            throw new RuntimeException("Amount cannot be less than the minimum allowed: " + minimum_amount);
        }
        this.amount = amount;
        this.owner = owner;
    }

    public Account(String owner) {
        this(owner, 0); // Default amount to 0 if none provided
    }

    public static Account of(String owner, int amount) {
        if (amount < 0) {
            throw new RuntimeException("Amount must be positive");
        }
        return new Account(owner, amount);
    }

    public int amount() {
        return this.amount;
    }

    public void deposite(int value) {
        if (value <= 0) {
            throw new RuntimeException("Amount must be positive");
        }
        this.amount += value;
    }

    public void withdraw(int value) {
        if (value <= 0) {
            throw new RuntimeException("Amount must be positive");
        } else if (this.amount - value < minimum_amount) {
            throw new RuntimeException(
                    "Operation impossible: amount cannot go below the minimum allowed: " + minimum_amount);
        }

        this.amount -= value;
    }

    public void transfer(Account destination, int amount) {
        withdraw(amount);
        destination.deposite(amount);
    }

    public String getOwner() {
        return this.owner;
    }

    public boolean areEqual(Account first, Account second) {
        return (first.getOwner().equals(second.getOwner()) && first.amount() == second.amount());
    }
}
