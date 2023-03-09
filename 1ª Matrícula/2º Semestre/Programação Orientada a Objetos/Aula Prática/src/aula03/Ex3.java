package aula03;

import java.util.Scanner;

public class Ex3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int max = 100;
        int min = 1;
        int range = max - min + 1;
        int secretNumber = (int)(Math.random() * range) + min;
        int counter = 1;

        while(true) {
            
            System.out.print("Número: ");
            int n = sc.nextInt();

            if(n != secretNumber) {
                if(n > secretNumber) {
                    System.out.println("Valor demasiado alto.");
                    counter++;
                }else {
                    System.out.println("Valor demasiado baixo");
                    counter++;
                }
            }else {
                System.out.println("Tentativas: " + counter);
                System.out.print("Pretende continuar? Prima (S)im ");
                String option = sc.next();

                if(!option.equals("S") && !option.equals("Sim") ) {
                    break;
                }else {
                    secretNumber = (int)(Math.random() * range) + min;
                    counter = 0;
                }                
            }
        }

        sc.close();
    }
}
