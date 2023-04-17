using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;
using OpenQA.Selenium.Support.Events;
using OpenQA.Selenium;
using System;
using System.Collections;

namespace SeleniumWD_course
{
    internal class CheckLog
    {
        private WebDriverWait wait;
        private EventFiringWebDriver driver;


        [SetUp]
        public void StartBrowser()
        {
            driver = new EventFiringWebDriver(new ChromeDriver());
            wait = new WebDriverWait(driver, TimeSpan.FromSeconds(10));
            driver.FindingElement += (sender, e) => Console.WriteLine("Начинаем искать элемент - " + e.FindMethod);
            driver.FindElementCompleted += (sender, e) => Console.WriteLine(e.FindMethod + " - найден!");
            driver.ExceptionThrown += (sender, e) => Console.WriteLine(e.ThrownException + " - не найден!");

        }

        [Test]
        public void StartSearch()
        {
            driver.Url = "http://localhost/litecart/admin/";
            IWebElement element = wait.Until(d => d.FindElement(By.Name("username")));
            driver.FindElement(By.Name("username")).SendKeys("admin");
            driver.FindElement(By.Name("password")).SendKeys("admin");
            driver.FindElement(By.Name("login")).Click();
            driver.Url = "http://localhost/litecart/admin/?app=catalog&doc=catalog&category_id=1";
            Thread.Sleep(1000);

            var Rows = driver.FindElements(By.XPath(".//tr[@class='row']/td[3]/a"));
            List<string> Links = new();

            // заполнение списка ссылок на зоны
            for (int i = 1; i < Rows.Count(); i++)
            {
                var row = Rows[i];
                Links.Add(row.GetAttribute("href"));
               
            }
            
            foreach (string link in Links)
            {
                driver.Url = link;
                var Names = driver.FindElements(By.XPath("//table[@class='dataTable']/tbody/tr/td[3]/select/option[@selected='selected']"));
                List<string> NameZone = new();
                foreach (IWebElement name in Names)
                {
                    if (name.GetAttribute("textContent") != "")
                    {
                        NameZone.Add(name.GetAttribute("textContent"));
                    }
                }
                List<string> ZoneNamesSorted = new(NameZone); 
                ZoneNamesSorted.Sort();
            }            
            foreach (LogEntry l in driver.Manage().Logs.GetLog("browser"))
            {
                Console.WriteLine(l);
                Assert.That(l.Equals("[Error]"));
            }
        }

        [TearDown]
        public void End()
        {
            driver.Quit();
            driver = null;
        }
    }
}
