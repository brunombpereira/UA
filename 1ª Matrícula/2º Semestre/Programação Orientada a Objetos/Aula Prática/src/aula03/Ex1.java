package aula03;

public class Ex1 {
    public static void main(String[] args) {
        int counter = 0;
        int n = Utils.positiveNumber.ispositive("Número: ");

        for(int i = n; i >= 1; i--) {

            if (Utils.isPrime.isPrime(i) == true) {
                counter += i;
            }
        }

        System.out.println("A soma dos números primos é igual a " + counter);
    }
}
