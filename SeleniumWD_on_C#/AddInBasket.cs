using OpenQA.Selenium.Chrome;
using OpenQA.Selenium.Support.UI;
using OpenQA.Selenium;

namespace SeleniumWD_course
{
    internal class AddInBasket
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
            int DuckAdd = 0;
            driver.Url = "http://localhost/litecart/";

            //создаем цикл добавления товара в корзину
            for (int i = 0; i < 5; i++)
            {
                driver.FindElement(By.XPath($"//ul[@class='listing-wrapper products']/li[{i + 1}]/a[1]")).Click();
                wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.UrlContains("duck"));
                
                var DuckQuantity = (int.Parse(driver.FindElement(By.XPath("//span[@class='quantity']")).GetAttribute("textContent")) + 1).ToString();
                
                try
                {
                    SelectElement ProductDuckSize = new SelectElement(driver.FindElement(By.XPath(".//*[@id=\"box-product\"]/div[2]/div[2]/div[5]/form/table/tbody/tr[1]/td/select")));
                    ProductDuckSize.SelectByValue("Medium");
                }
                catch (NoSuchElementException) { }
                
                driver.FindElement(By.XPath(".//button[@name='add_cart_product']")).Click();
                wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.TextToBePresentInElement(driver.FindElement(By.XPath(".//span[@class='quantity']")), DuckQuantity));

                DuckAdd++;
                driver.Url = "http://localhost/litecart/";
            }

            //проваливаемся в корзину и дожидаемся загрузки всех элементов
            driver.FindElement(By.XPath(".//div[@id='cart']/a[@class='link']")).Click();
            wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.UrlContains("checkout"));
            IWebElement? element = null;

            //записываем в новую переменную количество текущего товара в корзине
            var ProductBasketCount = driver.FindElements(By.XPath(".//table[@class='dataTable rounded-corners']//td[@class='item']")).Count;

            //создаем цикл удаления из корзины всех элементов
            for (int j = 0; j < ProductBasketCount; j++)
            {
                var BasketOurItem = driver.FindElement(By.XPath(".//div[@style='display: inline-block;']//a")).GetAttribute("textContent");
                var BasketItems = driver.FindElements(By.XPath(".//table[@class='dataTable rounded-corners']//td[@class='item']"));
                foreach (var Item in BasketItems)
                {
                    if (Item.GetAttribute("textContent") == BasketOurItem) element = Item;
                }
                driver.FindElement(By.XPath(".//button[@value='Remove']")).Click();
                wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.StalenessOf(element));
            }

            //ожидаем внесенных изменений 
            wait.Until(SeleniumExtras.WaitHelpers.ExpectedConditions.ElementIsVisible(By.XPath(".//em")));
            driver.Url = "http://localhost/litecart/";

            Console.WriteLine("В корзине произошли следующие изменения: ");
            Console.WriteLine("Товаров добавленно - " + DuckAdd + " шт.");
        }
        [TearDown]
        public void End()
        {
            driver.Quit();
            driver = null;
        }
    }
}
