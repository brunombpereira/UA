import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        ILibrary library = new Library();
        Scanner scanner = new Scanner(System.in);
        String choice = "";

        while (!choice.equals("7")) {
            System.out.println("Library Menu:");
            System.out.println("1. Add item");
            System.out.println("2. Remove item");
            System.out.println("3. Search for item");
            System.out.println("4. Borrow item");
            System.out.println("5. Return item");
            System.out.println("6. Print inventory");
            System.out.println("7. Exit");

            System.out.print("Enter choice: ");
            choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    while (true) {
                        System.out.print("Which item do you want to add:\n\n1 - Book\n2 - DVD\n\nOption: ");
                        int option = scanner.nextInt();

                        if (option == 1) {
                            System.out.print("Enter book name: ");
                            scanner.nextLine();
                            String name = scanner.nextLine();
                            System.out.print("Enter book author: ");
                            String author = scanner.nextLine();

                            library.addItem(new Book(name, author));
                            break;
                        } else if (option == 2) {
                            System.out.print("Enter book name: ");
                            scanner.nextLine();
                            String name = scanner.nextLine();
                            System.out.print("Enter book author: ");
                            String author = scanner.nextLine();
                            System.out.print("Enter the duration of the DVD: ");
                            int duration = scanner.nextInt();

                            library.addItem(new DVD(name, author, duration));
                            break;
                        }
                        else {
                            System.out.println("Invalid option. Please enter a valid one.");
                        }
                    }
                    break;
                case "2":
                    while (true) {
                        System.out.print("Which item do you want to remove:\n\n1 - Book\n2 - DVD\n");
                        int option = scanner.nextInt();

                        if (option == 1) {
                            System.out.print("Enter book name: ");
                            String name = scanner.nextLine();
                            System.out.print("Enter book author: ");
                            String author = scanner.nextLine();

                            library.removeItem(new Book(name, author));
                            break;
                        } else if (option == 2) {
                            System.out.print("Enter book name: ");
                            String name = scanner.nextLine();
                            System.out.print("Enter book author: ");
                            String author = scanner.nextLine();
                            System.out.print("Enter the duration of the DVD: ");
                            int duration = scanner.nextInt();

                            library.removeItem(new DVD(name, author, duration));
                            break;
                        }
                        else {
                            System.out.println("Invalid option. Please enter a valid one.");
                        }
                    }
                    break;
                case "3":
                    System.out.print("Enter item name: ");
                    String nom = scanner.nextLine();

                    LibraryItem item = library.searchForItem(nom);

                    if (item != null)
                        System.out.println(item);
                    else
                        System.out.println("Item not found.");
                    break;
                case "4":
                    System.out.print("Enter item ID: ");
                    int itemId = Integer.parseInt(scanner.nextLine());
                    System.out.print("Enter borror name: ");
                    String borrorName = scanner.nextLine();
                    System.out.print("For how long will you borrow it (days): ");
                    int numberOfDays = scanner.nextInt();

                    library.borrowItem(itemId, borrorName, numberOfDays);
                    break;
                case "5":
                    System.out.println("Enter item ID: ");
                    int returnId = Integer.parseInt(scanner.nextLine());

                    library.returnItem(returnId);
                    break;
                case "6":
                    library.printInventory();
                    break;
                case "7":
                    System.out.println("Exiting program.");
                    break;
                default:
                    System.out.println("Invalid choice.\nPlease enter an existing choice.\n\n");
            }
        }
        scanner.close();
    }
}