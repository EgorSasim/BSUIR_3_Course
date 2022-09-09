class Main {
	public static void main(String args[]) {
		Book book = new Book();
		book.author = "John konor";
		book.price = 3;
		book.title = "Terminator 3";
		Book.edition = 3;
		
		Book book2 = new Book();
		book2.author = "John konor";
		book2.price = 35;
		book2.title = "Terminator 3";

		boolean res = book.equals(book2);

		int hC = book.hashCode();
		int hC2 = book2.hashCode();

		String bStr = book.toString();
		String b2Str = book2.toString(); 

		Book cpBook = book.clone();
		System.out.println(cpBook.toString());

		System.out.println(res);
		System.out.println(hC == hC2);
		System.out.println(bStr);
		System.out.println(b2Str);

	}
}
