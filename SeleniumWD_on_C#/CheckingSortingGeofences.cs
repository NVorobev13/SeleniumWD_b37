using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;
using OpenQA.Selenium;

namespace SeleniumWD_course
{
    internal class CheckingSortingGeofences
    {
        private IWebDriver driver;

        [SetUp]
        public void start()
        {
            driver = new ChromeDriver();
        }

        [Test]

        public void CheckingGeo()
        {
            driver.Url = "http://localhost/litecart/admin/";
            driver.FindElement(By.Name("username")).SendKeys("admin");
            driver.FindElement(By.Name("password")).SendKeys("admin");
            driver.FindElement(By.Name("login")).Click();
            Thread.Sleep(1000);
            driver.Url = "http://localhost/litecart/admin/?app=geo_zones&doc=geo_zones";

            // ссылки на зоны
            var Rows = driver.FindElements(By.XPath("//tr[@class='row']/td[3]/a"));
            List<string> Links = new List<string>();

            // заполнение списка ссылок на зоны
            for (int i = 0; i < Rows.Count(); i++)
            {
                var row = Rows[i];
                Links.Add(row.GetAttribute("href"));
            }

            // проверка сортировок в зонах
            foreach (string link in Links)
            {
                driver.Url = link;
                var Names = driver.FindElements(By.XPath("//table[@class='dataTable']/tbody/tr/td[3]/select/option[@selected='selected']"));
                List<string> NameZone = new List<string>();
                foreach (IWebElement name in Names)
                {
                    if (name.GetAttribute("textContent") != "")
                    {
                        NameZone.Add(name.GetAttribute("textContent"));
                    }
                }
                
                List<string> ZoneNamesSorted = new List<string>(NameZone); // создание сортировочного списка
                ZoneNamesSorted.Sort();
                // сравнение списков сортировки
                if (NameZone.SequenceEqual(ZoneNamesSorted))
                {
                    Console.WriteLine("The zones are sorted correctly.");
                }
                else
                {
                    Console.WriteLine("The zones are sorted incorrectly.");
                }
            }
        }

        [TearDown]
        public void stop()
        {
            driver.Quit();
            driver = null;
        }
    }
}
