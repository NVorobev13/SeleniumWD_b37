using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;

namespace task_001_open_browser
{
    [TestFixture]
    public class GoSections
    {

        private IWebDriver driver;
        private WebDriverWait wait;

        [SetUp]
        public void StartBrowser()
        {
            driver = new ChromeDriver();
            wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
        }

        [Test]
        public void StartSearch()
        {
            driver.Url = "http://localhost/litecart/admin/";
            IWebElement element = wait.Until(d => d.FindElement(By.Name("username")));
            driver.FindElement(By.Name("username")).SendKeys("admin");
            driver.FindElement(By.Name("password")).SendKeys("admin");
            driver.FindElement(By.Name("remember_me")).Click();
            driver.FindElement(By.Name("login")).Click();
            driver.FindElement(By.CssSelector("#app- > a > span.name")).Click();
                driver.FindElement(By.XPath("//*[@id=\"doc-template\"]/a/span")).Click();
                driver.FindElement(By.XPath("//*[@id=\"doc-logotype\"]/a/span")).Click();
        }

        [TearDown]
        public void end()
        {
            driver.Quit();
            driver = null;
        }
    }
}
