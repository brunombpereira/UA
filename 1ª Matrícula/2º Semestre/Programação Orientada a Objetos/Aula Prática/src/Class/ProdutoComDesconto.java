package Class;

import java.util.Objects;

import static Utils.Validate.*;

public class ProdutoComDesconto extends Produto{
    private int discount;

    public ProdutoComDesconto(String name, int stock, double price, int discount) {
        super(name, stock, price);

        if (validateDiscount(discount)) {
            setPrice(price / (discount / 100.0));
            this.discount = discount;
        }
    }

    public int getDiscount() {
        return discount;
    }

    public void setDiscount(int discount) {
        this.discount = discount;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        ProdutoComDesconto that = (ProdutoComDesconto) o;
        return discount == that.discount;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), discount);
    }

    @Override
    public String toString() {
        return "ProdutoComDisconto{" +
                "discount=" + discount +
                '}';
    }
}
