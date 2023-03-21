using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;

namespace OpenBrowser
{
    [TestFixture]
    public class OpenBrowser
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
            driver.Url = "https://google.com/";
            IWebElement element = wait.Until(d => d.FindElement(By.Name("q")));
            driver.FindElement(By.Name("q")).SendKeys("Selenium WebDriver");
            driver.FindElement(By.Name("btnI")).Click();
            //driver.FindElement(By.Name("WebDriver - Selenium")).Click();
        }

        [TearDown]
        public void end()
        {
            driver.Quit();
            driver = null;
        }
    }
}