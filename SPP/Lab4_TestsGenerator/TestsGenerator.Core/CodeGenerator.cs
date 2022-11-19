using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

using static Microsoft.CodeAnalysis.CSharp.SyntaxFactory;

namespace TestsGenerator.Core
{
    internal static class CodeGenerator
    {
        public static List<ParsedClass> GetAllClassesFromFile(string fileText)
        {
            List<ParsedClass> classes = new();
            var tree = CSharpSyntaxTree.ParseText(fileText);

            IEnumerable<ClassDeclarationSyntax> classDeclarations = tree.GetRoot()
            .DescendantNodes()
            .OfType<ClassDeclarationSyntax>().ToList();

            foreach (var classDeclaration in classDeclarations)
            {
                var Parent = classDeclaration.Parent;
                Stack<string> NamespaceStack = new();
                while (Parent is not CompilationUnitSyntax)
                {
                    switch (Parent)
                    {
                        case ClassDeclarationSyntax ParentClass:
                            NamespaceStack.Push(ParentClass.Identifier.ToString());
                            break;
                        case NamespaceDeclarationSyntax ParentNamespace:
                            NamespaceStack.Push(ParentNamespace.Name.ToString());
                            break;
                    }
                    Parent = Parent.Parent;
                }

                var newClass = new ParsedClass() { ClassName = classDeclaration.Identifier.ToString(), Namespace = string.Join('.', NamespaceStack) };

                var methods = classDeclaration.Members.OfType<MethodDeclarationSyntax>().Where(x => x.ToString().Contains("public"));
                foreach (var method in methods)
                {
                    newClass.methods.Add(new ParsedMethod()
                    {
                        paramsStr = string.Join("_", method.ParameterList.Parameters.Select(x => x.Type.ToString())),
                        methodName = method.Identifier.Text
                    });
                }


                classes.Add(newClass);
            }

            return classes;
        }

        public static (string fileName, string content) BuildTextFile(ParsedClass parsedClass)
        {
            try
            {
                Console.WriteLine($"Generating test class for {parsedClass.FullName}");
                SyntaxList<MemberDeclarationSyntax> methodsSyntax = new();

                foreach (var method in parsedClass.methods)
                {
                    var methodSyntax = MethodDeclaration(
                                PredefinedType(
                                    Token(SyntaxKind.VoidKeyword)),
                                Identifier(method.fullName))
                            .WithAttributeLists(
                                SingletonList(
                                    AttributeList(
                                        SingletonSeparatedList(
                                            Attribute(
                                                IdentifierName("Test"))))))
                            .WithModifiers(
                                TokenList(Token(SyntaxKind.PublicKeyword)))
                            .WithBody(
                                Block(
                                    SingletonList<StatementSyntax>(
                                        ThrowStatement(
                                            ObjectCreationExpression(
                                                IdentifierName("NotImplementedException"))
                                            .WithArgumentList(
                                                ArgumentList()))
                                        ))).NormalizeWhitespace();
                    methodsSyntax = methodsSyntax.Add(methodSyntax);
                }


                var tree = SyntaxTree(
                    CompilationUnit()
                    .WithUsings(
        List(
            new UsingDirectiveSyntax[]{
            UsingDirective(
                IdentifierName(parsedClass.Namespace)),
            UsingDirective(
                IdentifierName("Xunit"))}))

                    .WithMembers(
                    SingletonList<MemberDeclarationSyntax>(
                        NamespaceDeclaration(
                            QualifiedName(
                                IdentifierName(parsedClass.Namespace),
                                IdentifierName("Tests")))
                    .WithMembers(
                    SingletonList<MemberDeclarationSyntax>(
                        ClassDeclaration(parsedClass.ClassName + "TestClass")
                        .WithAttributeLists(
                            SingletonList(
                                AttributeList(
                                    SingletonSeparatedList(
                                        Attribute(
                                            IdentifierName("TestFixture"))))))
                        .WithModifiers(
                            TokenList(
                                Token(SyntaxKind.PublicKeyword))).WithMembers(methodsSyntax)))))

                    .NormalizeWhitespace()


                    );

                return (parsedClass.FullName, tree.GetRoot().ToFullString());
            }
            catch
            {
                Console.WriteLine("dsa");
                return default;
            }
        }
    }
}
