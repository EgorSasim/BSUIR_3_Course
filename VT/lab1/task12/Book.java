import java.util.*;
import java.lang.reflect.Field;

class Book {
	public 	String title;
	public 	String author;
	public 	int price;
	public 	static int edition;

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
}

