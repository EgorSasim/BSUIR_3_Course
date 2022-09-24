using Faker.Core.Interfaces;
using Faker.Core.Generators;
using System.Collections;
using System.Reflection;

namespace Faker.Core
{
    public class Faker23 : IFaker
    {
        public T Create<T>() => (T)Create(typeof(T));
        private HashSet<Type> _dependens = new();

        private object Create(Type type)
        {
            type = Nullable.GetUnderlyingType(type) ?? type;

            if (Generator.SimpleGenerators.ContainsKey(type)) return Generator.SimpleGenerators[type]();
            if (type.IsGenericType && type.GetGenericTypeDefinition() == typeof(List<>))
            {
                var newList = Activator.CreateInstance(type) as IList;
                for (int i = 0; i < 5; i++)
                {
                    newList.Add(Create(type.GetGenericArguments()[0]));
                }

                return newList;
            }

            if (_dependens.Contains(type)) throw new Exception("Cycle depends");
            _dependens.Add(type);

            object result = CreateObj(type);

            _dependens.Remove(type);
            return result;
        }

        private object CreateObj(Type type)
        {
            var ctor = type.GetConstructors().MaxBy(x => x.GetParameters().Length);
            var @params = ctor.GetParameters();

            var publicSetters = type.GetProperties().Where(x => x.CanWrite && x.SetMethod.IsPublic);
            IEnumerable<FieldInfo> publicFields = type.GetFields().Where(x => x.IsPublic);

            publicSetters = publicSetters.Where(x => !@params.Any(y => x.Name == "set_" + y.Name));
            publicFields = publicFields.Where(x => !@params.Any(y => y.Name == x.Name)).ToArray();

            object result = CreateObj(ctor);

            foreach (var field in publicFields)
                field.SetValue(result, Create(field.FieldType));
            foreach (var prop in publicSetters)
                prop.SetValue(result, Create(prop.PropertyType));
            return result;
        }

        private object CreateObj(ConstructorInfo constructor)
        {
            List<object> @params = new();
            foreach (var param in constructor.GetParameters())
            {
                @params.Add(Create(param.ParameterType));
            }
            return constructor.Invoke(@params.ToArray());
        }
    }
}