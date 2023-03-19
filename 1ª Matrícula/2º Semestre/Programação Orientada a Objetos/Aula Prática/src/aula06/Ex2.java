package aula06;

import java.util.Scanner;
import Class.Date;
import Class.Contacto;

public class Ex2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Contacto[] contacts = new Contacto[10];

        while (true) {
            System.out.println("--------Contactos--------\n");
            System.out.println("1 - Inserir contacto\n2 - Alterar contacto\n3 - Apagar contacto\n4 - Procurar contacto\n5 - Listar contacto\n0 - Sair\n");
            System.out.print("Opção: ");
            int option = sc.nextInt();

            if (option == 1) {
                System.out.println("----------------------------------------------------------------------------------------------------\n");
                System.out.print("Nome: ");
                sc.nextLine();
                String name = sc.nextLine();
                System.out.print("Número do Cartão de Cidadão: ");
                int cc = sc.nextInt();
                System.out.println("\nData de Nascimento: \n");
                System.out.print("Dia: ");
                int day = sc.nextInt();
                System.out.print("Mês: ");
                int month = sc.nextInt();
                System.out.print("Ano: ");
                int year = sc.nextInt();

                Date birthDate = new Date(year, month, day);

                System.out.print("\nNúmero de telemóvel: ");
                int phoneNumber = sc.nextInt();
                System.out.print("Email: ");
                String email = sc.next();

                Contacto contact = new Contacto(name, cc, birthDate, phoneNumber, email);

                for (int i = 0; true;) {
                    if (contacts[i] != null && contacts[i].equals(contact)) {
                        System.out.print("Este contacto já existe, quer continuar a inserir como novo contacto? (Sim/Não)");
                        String choice = sc.next().toLowerCase();

                        if (choice.equals("sim")) {
                            for (int j = 0; j < contacts.length; j++) {
                                if (contacts[j] == null) {
                                    contacts[j] = contact;
                                    break;
                                }
                            }
                        }
                    } else {
                        for (int j = 0; j < contacts.length; j++) {
                            if (contacts[j] == null) {
                                contacts[j] = contact;
                                break;
                            }
                        }
                    }
                    break;
                }
            } else if (option == 2) {
                int counter = 0;

                System.out.println("----------------------------------------------------------------------------------------------------\n");
                System.out.print("Qual o número de telemóvel do contacto? ");
                int phoneNumber = sc.nextInt();

                for (Contacto contact : contacts) {
                    if (contact != null && contact.getPhoneNumber() == phoneNumber) {
                        System.out.println(contact + "\n");
                        counter++;
                    }
                }

                if (counter > 1) {
                    System.out.print("Insira o ID do contacto que deseja alterar: ");
                    int id = sc.nextInt();
                    System.out.println("O que deseja alterar?\n");
                    System.out.println("1 - Nome\n2 - Número de Cartão de Cidadão\n3 - Data de Nascimento\n4 - Número de telemóvel\n5 - Email\n0 - Cancelar");
                    System.out.print("Opção: ");
                    int choice = sc.nextInt();

                    while (true) {
                        if (choice == 1) {
                            System.out.print("\nNovo nome: ");
                            sc.nextLine();
                            String newName = sc.nextLine();

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getId() == id) {
                                    contact.setName(newName);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 2) {
                            System.out.print("\nNovo Número de Cartão de Cidadão: ");
                            int newCc = sc.nextInt();

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getId() == id) {
                                    contact.setCc(newCc);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 3) {
                            System.out.println("\nNova Data de Nascimento: ");
                            System.out.print("Dia: ");
                            int day = sc.nextInt();
                            System.out.print("Mês: ");
                            int month = sc.nextInt();
                            System.out.print("Ano: ");
                            int year = sc.nextInt();

                            Date newBirthDate = new Date(year, month, day);

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getId() == id) {
                                    contact.setBirthDate(newBirthDate);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 4) {
                            System.out.print("\nNovo Número de telemóvel: ");
                            int newPhoneNumber = sc.nextInt();

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getId() == id) {
                                    contact.setPhoneNumber(newPhoneNumber);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 5) {
                            System.out.print("\nNovo email: ");
                            sc.nextLine();
                            String newEmail = sc.nextLine();

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getId() == id) {
                                    contact.setEmail(newEmail);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 0) {
                            break;
                        }
                    }
                } else {
                    System.out.println("O que deseja alterar?\n");
                    System.out.println("1 - Nome\n2 - Número de Cartão de Cidadão\n3 - Data de Nascimento\n4 - Número de telemóvel\n5 - Email\n0 - Cancelar");
                    System.out.print("Opção: ");
                    int choice = sc.nextInt();

                    while (true) {
                        if (choice == 1) {
                            System.out.print("\nNovo nome: ");
                            sc.nextLine();
                            String newName = sc.nextLine();

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getPhoneNumber() == phoneNumber) {
                                    contact.setName(newName);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 2) {
                            System.out.print("\nNovo Número de Cartão de Cidadão: ");
                            int newCc = sc.nextInt();

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getPhoneNumber() == phoneNumber) {
                                    contact.setCc(newCc);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 3) {
                            System.out.println("\nNova Data de Nascimento: ");
                            System.out.print("Dia: ");
                            int day = sc.nextInt();
                            System.out.print("Mês: ");
                            int month = sc.nextInt();
                            System.out.print("Ano: ");
                            int year = sc.nextInt();

                            Date newBirthDate = new Date(year, month, day);

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getPhoneNumber() == phoneNumber) {
                                    contact.setBirthDate(newBirthDate);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 4) {
                            System.out.print("\nNovo Número de telemóvel: ");
                            int newPhoneNumber = sc.nextInt();

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getPhoneNumber() == phoneNumber) {
                                    contact.setPhoneNumber(newPhoneNumber);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 5) {
                            System.out.print("\nNovo email: ");
                            sc.nextLine();
                            String newEmail = sc.nextLine();

                            for (Contacto contact : contacts) {
                                if (contact != null && contact.getPhoneNumber() == phoneNumber) {
                                    contact.setEmail(newEmail);
                                    break;
                                }
                            }
                            break;
                        } else if (choice == 0) {
                            break;
                        }
                    }
                }
            } else if (option == 3) {
                Contacto[] newContacts = new Contacto[10];
                int counter = 0;
                int count = 0;

                System.out.println("----------------------------------------------------------------------------------------------------\n");
                System.out.println("\nIntroduza o número do contacto que deseja apagar: ");
                int phoneNumber = sc.nextInt();

                for (Contacto contact : contacts) {
                    if (contact != null && contact.getPhoneNumber() == phoneNumber) {
                        counter++;
                    }
                }

                if (counter > 1) {
                    System.out.println("\nComo há mais de 1 contacto com este nome, insira o ID do contacto que deseja apagar: ");
                    int id = sc.nextInt();

                    for (Contacto contact : contacts) {
                        count++;

                        if (contact != null && contact.getId() == id) {
                            for (int i = 0; i < newContacts.length; i++) {
                                if (i != (count - 1)) {
                                    newContacts[i] = contacts[i];
                                }
                            }
                        }
                    }

                } else {
                    for (Contacto contact : contacts) {
                        count++;

                        if (contact != null && contact.getPhoneNumber() == phoneNumber) {
                            for (int i = 0; i < newContacts.length; i++) {
                                if (i != (count - 1)) {
                                    newContacts[i] = contacts[i];
                                }
                            }
                        }
                    }

                }
                contacts = newContacts;
                System.out.println("\nContacto apagado.");
            } else if (option == 4) {
                System.out.println("----------------------------------------------------------------------------------------------------\n");
                System.out.print("\nInsira o nome do contacto que deseja procurar: ");
                sc.nextLine();
                String name = sc.nextLine();

                for (Contacto contact : contacts) {
                    if (contact != null && contact.getName().equals(name)) {
                        System.out.println(contact + "\n");
                    }
                }
            } else if (option == 5) {
                System.out.println("----------------------------------------------------------------------------------------------------\n");
                for (Contacto contact : contacts) {
                    if (contact != null) {
                        System.out.println(contact + "\n");
                    }
                }
            } else if (option == 0) {
                break;
            }
        }
    }
}
