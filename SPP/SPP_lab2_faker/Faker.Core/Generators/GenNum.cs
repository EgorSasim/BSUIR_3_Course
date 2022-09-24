using System.Reflection;
namespace Faker.Core.Generators 
{
    internal class NumericGenerator: Generator 
    {
         static NumericGenerator()
        {
            var genFunctions = typeof(NumericGenerator).GetMethods(BindingFlags.NonPublic | BindingFlags.Static);

            foreach (var func in genFunctions) simpleGenerators[func.ReturnType] = () => func.Invoke(null, null);
        }

        private static short Int16() => BitConverter.ToInt16(GetBytes(sizeof(short)));
        private static int Int32() => BitConverter.ToInt32(GetBytes(sizeof(int)));
        private static long Int64() => BitConverter.ToInt64(GetBytes(sizeof(long)));
        private static ushort UInt16() => BitConverter.ToUInt16(GetBytes(sizeof(ushort)));
        private static uint UInt32() => BitConverter.ToUInt32(GetBytes(sizeof(uint)));
        private static ulong UInt64() => BitConverter.ToUInt64(GetBytes(sizeof(ulong)));
        private static float Single() => BitConverter.ToSingle(GetBytes(sizeof(float)));
        private static double Double() => BitConverter.ToDouble(GetBytes(sizeof(double)));
    }
}