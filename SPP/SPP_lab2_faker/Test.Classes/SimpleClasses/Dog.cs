namespace Test.Classes.SimpleClasses
{
    public class Dog 
    {
        public string name;
        public string ownerName;

        public Dog(string _name) 
        {
            name = _name;
        }

        public void showName()
        {
            Console.WriteLine($"Dog name: {name}, Owner name: {ownerName}");
        }
    }
}