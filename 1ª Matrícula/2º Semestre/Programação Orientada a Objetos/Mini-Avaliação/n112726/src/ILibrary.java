public interface ILibrary {
    public void addItem(LibraryItem item);
    public void removeItem(LibraryItem item);
    public LibraryItem searchForItem(String title);
    public boolean borrowItem(int itemId, String borrorName, int numberOfDays);
    public boolean returnItem(int itemId);
    public void printInventory();
}