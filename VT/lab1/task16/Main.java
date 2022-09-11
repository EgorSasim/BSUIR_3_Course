import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

class Main {
    public static void main(String[] args) {
        ArrayList<Book> arr = new ArrayList<Book>();
        arr.add(new Book("book1", "author1", 1));
        arr.add(new Book("book7", "author1", 1));
        arr.add(new Book("book2", "author1", 1));
        arr.add(new Book("book6", "author1", 1));
        arr.add(new Book("book3", "author1", 1));

        for (int i = 0; i < arr.size(); ++i) {
            System.out.println(arr.get(i).title);
        }
        System.out.println();

        Collections.sort(arr, new sortByTitle());

        for (int i = 0; i < arr.size(); ++i) {
            System.out.println(arr.get(i).title);
        }
        System.out.println();
    }

    
    
}