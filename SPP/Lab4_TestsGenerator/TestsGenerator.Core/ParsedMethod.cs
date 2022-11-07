using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestsGenerator.Core
{
    public class ParsedMethod
    {
        public string paramsStr;

        public string methodName;

        public string fullName => $"{methodName}_{paramsStr}";

    }
}
