using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;
using OpenQA.Selenium;

namespace SeleniumWD_course
{
    internal class UsersReg
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
            int value = new Random().Next(1488, 7699);
            driver.Url = "http://localhost/litecart/";
            driver.FindElement(By.XPath(".//*[@id=\"box-account-login\"]/div/form/table/tbody/tr[5]/td/a")).Click();
            Thread.Sleep(1000);

            //создание переменных для поиска искомых элементов
            var UserFirstN = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[2]/td[1]/input"));
            var UserLastN = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[2]/td[2]/input"));
            var UserAddress = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[3]/td[1]/input"));
            var UserPostcode = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[4]/td[1]/input"));
            var UserCity = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[4]/td[2]/input"));
            var UserCountry = driver.FindElement(By.XPath(".//select[@name='country_code']"));
            var UserState = driver.FindElement(By.XPath(".//select[@name='zone_code']"));
            var UserEmail = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[6]/td[1]/input"));
            var UserPhone = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[6]/td[2]/input"));
            var UserPasswordD = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[8]/td[1]/input"));
            var UserPasswordC = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[8]/td[2]/input"));
            var UserEntrance = driver.FindElement(By.XPath(".//*[@id=\"create-account\"]/div/form/table/tbody/tr[9]/td/button"));
            
            //создание переменных для заполнения полей
            string TextFirstN = "User";
            string TextLastN = "Testing";
            string TextAddress = value + "' Owner";
            string TextPostcode = "7" + value;
            string TextCity = "Vankuver";
            string TextEmail = "support" + value + "@yahoo.com";
            string TextPhone = "+7921373" + value;
            string TextPassword = "qwerty123";
            string TextCountry = "United States";
            string TextState = "South Dakota";

            //заносим данные в определнные ранее поля
            UserFirstN.SendKeys(TextFirstN);
            UserLastN.SendKeys(TextLastN);
            UserAddress.SendKeys(TextAddress);
            UserPostcode.SendKeys(TextPostcode);
            UserCity.SendKeys(TextCity);
            UserEmail.SendKeys(TextEmail);
            UserPhone.SendKeys(TextPhone);
            UserPasswordD.SendKeys(TextPassword);
            UserPasswordC.SendKeys(TextPassword);
            UserCountry.SendKeys(TextCountry);
            Thread.Sleep(5000);
            UserState.SendKeys(TextState);
            Thread.Sleep(5000);
            UserEntrance.Click();
            Thread.Sleep(1000);

            var UserLogout = driver.FindElement(By.XPath(".//*[@id=\"box-account\"]/div/ul/li[4]/a"));
            UserLogout.Click();
            Thread.Sleep(5000);

            driver.FindElement(By.XPath(".//*[@id=\"box-account-login\"]/div/form/table/tbody/tr[1]/td/input")).SendKeys(TextEmail);
            driver.FindElement(By.XPath(".//*[@id=\"box-account-login\"]/div/form/table/tbody/tr[2]/td/input")).SendKeys(TextPassword);
            driver.FindElement(By.XPath(".//*[@id=\"box-account-login\"]/div/form/table/tbody/tr[4]/td/span/button[1]")).Click();
            Thread.Sleep(1000);

            Console.WriteLine("В системе создан новый пользователь.");
            Console.WriteLine("------------------------------------");
            Console.WriteLine("Логин: " + TextFirstN + " " + TextLastN);
            Console.WriteLine("Пароль: " + TextPassword);
            Console.WriteLine("Адрес: " + TextCountry + ", " + TextState + ", " + TextCity);
            Console.WriteLine("Почта: " + TextEmail);
        }

        [TearDown]
        public void end()
        {
            driver.Quit();
            driver = null;
        }
    }
}
