import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Library implements ILibrary {
    private List<LibraryItem> items;
    private int numberOfDays;

    public Library() {
        this.items = new ArrayList<>();
    }

    public void addItem(LibraryItem item) {
        this.items.add(item);
    }

    public void removeItem(LibraryItem item) {
        this.items.remove(item);
    }

    public LibraryItem searchForItem(String title) {
        for (LibraryItem item : this.items)
            if (item.getTitle().equals(title))
                return item;
        return null;
    }

    public boolean borrowItem(int itemId, String borrorName, int numberOfDays) {
        for (LibraryItem item : this.items) {
            if (item.getId() == itemId && item.isAvailable()) {
                item.checkout(borrorName);
                item.setNumberOfDays(numberOfDays);
                return true;
            }
        }
        return false;
    }

    public boolean returnItem(int itemId) {
        for (LibraryItem item : this.items) {
            if (item.getId() == itemId && !item.isAvailable()) {
                item.returnItem();
                return true;
            }
        }
        return false;
    }

    public void printInventory() {
        for (LibraryItem item : this.items) {
            System.out.println(item);
        }
    }

    public List<LibraryItem> getItems() {
        return items;
    }

    public void setItems(List<LibraryItem> items) {
        this.items = items;
    }

    public int getNumberOfDays() {
        return numberOfDays;
    }

    public void setNumberOfDays(int numberOfDays) {
        this.numberOfDays = numberOfDays;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Library library = (Library) o;
        return numberOfDays == library.numberOfDays && Objects.equals(items, library.items);
    }

    @Override
    public int hashCode() {
        return Objects.hash(items, numberOfDays);
    }

    @Override
    public String toString() {
        return "Library{" +
                "items=" + items +
                ", numberOfDays=" + numberOfDays +
                '}';
    }
}