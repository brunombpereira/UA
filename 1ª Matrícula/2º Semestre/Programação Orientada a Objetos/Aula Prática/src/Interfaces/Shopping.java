package Interfaces;

import Class.Produto;
public interface Shopping {
    void adicionarProduto (Produto produto, int quantidade);
    void listarProdutos();
    void calcularTotal();
}
