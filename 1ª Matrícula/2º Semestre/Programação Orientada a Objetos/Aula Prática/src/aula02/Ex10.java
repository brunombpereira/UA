package aula02;

import java.util.Scanner;

public class Ex10 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Número: ");
        double num = sc.nextDouble();

        double max = num;
        double min = num;
        double soma = num;
        int count = 1;

        while (true) {
            System.out.print("Digite outro número real ou o valor inicial para terminar: ");
            double n = sc.nextDouble();

            if (n == num) {
                break;
            }
            if (n > max){
                max = n;
            }
            if (n < min) {
                min = n;
            }
            
            soma += n;
            count ++;
        }

        double media = soma / count;

        System.out.println("Valor máximo: " + max);
        System.out.println("Valor mínimo: " + min);
        System.out.println("Média: " + media);
        System.out.println("Total de números lidos: " + count);

        sc.close();
    }
}
