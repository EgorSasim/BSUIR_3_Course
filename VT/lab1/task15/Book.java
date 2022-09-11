import java.util.*;
import java.lang.reflect.Field;

class Book implements Comparable<Book> {
	private 	String title;
	private 	String author;
	private 	int price;
	private 	static int edition;
	private int isbn;

	public boolean equals(Object obj) {
		if (obj == this) 
			return true;
		if (!(obj instanceof Book)) 
			return false;
		Field[] thisField = this.getClass().getDeclaredFields(); 
		Field[] objFields = obj.getClass().getDeclaredFields();

		if (thisField.length != objFields.length) 
			return false;
		Book tmp = (Book)obj;


		return this.author == tmp.author && this.price == tmp.price && this.title == tmp.title; 
	}	

	public int hashCode() {
		int hash = 3;
		hash = 31 * hash + (title == null ? 0 : title.hashCode());
		hash = 31 * hash + (author == null ? 0 : title.hashCode());
		hash = 31 * hash + price;
		hash = 31 * hash + edition;
		return hash;
	}

	public String toString() {
		return this.author + "\n" + this.title + "\n" + Integer.toString(this.price) + "\n"; 
	}
	
	public int compareTo(Book book) {
		return Integer.compare(isbn, book.isbn);
	}	
}

