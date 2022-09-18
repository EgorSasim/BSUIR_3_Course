using System.Reflection;
namespace Faker.Core.Generators
{
    internal sealed class StringGenerator : Generator
    {
        private const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        static StringGenerator()
        {
            var genFunctions = typeof(StringGenerator).GetMethods(BindingFlags.NonPublic | BindingFlags.Static);

            foreach (var func in genFunctions) simpleGenerators[func.ReturnType] = () => func.Invoke(null, null);
        }

        private static string String() => new(Enumerable.Repeat(chars, _random.Next(0, 64)).Select(s => s[_random.Next(s.Length)]).ToArray());
        private static char Char() => chars[_random.Next(chars.Length)];
    }
}