package aula04;

record Product(String name, double price, int quantity) {

    public double getTotalValue() {
        return price * quantity;
    }
}


class CashRegister {
    private final Product[] products;
    private int count;

    public CashRegister() {
        this.products = new Product[100];
        this.count = 0;
    }

    public void addProduct(Product product) {
        products[count] = product;
        count++;
    }

    public void printReceipt() {
        System.out.printf("%-10s %9s %9s %9s", "Produto", "Price", "Quantity", "Total\n");

        double totalValue = 0;

        for (int i = 0; i < count; i++) {
            Product product = products[i];
            
            double value = product.getTotalValue();
            totalValue += value;
            System.out.printf("%-11s%10.2f\t%d\t\t%.2f\n", product.name(), product.price(), product.quantity(), value);
        }
        System.out.printf("Total value: %.2f", totalValue);
    }
}


public class Ex2 {

    public static void main(String[] args) {
        CashRegister cr = new CashRegister();

        cr.addProduct(new Product("Book", 9.99, 3));
        cr.addProduct(new Product("Pen", 1.99, 10));
        cr.addProduct(new Product("Headphones", 29.99, 2));
        cr.addProduct(new Product("Notebook", 19.99, 5));
        cr.addProduct(new Product("Phone case", 5.99, 1));
        cr.printReceipt();
    }
}

