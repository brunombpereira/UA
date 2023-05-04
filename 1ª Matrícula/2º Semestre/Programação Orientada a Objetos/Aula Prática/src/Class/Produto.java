package Class;

import Interfaces.Product;
import java.util.Objects;
import static Utils.Validate.*;

public class Produto implements Product {
    private String name;
    private int stock;
    private double price;

    public Produto(String name, int stock, double price) {
        if (validateProduct(stock, price)) {
            this.name = name;
            this.stock = stock;
            this.price = price;
        }
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getStock() {
        return stock;
    }

    @Override
    public void addStock(int quantidade) {
        stock += quantidade;
    }

    @Override
    public void removeStock(int quantidade) {
        stock -= quantidade;
    }

    public void setStock(int stock) {
        this.stock = stock;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Produto produto = (Produto) o;
        return stock == produto.stock && Double.compare(produto.price, price) == 0 && Objects.equals(name, produto.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, stock, price);
    }

    @Override
    public String toString() {
        return "Produto{" +
                "name='" + name + '\'' +
                ", stock=" + stock +
                ", price=" + price +
                '}';
    }
}
