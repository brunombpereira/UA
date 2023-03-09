package aula03;

import java.util.Scanner;

public class Ex2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = 0;
        double taxa = 0.0;

        while(true) {
            System.out.print("Investimento: ");
            n = sc.nextInt();    

            if(n >= 0 && n % 1000 == 0) {
                break;
            }

            
        }

        while(true) {
            System.out.print("Taxa de juros mensal: ");
            taxa = sc.nextDouble();

            if(taxa >= 0.0 || taxa <= 5) {
                break;
            }
        }

        double c = (double)n;

        for(int i = 1; i <= 12; i++) {
            c = c + (taxa / 100.0) * c;
            
            System.out.println(i + "º Mês: " + c);
        }

        sc.close();
    }
}
