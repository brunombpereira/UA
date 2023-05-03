package aula08;

import java.util.Scanner;
import Class.*;
import static Utils.Validate.*;

public class Ex1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Empresa[] enterprises = new Empresa[10];
        VeiculoMotorizado[] veiculosMotorizados = new VeiculoMotorizado[10];
        boolean exits = false;

        while (true) {
            System.out.println("\n----Aluguer de Viaturas----\n");
            System.out.println("1 - Adicionar uma empresa\n2 - Adicionar uma viatura\n3 - Adicionar trajeto\n4 - Listar empresas\n5 - Listar viaturas\n0 - Sair");
            System.out.print("Opção: ");
            int option = sc.nextInt();

            if (option == 1) {
                while (true) {
                    System.out.println("---------------------------------------\n");
                    System.out.print("Nome da empresa: ");
                    String name = sc.next();
                    System.out.print("Código Postal: ");
                    String postalCode = sc.next();
                    System.out.print("Email: ");
                    String email = sc.next();

                    Empresa enterprise = new Empresa(name, postalCode, email);

                    if (enterprise.getName() != null) {
                        for (Empresa empresa : enterprises) {
                            if (empresa != null) {
                                if (empresa.equals(enterprise)) {
                                    exits = true;
                                    break;
                                }
                            }
                        }

                        if (exits) {
                            System.out.print("\nA empresa " + name + "já existe. Quer adicionar à mesma esta empresa? (S/N) ");
                            String choice = sc.nextLine();

                            if (choice.equalsIgnoreCase("S") || choice.equalsIgnoreCase("Sim")) {
                                for (int a = 0; a < enterprises.length; a++) {
                                    if (enterprises[a] == null) {
                                        enterprises[a] = new Empresa(name, postalCode, email);
                                        exits = false;
                                    } else {
                                        Empresa[] empresas = new Empresa[enterprises.length + 10];
                                        for (int i = 0; i < enterprises.length; i++) {
                                            empresas[i] = enterprises[i];

                                            if (i == (enterprises.length - 1)) {
                                                empresas[i + 1] = new Empresa(name, postalCode, email);
                                            }
                                        }
                                        enterprises = empresas;
                                        exits = false;
                                    }
                                }
                            }
                        } else {
                            for (int i = 0; i < enterprises.length; i++) {
                                if (enterprises[i] == null && enterprise.getName() != null) {
                                    enterprises[i] = enterprise;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
            } else if (option == 2) {
                while (true) {
                    System.out.println("---------------------------------------\n");
                    int couter = 0;
                    for (int i = 0; i < enterprises.length; i++) {
                        if (enterprises[i] != null) {
                            couter++;
                            System.out.println((i + 1) + " - " + enterprises[i].getName());
                        }
                    }

                    try {
                        System.out.print("\nA qual empresa quer adicionar a viatura? (1 - " + couter + ") : ");
                        int choice = sc.nextInt();

                        if ((1 <= choice) && (choice <= couter)) {
                            try {
                                System.out.println("\nDe entre as opções seguintes escolha a viatura que quer adicionar.\n");
                                System.out.print("1 - Motociclo\n2 - Automóvel Ligeiro\n3 - Táxi\n4 - Pesado de Mercadorias\n5 - Pesado de Passageiros\n0 - Cancelar\n\nOpção: ");

                                try {
                                    int escolha = sc.nextInt();

                                    System.out.print("\nQual é o número da matrícula da viatura? ");
                                    sc.nextLine();
                                    String plate = sc.nextLine();
                                    System.out.print("Qual é a marca da viatura? ");
                                    String brand = sc.nextLine();
                                    System.out.print("Qual é o modelo da viatura? ");
                                    String model = sc.nextLine();
                                    System.out.print("Qual é a potência da viatura (CV)? ");
                                    int potency = sc.nextInt();
                                    System.out.print("Quantos quilómetros tem a viatura? ");
                                    int km = sc.nextInt();

                                    if (escolha == 1) {
                                        System.out.print("Qual o tipo do motociclo? (Desportivo/Estrada) ");

                                        try {
                                            sc.nextLine();
                                            String type = sc.nextLine();

                                            for (int i = 0; i < veiculosMotorizados.length; i++) {
                                                if (veiculosMotorizados[i] == null) {
                                                    veiculosMotorizados[i] = new Motociclo(plate, brand, model, potency, km, enterprises[choice - 1].getName(), type);
                                                    break;
                                                } else if (veiculosMotorizados[i] != null && i == veiculosMotorizados.length - 1){
                                                    VeiculoMotorizado[] veiculoMotorizados = new VeiculoMotorizado[veiculosMotorizados.length + 10];

                                                    System.arraycopy(veiculosMotorizados, 0, veiculoMotorizados, 0, veiculosMotorizados.length);

                                                    veiculoMotorizados[veiculosMotorizados.length + 1] = new Motociclo(plate, brand, model, potency, km, enterprises[choice - 1].getName(), type);
                                                    veiculosMotorizados = veiculoMotorizados;
                                                    break;
                                                }
                                            }
                                            break;
                                        } catch (Exception ignored) {
                                        }
                                    } else if (escolha == 2) {
                                        System.out.print("Qual é o número do quadro? ");

                                        try {
                                            int serialNumber = sc.nextInt();

                                            System.out.print("Qual é a acapacidade da bagageira? ");

                                            try {
                                                int luggageCapacity = sc.nextInt();

                                                for (int i = 0; i < veiculosMotorizados.length; i++) {
                                                    if (veiculosMotorizados[i] == null) {
                                                        veiculosMotorizados[i] = new AutomovelLigeiro(plate, brand, model, potency, km, enterprises[choice - 1].getName(), serialNumber, luggageCapacity);
                                                        break;
                                                    } else if (veiculosMotorizados[i] != null && i == veiculosMotorizados.length - 1){
                                                        VeiculoMotorizado[] veiculoMotorizados = new VeiculoMotorizado[veiculosMotorizados.length + 10];

                                                        for (int a = 0; a < veiculosMotorizados.length; a++) {
                                                            veiculoMotorizados[a] = veiculosMotorizados[a];
                                                        }

                                                        veiculoMotorizados[veiculosMotorizados.length + 1] = new AutomovelLigeiro(plate, brand, model, potency, km, enterprises[choice - 1].getName(), serialNumber, luggageCapacity);
                                                        veiculosMotorizados = veiculoMotorizados;
                                                        break;
                                                    }
                                                }
                                            }catch (Exception ignored) {
                                            }
                                        }catch (Exception ignored) {
                                        }
                                    } else if (escolha == 3) {
                                        System.out.print("Qual é o número do quadro? ");

                                        try {
                                            int serialNumber = sc.nextInt();

                                            System.out.print("Qual é a acapacidade da bagageira? ");

                                            try {
                                                int luggageCapacity = sc.nextInt();

                                                System.out.print("Qual é o número da licença? ");

                                                try {
                                                    int licenseNumber = sc.nextInt();

                                                    for (int i = 0; i < veiculosMotorizados.length; i++) {
                                                        if (veiculosMotorizados[i] == null) {
                                                            veiculosMotorizados[i] = new Taxi(plate, brand, model, potency, km, enterprises[choice - 1].getName(), serialNumber, luggageCapacity, licenseNumber);
                                                            break;
                                                        } else if (veiculosMotorizados[i] != null && i == veiculosMotorizados.length - 1){
                                                            VeiculoMotorizado[] veiculoMotorizados = new VeiculoMotorizado[veiculosMotorizados.length + 10];

                                                            for (int a = 0; a < veiculosMotorizados.length; a++) {
                                                                veiculoMotorizados[a] = veiculosMotorizados[a];
                                                            }

                                                            veiculoMotorizados[veiculosMotorizados.length + 1] = new Taxi(plate, brand, model, potency, km, enterprises[choice - 1].getName(), serialNumber, luggageCapacity, licenseNumber);
                                                            veiculosMotorizados = veiculoMotorizados;
                                                            break;
                                                        }
                                                    }
                                                } catch (Exception ignored) {
                                                }
                                            }catch (Exception ignored) {
                                            }
                                        }catch (Exception ignored) {
                                        }
                                    } else if (escolha == 4) {
                                        System.out.print("Qual é o número do quadro? ");

                                        try {
                                            int serialNumber = sc.nextInt();

                                            System.out.print("Qual o peso do veículo? ");

                                            try {
                                                int weight = sc.nextInt();

                                                System.out.print("Qual é a carga máxima do veículo? ");

                                                try {
                                                    int maxLoad = sc.nextInt();

                                                    for (int i = 0; i < veiculosMotorizados.length; i++) {
                                                        if (veiculosMotorizados[i] == null) {
                                                            veiculosMotorizados[i] = new PesadoMercadorias(plate, brand, model, potency, km, enterprises[choice - 1].getName(), serialNumber, weight, maxLoad);
                                                            break;
                                                        } else if (veiculosMotorizados[i] != null && i == veiculosMotorizados.length - 1){
                                                            VeiculoMotorizado[] veiculoMotorizados = new VeiculoMotorizado[veiculosMotorizados.length + 10];

                                                            for (int a = 0; a < veiculosMotorizados.length; a++) {
                                                                veiculoMotorizados[a] = veiculosMotorizados[a];
                                                            }

                                                            veiculoMotorizados[veiculosMotorizados.length + 1] = new PesadoMercadorias(plate, brand, model, potency, km, enterprises[choice - 1].getName(), serialNumber, weight, maxLoad);
                                                            veiculosMotorizados = veiculoMotorizados;
                                                            break;
                                                        }
                                                    }
                                                }catch (Exception ignored) {
                                                }
                                            }catch (Exception ignored) {
                                            }
                                        } catch (Exception ignored) {
                                        }
                                    } else if (escolha == 5) {
                                        System.out.print("Qual é o número do quadro? ");

                                        try {
                                            int serialNumber = sc.nextInt();

                                            System.out.print("Qual o peso do veículo? ");

                                            try {
                                                int weight = sc.nextInt();

                                                System.out.print("Qual é o número máximo de passageiros do veículo? ");

                                                try {
                                                    int maxPassengers = sc.nextInt();

                                                    for (int i = 0; i < veiculosMotorizados.length; i++) {
                                                        if (veiculosMotorizados[i] == null) {
                                                            veiculosMotorizados[i] = new PesadoPassageiros(plate, brand, model, potency, km, enterprises[choice - 1].getName(), serialNumber, weight, maxPassengers);
                                                            break;
                                                        } else if (veiculosMotorizados[i] != null && i == veiculosMotorizados.length - 1){
                                                            VeiculoMotorizado[] veiculoMotorizados = new VeiculoMotorizado[veiculosMotorizados.length + 10];

                                                            for (int a = 0; a < veiculosMotorizados.length; a++) {
                                                                veiculoMotorizados[a] = veiculosMotorizados[a];
                                                            }

                                                            veiculoMotorizados[veiculosMotorizados.length + 1] = new PesadoPassageiros(plate, brand, model, potency, km, enterprises[choice - 1].getName(), serialNumber, weight, maxPassengers);
                                                            veiculosMotorizados = veiculoMotorizados;
                                                            break;
                                                        }
                                                    }
                                                    break;
                                                }catch (Exception ignored) {
                                                }
                                            }catch (Exception ignored) {
                                            }
                                        } catch (Exception ignored) {
                                        }
                                    } else if (escolha == 0) {
                                        break;
                                    }
                                }catch (Exception ignored) {
                                }
                            }catch (Exception ignored) {
                            }
                        }
                    } catch (Exception ignored) {
                    }
                }
            } else if (option == 3) {
                System.out.println("\n---------------------------------------\n");
                int couter = 0;
                int count = 0;
                for (int i = 0; i < enterprises.length; i++) {
                    if (enterprises[i] != null) {
                        couter++;
                        System.out.println((i + 1) + " - " + enterprises[i].getName());
                    }
                }

                System.out.println("\nEm que empresa se encontra a viatura? (1 - " + couter + ") ");

                int choice = sc.nextInt();

                if ((1 <= choice) && (choice <= couter)) {
                    for (VeiculoMotorizado veiculoMotorizado : veiculosMotorizados) {
                        if (veiculoMotorizado != null) {
                            if (veiculoMotorizado.getCompanyName().equals(enterprises[choice - 1].getName())) {
                                count++;
                                System.out.println(veiculoMotorizado);
                                System.out.println("\n----------------------------------");
                            }
                        }
                    }

                    if (count > 1) {
                        System.out.print("Qual a matrícula do veículo? ");

                        try {
                            String plate = sc.nextLine();

                            if (validatePlate(plate)) {
                                System.out.println("Quantos quilómetros tem o trajeto? ");

                                try {
                                    int km = sc.nextInt();

                                    for (int i = 0; i < count; i++) {
                                        if (veiculosMotorizados[i] != null) {
                                            if (veiculosMotorizados[i].getPlate().equals(plate)) {
                                                veiculosMotorizados[i].trajeto(km);
                                                break;
                                            }
                                        }
                                    }
                                }catch (Exception ignored) {
                                }
                            }
                        } catch (Exception ignored) {
                        }
                    } else {
                        System.out.println("Quantos quilómetros tem o trajeto? ");

                        try {
                            int km = sc.nextInt();

                            veiculosMotorizados[count -1].trajeto(km);
                        }catch (Exception ignored) {
                        }
                    }
                }
            } else if (option == 4) {
                for (Empresa enterprise : enterprises) {
                    if (enterprise != null) {
                        System.out.println("-----------------------------\n" + enterprise.getName() + "\n\n" + enterprise);
                    }
                }
            } else if (option == 5) {
                int counter = 0;
                for (int i = 0; i < enterprises.length; i ++) {
                    if (enterprises[i] != null) {
                        counter++;
                        System.out.println((i + 1) + " - " + enterprises[i].getName());
                    }
                }

                System.out.print("De qual empresa deseja ver as viaturas? (1 - " + counter + ") ");

                try {
                    int choice = sc.nextInt();

                    for (VeiculoMotorizado veiculoMotorizado : veiculosMotorizados) {
                        if (veiculoMotorizado != null) {
                            if (veiculoMotorizado.getCompanyName().equals(enterprises[choice - 1].getName())) {
                                System.out.println("----------------------\n" + veiculoMotorizado.getClass() + "\n\n" +  veiculoMotorizado);
                            }
                        }
                    }
                } catch (Exception ignored) {
                }
            }else if (option == 0) {
                break;
            }
        }
    }
}
