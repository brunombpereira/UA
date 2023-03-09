package aula02;

import java.util.Scanner;

public class Ex4 {

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        System.out.print("Montante investido: ");
        double mi = sc.nextDouble();
        System.out.print("Taxa de juro mensal: ");
        double j = sc.nextDouble();

        for(int i = 1 ; i <= 3; i++) {
            mi = (mi * (j / 100)) + mi;
        }
        
        System.out.println("O valor total ao fim de 3 meses é de " + mi + "€.");

        sc.close();
    }
}
