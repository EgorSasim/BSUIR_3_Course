using OpenQA.Selenium;

namespace SchoolTests
{
    public class Tests
    {

        private IWebDriver driver;

        private readonly By oneWindowButton = By.XPath("//a[text() = 'Одно окно']");
        private readonly By blindPeopleVersionButton = By.XPath("//span[text() = 'Версия для слабовидящих' ]");
        private readonly By searchInputButton = By.XPath("//input[@name='text']");
        private readonly By searchButton = By.XPath("//input[@value='Найти']");

        private string textForSearch = "GSPD drug family";

        [SetUp]
        public void Setup()
        {
            driver = new OpenQA.Selenium.Chrome.ChromeDriver();
            driver.Navigate().GoToUrl("http://gymn6.minsk.edu.by/");
            driver.Manage().Window.Maximize();
        }

        [Test]
        public void Test1()
        {
            var hsearchInputButton = driver.FindElement(searchInputButton);
            hsearchInputButton.SendKeys(textForSearch);
            var hSearchButton = driver.FindElement(searchButton);
            hSearchButton.Click();

            Thread.Sleep(10000);

            var hBlindPeopleVersionButton = driver.FindElement(blindPeopleVersionButton);
            var hOneWindowButton = driver.FindElement(oneWindowButton);
            
            hBlindPeopleVersionButton.Click();
            hOneWindowButton.Click();
           
        }
        [TearDown]
        public void TearDown()
        {

        }

    }
}