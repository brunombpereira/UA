package Class;

import Interfaces.Shopping;

import java.util.LinkedList;

public class CarrinhoDeCompras implements Shopping {
    private Produto product;
    private int stock;
    private final LinkedList<Object> shoppingCar = new LinkedList<>();

    @Override
    public void adicionarProduto(Produto produto, int quantidade) {
        shoppingCar.add(produto);
        shoppingCar.add(quantidade);
    }

    @Override
    public void listarProdutos() {
        StringBuilder stringBuilder = new StringBuilder();
        for (Object carrinhoDeCompra : shoppingCar) {
            if (carrinhoDeCompra.getClass().equals(Produto.class)) {
                stringBuilder.append(((Produto) carrinhoDeCompra).getName()).append(" - ");
            } else {
                stringBuilder.append(carrinhoDeCompra).append("\n");
            }
            System.out.println(stringBuilder);
        }
    }

    @Override
    public void calcularTotal() {
        double totalPrice = 0;
        for (int i = 0; i < shoppingCar.size(); i++) {
            if (i % 2 != 0) {
                totalPrice += Integer.parseInt(shoppingCar.get(i).toString());
            }
        }
        System.out.println("O preço total é de " + totalPrice + "€");
    }
}
