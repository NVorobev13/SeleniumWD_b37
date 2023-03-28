using NUnit.Framework;
using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;
using OpenQA.Selenium;

namespace SeleniumWD_course
{
    internal class DescCountry
    {
        private IWebDriver driver;

        [SetUp]
        public void start()
        {
            driver = new ChromeDriver();
        }

        [Test]

        public void CheckingCounty()
        {
            driver.Url = "http://localhost/litecart/admin/";
            driver.FindElement(By.Name("username")).SendKeys("admin");
            driver.FindElement(By.Name("password")).SendKeys("admin");
            driver.FindElement(By.Name("login")).Click();
            Thread.Sleep(1000);
            driver.Url = "http://localhost/litecart/admin/?app=countries&doc=countries"; //переход на раздел - страны 

            var Rows = driver.FindElements(By.XPath("//table[@class='dataTable']/tbody/tr[@class='row']"));
            
            //Создание списков для дальнейшей обработки и сравнения
            List<string> Countries = new List<string>();
            List<string> Links = new List<string>();

            //Цикл для заполнения списков
            for (int k = 0; k < Rows.Count(); k++)
            {
                var row = Rows[k];
                var country = row.FindElement(By.XPath("./td[5]/a")).GetAttribute("textContent");   //XPath на наименование страны
                Countries.Add(country);
                var zone = row.FindElement(By.XPath("./td[6]")).GetAttribute("textContent");        //XPath на зону
                if (zone != "0")
                {
                    Links.Add(row.FindElement(By.XPath("./td[5]/a")).GetAttribute("href"));         //Поиск XPath страны с zone > 0
                }

            }

            //Сортировка списка стран
            List<string> SortingCountries = new List<string>(Countries);
            SortingCountries.Sort();

            //Проверка сортировки на валидность
            if (Countries.SequenceEqual(SortingCountries))
            {
                Console.WriteLine("The countries were sorted correctly.");
            }
            else
            {
                Console.WriteLine("The countries were sorted incorrectly.");
            }


            //Проверка корректности сортировка зон
            foreach (string link in Links)
            {
                driver.Url = link;
                var Names = driver.FindElements(By.XPath("//table[@id='table-zones']/tbody/tr/td[3]"));
                List<string> NameZone = new List<string>();
                foreach (IWebElement name in Names)
                {
                    if (name.GetAttribute("textContent") != "")
                    {
                        NameZone.Add(name.GetAttribute("textContent"));
                    }
                }
                // создание сортировочного списка
                List<string> ZoneNamesSorted = new List<string>(NameZone);
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