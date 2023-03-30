using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;
using OpenQA.Selenium;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SeleniumWD_course
{
    internal class CreateUser
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
            //int value = ;
            driver.Url = "http://localhost/litecart/";
            driver.FindElement(By.XPath(".//*[@id=\"box-account-login\"]/div/form/table/tbody/tr[5]/td/a")).Click();
            Thread.Sleep(1000);
            
            //создание переменных для поиска искомых элементов
            var UserFirstN = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[2]/td[1]/input"));
            var UserLastN = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[2]/td[2]/input"));
            var UserAddress = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[3]/td[1]/input"));
            var UserPostcode = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[4]/td[1]/input"));
            var UserCity = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[4]/td[2]/input"));
            //var UserCountry = driver.FindElement(By.XPath(""));
            //var UserState = driver.FindElement(By.XPath(""));
            var UserEmail = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[6]/td[1]/input"));
            var UserPhone = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[6]/td[1]/input"));
            var UserPasswordD = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[8]/td[1]/input"));
            var UserPasswordC = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[8]/td[2]/input"));

            //создание переменных для заполнения полей
            string TextFirstN = "User";
            string TextLastN = "Testing";
            string TextAddress = "6' Owner";
            string TextPostcode = "753159";
            string TextCity = "Vankuver";
            string TextEmail = "support@yahoo.com";
            string TextPhone = "+79213732394";
            string TextPassword = "qwerty123";

            UserFirstN.SendKeys(TextFirstN);
            UserLastN.SendKeys(TextLastN);
            UserAddress.SendKeys(TextAddress);
            UserPostcode.SendKeys(TextPostcode);
            UserCity.SendKeys(TextCity);
            UserEmail.SendKeys(TextEmail);
            UserPhone.SendKeys(TextPhone);
            UserPasswordD.SendKeys(TextPassword);
            UserPasswordC.SendKeys(TextPassword);

            driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[5]/td[1]/span[2]/span[1]/span/span[2]")).Click();
            driver.FindElement(By.XPath("/html/body/span/span/span[1]/input")).SendKeys("Canada");
            //driver.FindElement(By.XPath("//*[@id=\"select2-country_code-km-result-cfim-CA\"]")).Click();
            Thread.Sleep(10000);
            //UserLastN.SendKeys(new string);

            driver.Url = "http://localhost/litecart/admin/";
            IWebElement element = wait.Until(d => d.FindElement(By.Name("username")));
            driver.FindElement(By.Name("username")).SendKeys("admin");
            driver.FindElement(By.Name("password")).SendKeys("admin");
            driver.FindElement(By.Name("remember_me")).Click();
            driver.FindElement(By.Name("login")).Click();
        }

        [TearDown]
        public void end()
        {
            driver.Quit();
            driver = null;
        }
    }
}
