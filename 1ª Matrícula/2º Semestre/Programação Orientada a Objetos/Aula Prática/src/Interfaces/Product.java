package Interfaces;

public interface Product {
    public String getName();
    public double getPrice();
    public int getStock();
    public void addStock(int quantidade);
    public void removeStock(int quantidade);
}
