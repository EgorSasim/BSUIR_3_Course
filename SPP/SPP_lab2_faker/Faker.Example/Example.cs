using Faker.Core;
using Faker.Core.Interfaces;
using Faker;

class Example 
{
    public static void Main() 
    {
        int randInt = 0;
        float randFloat = 0.0F;
        double randDouble = 0.0;
        string randString = "";
        string randString2 = "";

        Faker23 _faker = new Faker23();

        randInt = _faker.Create<int>();
        randFloat = _faker.Create<float>();
        randDouble = _faker.Create<double>();
        randString = _faker.Create<string>();
        randString2 = _faker.Create<string>();

        Console.WriteLine($"Rand int: {randInt}\nRand float: {randFloat}\nRand double: {randDouble}\nRand string: {randString}\nRand string2: {randString2}");
    }
}