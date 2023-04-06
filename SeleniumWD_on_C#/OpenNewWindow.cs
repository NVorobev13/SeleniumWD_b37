using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;
using OpenQA.Selenium;

namespace SeleniumWD_course
{
    internal class OpenNewWindow
    {
        private IWebDriver driver;
        private WebDriverWait wait;
        public ExpectedConditions? ExpectedConditions;

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
            driver.FindElement(By.XPath(".//*[@id=\"box-login\"]/form/div[1]/table/tbody/tr[1]/td[2]/span/input")).SendKeys("admin");
            driver.FindElement(By.XPath(".//*[@id=\"box-login\"]/form/div[1]/table/tbody/tr[2]/td[2]/span/input")).SendKeys("admin");
            driver.FindElement(By.XPath(".//*[@id=\"box-login\"]/form/div[2]/button")).Click();
            Thread.Sleep(1000);

            driver.Url = "http://localhost/litecart/admin/?app=countries&doc=countries";
            wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.UrlContains("countries"));
            driver.FindElement(By.XPath(".//td[@id='content']//tr[@class='row']//a")).Click();
            Thread.Sleep(1000);
            var Countries = driver.FindElements(By.XPath(".//i[@class='fa fa-external-link']"));
            string WindowsOpen = driver.CurrentWindowHandle;

            Console.WriteLine("Открытие новых окон: ");

            //создаем цикл по воспроизведению сценария на открытие окон
            foreach(var NewPage in Countries)
            {
                Thread.Sleep(1000);
                ICollection<string> MainWindows = driver.WindowHandles;
                NewPage.Click();                                            //открываем новое окно
                string NewWindowsPage = FindNewPage(driver, MainWindows);   //объявляем новое окно
                driver.SwitchTo().Window(NewWindowsPage);                   //переключение на открытое окно
                Console.WriteLine("Окно - " + NewWindowsPage);              //записываем в консольный вывод наш результат
                Thread.Sleep(1000);
                driver.Close();                                             //закрываем открытое окно
                driver.SwitchTo().Window(WindowsOpen);                      //переходи на главное окно
            }
        }
        [TearDown]
        public void End()
        {
            driver.Quit();
            driver = null;
        }

        //поиск нового окна в браузере
        static string FindNewPage(IWebDriver driver, ICollection<string> OldPagesWin, int RetryCount = 100)
        {
            bool ReturnValues;
            string OtherPagesWin = null;
            for (var i = 0; i < RetryCount; Thread.Sleep(1000), i++)
            {
                ICollection<string> AllPagesWin = driver.WindowHandles;
                ReturnValues = (OldPagesWin.Equals(AllPagesWin) ? true : false);
                if (!ReturnValues)
                {
                    foreach(var Window in AllPagesWin)
                    {
                        if (!OldPagesWin.Contains(Window))
                        {
                            OtherPagesWin = Window;
                        }
                        else if (OtherPagesWin != null)
                        {
                            return OtherPagesWin;
                        }
                    }
                }
            }
            throw new ApplicationException("Новое окно - отсутсвует.");
        }
    }
}
